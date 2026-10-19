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

void RenderBackendOpenGL4::Init( void ) {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	this->InitWindow();
	this->InitContext();	

	if (renderConfig.fullscreen) {
		SDL_SetWindowFullscreen( renderData.window, SDL_WINDOW_FULLSCREEN_DESKTOP );
	}

	if (renderConfig.resizeable) {
		SDL_SetWindowResizable( renderData.window, SDL_TRUE );
	}

	/*--------------------------------------------------------------------------
		Just in case:
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glEnalbe( GL_BACK );
	--------------------------------------------------------------------------*/
}

void RenderBackendOpenGL4::Reinit( void ) {
	SDL_GL_DeleteContext( renderData.context );
	SDL_DestroyWindow( renderData.window );

	renderConfig.Load("renderConfig.json");

	this->InitWindow();
	this->InitContext();

	if (renderConfig.fullscreen) {
		SDL_SetWindowFullscreen( renderData.window, SDL_WINDOW_FULLSCREEN_DESKTOP );
	}

	if (renderConfig.resizeable) {
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