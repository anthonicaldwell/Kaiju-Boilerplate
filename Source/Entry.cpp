/*------------------------------------------------------------------------------
    Entry.cpp
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.19
--------------------------------------------------------------------------------
	The primary entry point for the application.
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
#include "Common.h"
#include "Assets/Assets.h"
#include "Render/Render.h"
#include "Logic/Logic.h"


void escapeHook(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			renderData.active = false;
		}
	}
}

int main ( int argc, char * argv[] ) {

	// Real configuration backend selection should happen here later via JSON config
	std::unique_ptr<RenderBackend> renderBackend = std::make_unique<RenderBackendOpenGL4>();

	RenderSystem::Init( std::move(renderBackend) );

	RenderSystem::AddEventHook( escapeHook );

	RenderSystem::LoadShader( "Unlit2D" );

	Logic::Init();

	while (renderData.active) {
		RenderSystem::Events();

		Logic::Update();

		RenderSystem::FrameStart();

		Logic::Draw();

		RenderSystem::FrameEnd();
	}

	Logic::Exit();
	RenderSystem::Exit();

	return 0;
}