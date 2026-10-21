/*------------------------------------------------------------------------------
    Render.cpp
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.19
--------------------------------------------------------------------------------
	RenderSystem implementation.
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
#include "Render.h"
#include "stb_image.h"

void RenderSystem::Init( std::unique_ptr<RenderBackend> backend ) {

	if (backend != nullptr) {
		renderBackend = std::move(backend);
	} else {
		Debug::log( "render", "Render backend was nullptr!" );
		return;
	}

	if (renderBackend == nullptr) return;
	
	renderBackend->Init();

	if (renderConfig.iconPath != "") {
		LoadWindowIcon(renderConfig.iconPath);
	}
	
}

void RenderSystem::Reinit( void ) {
	if (renderBackend == nullptr) return;
	
	renderBackend->Reinit();
}

void RenderSystem::FrameStart( void ) {
	if (renderBackend == nullptr) return;
	
	renderBackend->FrameStart();
}

void RenderSystem::FrameEnd( void ) {
	if (renderBackend == nullptr) return;
	
	renderBackend->FrameEnd();
}

void RenderSystem::Exit( void ) {
	if (renderBackend == nullptr) return;
	
	renderBackend->Exit();
}

/*------------------------------------------------------------------------------
	Shaders
--------------------------------------------------------------------------------
	Just about every modern graphics API uses some form of shaders.
	This is the API to load and use them.
------------------------------------------------------------------------------*/
void RenderSystem::LoadShader(const std::string& shaderName ) {
	if (renderBackend == nullptr) return;
	
	renderBackend->LoadShader( shaderName );
}

void RenderSystem::UseShader(const std::string& shaderName ) {

}

void RenderSystem::ShaderPushTexture() {

}

void RenderSystem::ShaderPushMatrix() {

}

void RenderSystem::ShaderPushVec4() {

}

void RenderSystem::ShaderPushVec3() {

}

void RenderSystem::ShaderPushVec2() {

}

void RenderSystem::ShaderPushFloat() {

}

void RenderSystem::ShaderPushInt() {

}

/*------------------------------------------------------------------------------
	Events
--------------------------------------------------------------------------------
	Hooks into the SDL Event system allowing the programmer to easily add
	callbacks.
------------------------------------------------------------------------------*/

void RenderSystem::AddEventHook( RenderEventHook hook ) {
	hooks.push_back(hook);
}

void RenderSystem::Events( void ) {
	while (SDL_PollEvent(&renderData.event) !=0 ) {
		if (renderData.event.type == SDL_QUIT) {
			renderData.active = false;
		}

		for (auto hook : hooks) {
			hook(renderData.event);
		}
	}
}

/*------------------------------------------------------------------------------
	Utility
--------------------------------------------------------------------------------
	Various utility functions.
------------------------------------------------------------------------------*/

void RenderSystem::LoadWindowIcon( std::string path ) {
	int width, height, channels;

	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);

	if (!pixels) {
		std::cerr << "Unable to load window icon!" << std::endl;
		return;
	}

	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif

	SDL_Surface* iconSurf = SDL_CreateRGBSurfaceFrom( pixels, width, height, 32, width * 4,
		rmask, gmask, bmask, amask );

	if (iconSurf) {
		SDL_SetWindowIcon( renderData.window, iconSurf );
		SDL_FreeSurface( iconSurf );
	}

}