/*------------------------------------------------------------------------------
    RenderTypes.h
--------------------------------------------------------------------------------
	Date Created: 2026.10.21
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
#ifndef __render_types_h__
#define __render_types_h__

#include "../Common.h"
#include "stb_image.h"

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

typedef struct Texture_s {
	size_t rID;
	uint32_t texID;
	std::string name;
	
	int width;
	int height;
	int channels;

	// Would prefer if all loading was in Assets namespace; refactor.
	inline unsigned char* Load(const std::string path) { // !
		return stbi_load( path.c_str(), &width, &height, &channels, 0);
	}

} Texture;

typedef struct Shader_s {
	uint32_t vertID;
	uint32_t fragID;
	uint32_t progID;
	std::string name;

	Shader_s() : vertID(0), fragID(0), name("") {}
} Shader;

#endif