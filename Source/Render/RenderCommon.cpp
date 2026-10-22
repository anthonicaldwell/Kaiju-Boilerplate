/*------------------------------------------------------------------------------
    RenderCommon.cpp
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
#include "RenderCommon.h"

RenderConfig renderConfig;
RenderData renderData;

void RenderConfig_s::Load( const std::string& path ) {
	std::ifstream file(path);

	if (!file.is_open()) {
		Debug::log( "config", "Failed to open RenderConfig.json" );
		return;
	}

	try {
		nlohmann::json j;
		file >> j;

		renderConfig.title = j.value("title","Default");
		renderConfig.iconPath = j.value("icon", "");
		renderConfig.windowWidth = j.value("windowWidth",960);
		renderConfig.windowHeight = j.value("windowHeight",540);
		renderConfig.fullscreen = j.value("fullscreen",false);
		renderConfig.resizable = j.value("resizable",false);
		renderConfig.vsync = j.value("vsync",1);

	} catch (const std::exception& e) {
		std::string logMsg = "Config Error: ";
		logMsg += "\n";
		logMsg += e.what();
		logMsg += "\n";
		
		Debug::log( "config", logMsg );
	}
}