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

wCreateCallBack UIManager::WindowManager::onCreate;
wFocusCallBack UIManager::WindowManager::onFocus;
wDestroyCallBack UIManager::WindowManager::onDestroy;
wPersonalizedCallBack UIManager::WindowManager::onMessageRec;

HWND UIManager::WindowManager::wHWND;
std::vector<vObject> UIManager::WindowManager::vObjects;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Private
//
void UIManager::WindowManager::createView()
{
	//Create Window
	this->wCreated = true;
	wHWND = CreateWindowEx(
		ExwFlags,
		this->wiName.c_str(),			/* Title Class */
		this->wiName.c_str(),			/* Title Text */
		wFlags,							/* Initial Flags */
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
UIManager::WindowManager::WindowManager() : hInstance(NULL)
{
}

void UIManager::WindowManager::setInitialData(HINSTANCE & hInstance, std::string wiName, int startX, int startY, int endX, int endY)
{
	this->wiName = wiName;
	this->hInstance = hInstance;
	this->startX = startX;
	this->startY = startX;
	this->endX = endX;
	this->endY = endY;
}

void UIManager::WindowManager::setHInstance(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
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
	if (wCreated) {
		SetWindowPos(wHWND, 0, 0, 0, xsize, ysize, SWP_NOMOVE);
	} else {
		endX = xsize;
		endY = ysize;
	}
}

void UIManager::WindowManager::setVisible(bool visible)
{
	if (!wCreated) {
		if (visible) {
			wFlags = wFlags | WS_VISIBLE;
		} else {
			wFlags = wFlags & ~WS_VISIBLE;
		}
	}
}

void UIManager::WindowManager::setStartState(UIManager::wStartState state)
{
	switch(state) {
		case UIManager::Maximized: {
			wFlags = wFlags | WS_MAXIMIZE;
			break;
		}
		case UIManager::Minimized: {
			wFlags = wFlags | WS_MINIMIZE;
			break;
		}
		default: {
			break;
		}
	}
}

void UIManager::WindowManager::setCursor(HCURSOR cursor)
{
	wCursor = cursor;
}

void UIManager::WindowManager::setIcon(HICON icon)
{
	wIcon = icon;
}

void UIManager::WindowManager::setBackGround(HBRUSH brush)
{
	wbColor = brush;
}

void UIManager::WindowManager::allowMaximizeButton(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_MAXIMIZEBOX;
		}
		else {
			wFlags = wFlags & ~WS_MAXIMIZEBOX;
		}
	}
}

void UIManager::WindowManager::allowMinimizeButton(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_MINIMIZEBOX;
		}
		else {
			wFlags = wFlags & ~WS_MINIMIZEBOX;
		}
	}
}

void UIManager::WindowManager::allowResize(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_THICKFRAME;
		}
		else {
			wFlags = wFlags & ~WS_THICKFRAME;
		}
	}
}

void UIManager::WindowManager::setTopMost(bool active)
{
	if (!wCreated) {
		if (active) {
			ExwFlags = ExwFlags | WS_EX_TOPMOST;
		}
		else {
			ExwFlags = ExwFlags & ~WS_EX_TOPMOST;
		}
	}
}

void UIManager::WindowManager::setOnCreate(wCreateCallBack callback)
{
	onCreate = callback;
}

void UIManager::WindowManager::setOnFocus(wFocusCallBack callback)
{
	onFocus = callback;
}

void UIManager::WindowManager::setOnDestroy(wDestroyCallBack callback)
{
	onDestroy = callback;
}

void UIManager::WindowManager::setPersonalizedHandler(wPersonalizedCallBack callback)
{
	onMessageRec = callback;
}

void UIManager::WindowManager::build()
{
	//Create Class
	winClass.cbSize = sizeof(winClass);
	winClass.hInstance = hInstance;
	winClass.lpszClassName = this->wiName.c_str();
	winClass.lpfnWndProc = WndProc; //Execution callback
	//Load default editable ellements
	winClass.hCursor = wCursor;		/*Default*/
	winClass.hIcon = wIcon;								/*Alt+Tab Dialog*/
	winClass.hbrBackground = wbColor;
	winClass.lpszMenuName = NULL;						/* No menu */
	RegisterClassEx(&winClass);

	//Create Window
	createView();
}

void UIManager::WindowManager::addView(UIManager::View view)
{
	vObject object;
	object.view = view;
	std::string type = vh::getView(view.vType);
	object.manager = CreateWindowW(FormatFactory::StringToWString(type).c_str(), FormatFactory::StringToWString(view.vText).c_str(),
		WS_CHILD | WS_VISIBLE,
		view.startX, view.startY, view.endX, view.endY,
		wHWND, (HMENU)vObjects.size(), NULL, NULL);
	vObjects.push_back(object);
}

LRESULT CALLBACK UIManager::WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE: //On Window Create
	{
		wHWND = hwnd;
		if (onCreate != NULL)
			onCreate(hwnd);
		break;
	}
	case WM_COMMAND: //Command execution
	{
		vObject object = vObjects.at(wParam);
		if (object.view.onClick != NULL)
			object.view.onClick(object.manager);
		break;
	}
	case WM_SETFOCUS: //Get Focus
	{
		if (onFocus != NULL)
			onFocus(hwnd, true);
		break;
	}
	case WM_KILLFOCUS: //Lost Focus
	{
		if (onFocus != NULL)
			onFocus(hwnd, false);
		break;
	}
	case WM_DESTROY: //Form Destroyed
	{
		if (onDestroy != NULL)
			onDestroy(hwnd);
		PostQuitMessage(0);
		break;
	}
	}
	if (onMessageRec != NULL)
		onMessageRec(hwnd, msg, wParam, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}