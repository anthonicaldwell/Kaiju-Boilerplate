/*------------------------------------------------------------------------------
    PolyList.h
--------------------------------------------------------------------------------
	Date Created: 2026.10.20
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
#ifndef __poly_list_h__
#define __poly_list_h__

#include "RenderCommon.h"

typedef struct PolyList3D_s {
	std::vector<Vec3> pos;
	std::vector<Vec3> norms;
	std::vector<Vec2> texCoord; 
	std::vector<int> indices;

	PolyList_s() {}

	void PushVert( const Vec3 v ) { pos.push_back(v); }
	void PushTexCoord( const Vec2 t ) { texCoord.push_back(t); }
	void PushIndex( const int i ) { indices.push_back(i); }
} PolyList3D;

typedef struct PolyList2D_s {

} PolyList2D;

#endif