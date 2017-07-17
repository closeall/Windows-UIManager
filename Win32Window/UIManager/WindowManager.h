/*Copyright 2017 Onelio

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

//Win7 Style
#ifndef _LEGACY_UI
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' " "version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#endif

#define UIMANAGER_VERSION 12
#define _AFXDLL
#include <SDKDDKVer.h>
#include <afxwin.h>
#include <commctrl.h>
//#include <Windows.h>
//#include <Windowsx.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include "Namespace.h"
#include "Interface.h"
#include "View.h"

#include "Util\FormatFactory.h"
#include "Util\ViewHandler.h"
#include "Util\Drawer.h"

//typedef HWND HWND;
COLORREF HEX(std::string color);
enum UIManager::StartState { Normal, Maximized, Minimized};
struct vObject{
	HWND manager;
	UIManager::View *view;
};

class UIManager::WindowManager {
private:
	//Class data
	HINSTANCE hInstance;
	WNDCLASSEX winClass; /* Data structure for the windowclass */
	MSG msg;
	static HWND wHWND;
	static std::vector<vObject> vObjects;
	bool wCreated = false;
	//Window Data
	std::string wiName;
	DWORD ExwFlags;
	DWORD wFlags = WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | BS_NOTIFY;
	HCURSOR wCursor = LoadCursor(0, IDC_ARROW);
	HICON wIcon = LoadIcon(NULL, IDI_APPLICATION);
	DWORD wClassStyle;
	HBRUSH wbColor;
	int startX;
	int startY;
	int endX;
	int endY;
	static bool wDragAndMove;
	static int wObjHover;
	//Private functions
	void createView();
	static int viewLocByRef(LPARAM hwnd);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//Callback
	//
	static wLeftClickCallBack onLeftClick;
	static wRightClickCallBack onRightClick;
	static wMiddleClickCallBack onMiddleClick;
	static wCreateCallBack onCreate;
	static wFocusCallBack onFocus;
	static wDestroyCallBack onDestroy;
	static wPersonalizedCallBack onMessageRec;
public:
	//Creation Functions
	//
	WindowManager();
	//Window
	void setInitialData(HINSTANCE & hInstance, std::string wiName = "Window Name", int startX = 300, int startY = 200, int endX = 120, int endY = 400);
	void setHInstance(HINSTANCE hInstance);
	void setText(std::string text);
	void setLocation(int xloc, int yloc);
	void setSize(int xsize, int ysize);
	void setVisible(bool visible);
	void setEnabled(bool enabled);
	void setTopMost(bool active);
	void setStartState(UIManager::StartState state);
	void setFocusable(bool focusable);
	void makeTop();
	void makeBottom();
	//Borders & Tool Bar
	void setCursor(HCURSOR cursor);
	void setIcon(HICON icon);
	void setBackground(HBRUSH brush);
	void setBackground(HBITMAP brush);
	void allowMaximizeButton(bool allow);
	void allowMinimizeButton(bool allow);
	void allowResize(bool allow);
	void disallowTitleBar(bool allow);
	void allowDragAndMove(bool allow);
	void setTransparentKeyColor(COLORREF color);
	void setAlpha(int percent); //100 -> 0
	void inflateShadow();
	void UIM_VERSION(); //Get Code Version
	//Others
	void setOnLeftClick(wLeftClickCallBack callback = NULL);
	void setOnRightClick(wRightClickCallBack callback = NULL);
	void setOnMiddleClick(wMiddleClickCallBack callback = NULL);
	void setOnCreate(wCreateCallBack callback = NULL);
	void setOnFocus(wFocusCallBack callback = NULL);
	void setOnDestroy(wDestroyCallBack callback = NULL);
	void setPersonalizedHandler(wPersonalizedCallBack callback = NULL);
	void build();
	void minimize();
	void destroy();
	HWND getHWND();
	//Runtime Functions
	//
	void addView(UIManager::View &view);
};

#endif //#define _UI_MANAGER_WINDOW_MANAGER_HEADER