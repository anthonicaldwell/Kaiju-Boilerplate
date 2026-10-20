/*------------------------------------------------------------------------------
    Common.h
--------------------------------------------------------------------------------
	Date Created: 2026.10.18
	Date Updated: 2026.10.18
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
#ifndef __common_h__
#define __common_h__

#include <cmath>
#include <cstdint>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

namespace Debug {
	static inline void log(std::string logName, std::string message) {
		std::string logFileName = logName + ".txt";
		std::string fullMessage = "";

		time_t now = time(0);
		tm* ltm = localtime(&now);
		char timeBuf[80] = {};
		strftime(timeBuf, 80, "%Y-%m-%d %H:%M:%S", ltm);

		fullMessage = "[ ";
		fullMessage += timeBuf;
		fullMessage += "] " + message;

		std::ofstream logFile(logFileName, std::ios_base::app);
		logFile << fullMessage << std::endl;
		logFile.close();
	}
}

#endif