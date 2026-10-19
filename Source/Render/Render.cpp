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

void RenderSystem::Init( std::unique_ptr<RenderBackend> backend ) {

	if (backend != nullptr) {
		renderBackend = std::move(backend);
	} else {
		std::cerr << "Render backend was nullptr!" << std::endl;
		return;
	}

	if (renderBackend != nullptr) {
		renderBackend->Init();
	}
}

void RenderSystem::Reinit( void ) {
	if (renderBackend != nullptr) {
		renderBackend->Reinit();
	}
}

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

void RenderSystem::FrameStart( void ) {
	if (renderBackend != nullptr) {
		renderBackend->FrameStart();
	}
}

void RenderSystem::FrameEnd( void ) {
	if (renderBackend != nullptr) {
		renderBackend->FrameEnd();
	}
}

void RenderSystem::Exit( void ) {
	if (renderBackend != nullptr) {
		renderBackend->Exit();
	}
}