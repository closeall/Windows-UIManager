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

#ifndef _UI_MANAGER_WINDOW_MANAGER_HEADER
#define _UI_MANAGER_WINDOW_MANAGER_HEADER

#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>

#include "Namespace.h"
#include "Interface.h"

class UIManager::WindowManager {
private:
	//Class data
	HINSTANCE hInstance;
	WNDCLASSEX winClass; /* Data structure for the windowclass */
	MSG msg;
	HWND hwnd;
	//Window Data
	std::string wiName;
	int startX;
	int startY;
	int endX;
	int endY;
	//Private functions
	void createView();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	//Private Callback
	static CallBack onCreate;
	//Public Functions
	WindowManager(HINSTANCE & hInstance, std::string wiName = "Window Name", int startX = 300, int startY = 200, int endX = 120, int endY = 400);
	void setText(std::string text);
	void setLocation(int xloc, int yloc);
	void setSize(int xsize, int ysize);
	void build(CallBack callback = NULL);
	HWND getHWND();
	void show();
	void hide();
};

#endif //#define _UI_MANAGER_WINDOW_MANAGER_HEADER