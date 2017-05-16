/*Copyright 2017 Ricardo Moya Mejias

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#ifndef _UI_MANAGER_VIEW_TEXT_VIEW_HEADER
#define _UI_MANAGER_VIEW_TEXT_VIEW_HEADER

#include <Windows.h>
#include <iostream>
#include <string>

#include "..\Namespace.h"
#include "..\Interface.h"

class UIManager::TextView {
private:
	//Class data
	HWND hwnd;
	//Object Data
	std::string type = "Static";
	std::string oName;
	int startX;
	int startY;
	int endX;
	int endY;
public:
	//Public Functions
	TextView();
	TextView(std::string text, int xloc = 0, int yloc = 0);
	void setText(std::string text);
	void setLocation(int xloc, int yloc);
	void setSize(int xsize, int ysize);
	std::string getType();
	std::string getText();
	int getXLoc();
	int getYLoc();
	int getXSize();
	int getYSize();
};

#endif //#define _UI_MANAGER_VIEW_TEXT_VIEW_HEADER