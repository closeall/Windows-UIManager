#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"

//CallBacks
void onCreate(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UIManager::WindowManager window = UIManager::WindowManager(hInstance, "Prueba de Ventana", 100, 100);
	window.setSize(400, 500);
	window.build(onCreate);
}

void onCreate(HWND hwnd) {
	//Execute shitty stuff
	MessageBox(0, "Mensaje de Bienvenida", "Título del mensaje", MB_OK);
	//Add views
	CreateWindowW(L"Static", L"Esto es un mensaje",
		WS_CHILD | WS_VISIBLE,
		50, 50, 150, 25,
		hwnd, (HMENU)1, NULL, NULL);
}
