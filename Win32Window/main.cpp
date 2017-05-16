#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"
//Views
#include "UIManager\Views\TextView.h"

//CallBacks
void onCreate(HWND hwnd);

//If you want access
UIManager::WindowManager *manager;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UIManager::WindowManager window = UIManager::WindowManager(hInstance, "Prueba de Ventana", 100, 100);
	manager = &window;
	window.setSize(400, 500);
	window.setTopMost(true);
	window.build(onCreate);
}

void onCreate(HWND hwnd) {
	//Stuff that can be done previous to the build too

	//Execute shitty stuff
	//MessageBox(0, "Mensaje de Bienvenida", "Título del mensaje", MB_OK);
	//Add views
	UIManager::TextView textView1;
	textView1.setText("Esto es un mensaje");
	textView1.setLocation(50, 50);
	textView1.setSize(150, 25);
	CreateWindowW(L"Static", L"Esto es un mensaje",
		WS_CHILD | WS_VISIBLE,
		50, 50, 150, 25,
		hwnd, (HMENU)1, NULL, NULL);
}
