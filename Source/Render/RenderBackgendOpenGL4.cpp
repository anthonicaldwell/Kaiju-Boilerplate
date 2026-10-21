/*------------------------------------------------------------------------------
    RenderBackendOpenGL4.cpp
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.19
--------------------------------------------------------------------------------
	
--------------------------------------------------------------------------------
	MIT License

	Copyright (c) 2026 Anthoni Caldwell (a.k.a. Data Kaiju データ怪獣)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
------------------------------------------------------------------------------*/
#include "RenderBackendOpenGL4.h"
#include "../Assets/Assets.h"
#include "stb_image.h"

void RenderBackendOpenGL4::Init( void ) {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	Reinit();

	glewExperimental = GL_TRUE;
	glewInit();

	/*--------------------------------------------------------------------------
		Just in case:
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glEnalbe( GL_BACK );
	--------------------------------------------------------------------------*/
}

void RenderBackendOpenGL4::Reinit( void ) {

	if ( renderData.context != nullptr) {
		SDL_GL_DeleteContext( renderData.context );
	}

	if ( renderData.window != nullptr ) {
		SDL_DestroyWindow( renderData.window );
	}

	this->InitWindow();
	this->InitContext();

	if (renderConfig.fullscreen) {
		SDL_SetWindowFullscreen( renderData.window, SDL_WINDOW_FULLSCREEN_DESKTOP );
	}

	if (renderConfig.resizable) {
		SDL_SetWindowResizable( renderData.window, SDL_TRUE );
	}
}

void RenderBackendOpenGL4::FrameStart( void ) {
	glClearColor( 0.2f, 0.5f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT ); // GL_DEPTH_BUFFER_BIT
}

void RenderBackendOpenGL4::FrameEnd( void ) {
	SDL_GL_SwapWindow( renderData.window );
}

void RenderBackendOpenGL4::Exit( void ) {
	SDL_GL_DeleteContext( renderData.context );
	SDL_DestroyWindow( renderData.window );
	SDL_Quit();
}

void RenderBackendOpenGL4::InitWindow( void ) {
	renderData.window = SDL_CreateWindow( renderConfig.title.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		renderConfig.windowWidth, renderConfig.windowHeight,
		SDL_WINDOW_OPENGL );

	if (!renderData.window) {
		std::cerr << "Failed to create application window!" << std::endl;
		return;
	}
}

void RenderBackendOpenGL4::InitContext( void ) {
	renderData.context = SDL_GL_CreateContext( renderData.window );

	if (!renderData.context) {
		std::cerr << "Failed to create OpenGL context!" << std::endl;
		return;
	}

	SDL_GL_SetSwapInterval(renderConfig.vsync);
}

/*------------------------------------------------------------------------------
	Shaders
------------------------------------------------------------------------------*/
void RenderBackendOpenGL4::LoadShader(const std::string& shaderName ) {
	// Load shader text
	// Convert to const

	// Create, Compile frag, vert, prog. Link prog;
	std::string shaderVertPath = "../Assets/Shaders/"+shaderName+".vert";
	std::string shaderFragPath = "../Assets/Shaders/"+shaderName+".frag";

	bool hasVert = Assets::Exists( shaderVertPath );
	bool hasFrag = Assets::Exists( shaderFragPath );

	Shader shade = {};

	shade.name = shaderName;
	shade.progID = glCreateProgram();

	int params;

	if (hasVert) {
		std::string vertSrc = Assets::LoadTextFile( shaderVertPath );
		const char * vsrc = vertSrc.c_str();

		shade.vertID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource( shade.vertID, 1, &vsrc, NULL );
		glCompileShader( shade.vertID );

		params = 0;

		glGetShaderiv( shade.vertID, GL_COMPILE_STATUS, &params );

		if (GL_TRUE != params) {
			int maxLength = 2048, actualLength = 0;
			char slog[2048];
			glGetShaderInfoLog( shade.vertID, maxLength, &actualLength, slog);

			std::string log;
			log += "ERROR: Vertex shader did not compile.\nIndex: ";
			log += std::to_string( shade.vertID ) + "\n";
			log += slog;
			Debug::log("shader", log);
			return;
		}

		glAttachShader( shade.progID, shade.vertID );
	}

	if (hasFrag) {
		std::string fragSrc =  Assets::LoadTextFile( shaderFragPath );
		const char * fsrc = fragSrc.c_str();

		shade.fragID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource( shade.fragID, 1, &fsrc, NULL );
		glCompileShader( shade.fragID );

		params = 0;		

		glGetShaderiv( shade.fragID, GL_COMPILE_STATUS, &params );

		if (GL_TRUE != params) {
			int maxLength = 2048, actualLength = 0;
			char slog[2048];
			glGetShaderInfoLog( shade.fragID, maxLength, &actualLength, slog);

			std::string log;
			log += "ERROR: Fragment shader did not compile.\nIndex: ";
			log += std::to_string( shade.fragID ) + "\n";
			log += slog;
			Debug::log("shader", log);
			return;
		}

		glAttachShader( shade.progID, shade.fragID );
	}

	glLinkProgram( shade.progID );

	params = 0;

	glGetProgramiv( shade.progID, GL_LINK_STATUS, &params);

	if (GL_TRUE != params) {
		int maxLength = 2048, actualLength = 0;
			char slog[2048];
			glGetProgramInfoLog( shade.progID, maxLength, &actualLength, slog);

			std::string log;
			log += "ERROR: Shader program did not link.\nIndex: ";
			log += std::to_string( shade.progID ) + "\n";
			log += slog;
			Debug::log("shader", log);
			return;
	}

	shaderList.push_back(shade);
}

void RenderBackendOpenGL4::UseShader(const std::string& shaderName ) {
	// Find shader name
	// Use shader
}

void RenderBackendOpenGL4::ShaderPushTexture() {
	// Push Sampler2D Uniform
}

void RenderBackendOpenGL4::ShaderPushMatrix() {
	// Push Matrix Uniform
}

void RenderBackendOpenGL4::ShaderPushVec4() {
	// Push Vec4 uniform
}

void RenderBackendOpenGL4::ShaderPushVec3() {
	// Push Vec3 uniform
}

void RenderBackendOpenGL4::ShaderPushVec2() {
	// Push Vec2 uniform
}

void RenderBackendOpenGL4::ShaderPushFloat() {
	// Push Float uniform
}

void RenderBackendOpenGL4::ShaderPushInt() {
	// Push Int
}