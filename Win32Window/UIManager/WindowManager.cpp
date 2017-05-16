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

#include "WindowManager.h"

CallBack UIManager::WindowManager::onCreate;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Private
//
void UIManager::WindowManager::createView()
{
	//Create Window
	hwnd = CreateWindowEx(
		0,
		this->wiName.c_str(),			/* Title Class */
		this->wiName.c_str(),			/* Title Text */
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE | WS_OVERLAPPEDWINDOW,							/* Initial Flags */
		startX,							/* X Start */
		startY,							/* Y Start */
		endX,							/* The programs width */
		endY,							/* and height in pixels */
		HWND_DESKTOP,					/* The window is a child-window to desktop */
		NULL,							/* No menu */
		hInstance,						/* Program Instance handler */
		NULL
	);

	//Messages Manage
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

//Public
//
UIManager::WindowManager::WindowManager(HINSTANCE & hInstance, std::string wiName, int startX, int startY, int endX, int endY)
{
	this->wiName = wiName;
	this->hInstance = hInstance;
	this->startX = startX;
	this->startY = startX;
	this->endX = endX;
	this->endY = endY;
}

void UIManager::WindowManager::setText(std::string text)
{
	wiName = text;
}

void UIManager::WindowManager::setLocation(int xloc, int yloc)
{
	startX = xloc;
	startY = yloc;
}

void UIManager::WindowManager::setSize(int xsize, int ysize)
{
	endX = xsize;
	endY = ysize;
}

void UIManager::WindowManager::build(CallBack callback)
{
	//Set Callback
	if (callback != NULL)
		onCreate = callback;
	//Create Class
	winClass.cbSize = sizeof(winClass);
	winClass.hInstance = hInstance;
	winClass.lpszClassName = this->wiName.c_str();
	winClass.lpfnWndProc = WndProc; //Execution callback
	//Load default editable ellements
	winClass.hCursor = LoadCursor(0, IDC_ARROW);		/*Default*/
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	/*Default*/		//Alt+Tab Dialog
	winClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	winClass.lpszMenuName = NULL;						/* No menu */
	RegisterClassEx(&winClass);

	//Create Window
	createView();
}

void UIManager::WindowManager::show()
{
	
}

void UIManager::WindowManager::hide()
{
}


LRESULT CALLBACK UIManager::WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE: //On Window Create
	{
		onCreate(hwnd);
		break;
	}

	case WM_COMMAND:
	{
		//Por ahora no hay que tocar aquí
		break;
	}

	case WM_DESTROY:
	{
		//Aquí se destruye el form
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}