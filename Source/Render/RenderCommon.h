/*------------------------------------------------------------------------------
    RenderCommon.h
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.21
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
#ifndef __render_common_h__
#define __render_common_h__

#include "../Common.h"
#include "RenderTypes.h"

typedef struct RenderData_s {

	bool active;

	SDL_Window * window;
	SDL_GLContext context;
	SDL_Event event;

	RenderData_s() : window(nullptr), context(nullptr), active(true) {}
} RenderData;

typedef struct RenderConfig_s {
	std::string title;
	std::string iconPath;
	
	int windowWidth;
	int windowHeight;
	bool fullscreen;
	int vsync;
	bool resizable;

	RenderConfig_s() 
	: title("Config Not Loaded"), windowWidth(960), windowHeight(540), 
	fullscreen(false), vsync(1), resizable(false) {
		Load("../Config/RenderConfig.json");
	}

	void Load( const std::string& path );	
} RenderConfig;

extern RenderConfig renderConfig;
extern RenderData renderData;

class RenderBackend {
public:
	RenderBackend() {}

	virtual void Init(void) {}
	virtual void Reinit(void) {}

	virtual void FrameStart(void) {}
	virtual void FrameEnd(void) {}
	
	virtual void Exit(void) {}

	// Textures
	virtual bool Exists( const Texture& tex ) { return false; }
	virtual void LoadTexture( const std::string name, const std::string path ) {}
	virtual void UseTexture( const std::string name ) {}
	virtual void FreeTexture( const std::string name ) {}
	virtual void FreeAllTextures() {}

	// Generative Textures
		// Gen Texture( width, height )
		// GenTex.DrawText( )
		// GenTex.Point( )
		// GenTex.Line( )
		// GenTex.Rect( )
		// GenTex.Ellipse( )
		// GenTex.Poly( .. )
		// GenTex.Image( .. )

	// Geometry
		// Load Geometry
		// Push Geometry

	// View
		// Set Perspective
		// Set Orthographic

	// Shaders
	virtual void LoadShader(const std::string& shaderName ) {}
	virtual void UseShader(const std::string& shaderName ) {}
	virtual void FreeShader(const std::string& shaderName ) {}
	virtual void FreeAllShaders() {}

	virtual void ShaderPushMatrix() {}
	virtual void ShaderPushVec4() {}
	virtual void ShaderPushVec3() {}
	virtual void ShaderPushVec2() {}
	virtual void ShaderPushFloat() {}
	virtual void ShaderPushInt() {}

private:

};

#endif