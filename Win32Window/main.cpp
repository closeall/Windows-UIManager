#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"

//Window object
//UIManager::WindowManager window;
//CallBacks
CallBack UIManager::WindowManager::onCreate;
void onCreate();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UIManager::WindowManager window = UIManager::WindowManager(hInstance, "Prueba de Ventana", 100, 100);
	window.setSize(400, 500);
	window.build(std::bind(onCreate));
}

void onCreate() {
	//Execute shitty stuff
	MessageBox(0, "Mensaje de Bienvenida", "Título del mensaje", MB_OK);
	//Add views
	/*CreateWindowW(L"Static", L"Esto es un mensaje",
		WS_CHILD | WS_VISIBLE,
		50, 50, 150, 25,
		window.getHWND, (HMENU)1, NULL, NULL);*/
}
