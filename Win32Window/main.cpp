#include <windows.h>

#include "WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UIManager::WindowManager window = UIManager::WindowManager(hInstance);
	window.show();
}
