/*------------------------------------------------------------------------------
    Render.h
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.21
--------------------------------------------------------------------------------
	RenderSystem definition. Handles core rending logic.
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
#ifndef __render_h__
#define __render_h__

#include "RenderCommon.h"
#include "PolyList.h"
#include "RenderBackendOpenGL4.h"

using RenderEventHook = void(*)(SDL_Event event);

namespace RenderSystem {

	inline static std::unique_ptr<RenderBackend> renderBackend;
	inline static std::vector<RenderEventHook> hooks;

	void Init( std::unique_ptr<RenderBackend> backend );
	void Reinit( void );

	void FrameStart( void );
	void FrameEnd( void );

	void Exit( void );

/*------------------------------------------------------------------------------
	Texture
------------------------------------------------------------------------------*/
	bool Exists( const Texture& tex );
	void LoadTexture( const std::string name, const std::string path );
	void UseTexture( const std::string name );
	void FreeTexture( const std::string name );
	void FreeAllTextures();

/*------------------------------------------------------------------------------
	Geometry
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
	Shaders
------------------------------------------------------------------------------*/
	void LoadShader(const std::string& shaderName );
	void UseShader(const std::string& shaderName );
	void FreeShader(const std::string& shaderName );
 	void FreeAllShaders();

	void ShaderPushMatrix();
	void ShaderPushVec4();
	void ShaderPushVec3();
	void ShaderPushVec2();
	void ShaderPushFloat();
	void ShaderPushInt();

/*------------------------------------------------------------------------------
	Events
------------------------------------------------------------------------------*/
	void AddEventHook( RenderEventHook hook );

	void Events( void );
/*------------------------------------------------------------------------------
	Utility
------------------------------------------------------------------------------*/
	void LoadWindowIcon( std::string path );
	
};


#endif
