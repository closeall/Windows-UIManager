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

#ifndef _UI_MANAGER_NAMESPACE_WINDOW_MANAGER
#define _UI_MANAGER_NAMESPACE_WINDOW_MANAGER

#include <Windows.h>
#include "Namespace.h"
#include <iostream>
#include <string>

class UIManager::WindowManager {
private:
	//Class data
	HINSTANCE hInstance;
	WNDCLASSEX winClass; /* Data structure for the windowclass */
	MSG msg;
	HWND hwnd;
	//Window Data
	LPCSTR wiName;
	int startX = 250;
	int startY = 150;
	int endX = 544;
	int endY = 375;
public:
	WindowManager(HINSTANCE & hInstance, std::string wiName = "Window Name");
	void setLocation(int xloc, int yloc);
	void setSize(int xsize, int ysize);
	void show();
};

#endif //#define _UI_MANAGER_NAMESPACE_WINDOW_MANAGER