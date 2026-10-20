/*------------------------------------------------------------------------------
    RenderCommon.h
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
#ifndef __render_common_h__
#define __render_common_h__

#include "../Common.h"

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
		this->Load("RenderConfig.json");
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

	virtual void LoadShader(const std::string& shaderName ) {}
	virtual void UseShader(const std::string& shaderName ) {}

	virtual void ShaderPushTexture() {}
	virtual void ShaderPushMatrix() {}
	virtual void ShaderPushVec4() {}
	virtual void ShaderPushVec3() {}
	virtual void ShaderPushVec2() {}
	virtual void ShaderPushFloat() {}
	virtual void ShaderPushInt() {}

private:

};

typedef struct Vec2_s {
	float x;
	float y;

	Vec2_s() : x(0.f), y(0.f) {}
	Vec2_s(float x, float y) : x(x), y(y) {}
} Vec2;
 
typedef struct Vec3_s {
	float x;
	float y;
	float z;

	Vec3_s() : x(0.f), y(0.f), z(0.f) {}
	Vec3_s(float x, float y, float z) : x(x), y(y), z(z) {}
} Vec3;

typedef struct Vec4_s {
	float x;
	float y;
	float z;
	float w;

	Vec4_s() : x(0.f), y(0.f), z(0.f), w(1.f) {}
	Vec4_s(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
} Vec4;

typedef struct Rgba_s {
	float r;
	float g;
	float b;
	float a;

	Rgba_s() : r(0.f), g(0.f), b(0.f), a(1.f) {}
	Rgba_s(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
} Rgba;

typedef struct Mat4_s {
	float m[16] = { 1.f, 0.f, 0.f, 0.f,
			  0.f, 1.f, 0.f, 0.f,
			  0.f, 0.f, 1.f, 0.f,
			  0.f, 0.f, 0.f, 1.f };

	Mat4_s() {}

	Mat4_s( float x0, float x1, float x2, float x3,
			float y0, float y1, float y2, float y3,
			float z0, float z1, float z2, float z3,
			float w0, float w1, float w2, float w3 ) {

		m[0] = x0;
		m[1] = x1;
		m[2] = x2;
		m[3] = x3;

		m[4] = y0;
		m[5] = y1;
		m[6] = y2;
		m[7] = y3;

		m[8] = z0;
		m[9] = z1;
		m[10] = z2;
		m[11] = z3;

		m[12] = w0;
		m[13] = w1;
		m[14] = w2;
		m[15] = w3;
	}
} Mat4;

typedef struct Shader_s {
	GLuint vertID;
	GLuint fragID;
	GLuint progID;
	std::string name;

	Shader_s() : vertID(0), fragID(0), name("") {}
} Shader;

#endif