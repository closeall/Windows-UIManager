#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

//CallBacks
void onCreate(HWND hwnd);
void onFocus(HWND hwnd, bool focused);
void onDestroy(HWND hwnd);

//Global or reference for access from inside childs with Manager control
UIManager::WindowManager window;
//Define Window data
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(400, 480);
	//Callbacks
	window.setOnCreate(onCreate);
	window.setOnFocus(onFocus);
	window.setOnDestroy(onDestroy);
	window.build(); //Build always at the end of the int
}

void onCreate(HWND hwnd) {
	//Add views
	UIManager::View textView = UIManager::View(UIManager::TextView);
	textView.setText("Esto es un mensaje");
	CreateWindowW(L"Static", L"Esto es un mensaje",
		WS_CHILD | WS_VISIBLE,
		50, 50, 150, 25,
		hwnd, (HMENU)1, NULL, NULL);
}

void onFocus(HWND hwnd, bool focused) {
	if (focused) {
		//MessageBox(0, "Hello!", "I see U", MB_OK);
	}
}

void onDestroy(HWND hwnd) {
	MessageBox(0, "Good Bye!", "I see U", MB_OK);
}
