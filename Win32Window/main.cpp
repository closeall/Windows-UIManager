#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

//3# Create Window CallBacks
void onCreate(HWND hwnd);
void onDestroy(HWND hwnd);
//View
void onButtonClick(HWND object);

//1# Global(or not) reference for access from inside childs with Manager control
UIManager::WindowManager window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(400, 480);
	window.allowResize(false);
	//Callbacks
	window.setOnCreate(onCreate);
	window.setOnDestroy(onDestroy);
	window.build();
}

void onCreate(HWND hwnd) {
	//TextBox1
	UIManager::View textView = UIManager::View(UIManager::TextView);
	textView.setText("This is a message");
	window.addView(textView);
	//Button1
	UIManager::View button = UIManager::View(UIManager::Button);
	button.setText("Click here");
	button.setLocation(70, 70);
	button.setOnClick(onButtonClick);
	window.addView(button);
}

void onButtonClick(HWND object) {
	MessageBox(0, "Hello", "Message", MB_OK);
}

void onDestroy(HWND hwnd) {
	MessageBox(0, "Bye!", "see U", MB_OK);
}
