#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

//3# Create Window CallBacks
void onCreate(HWND hwnd);
void onFocus(HWND hwnd, bool focused);
void onDestroy(HWND hwnd);

//1# Global(or not) reference for access from inside childs with Manager control
UIManager::WindowManager window;
//2# Define Window data
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(400, 480);
	//Callbacks
	window.setOnCreate(onCreate);
	window.setOnFocus(onFocus);
	window.setOnDestroy(onDestroy);
	window.build(); //Build always at the end of the int to prevent stuck on execution
}

//4# Add views one by one or in a list
void onCreate(HWND hwnd) {
	//TextBox1
	UIManager::View textView = UIManager::View(UIManager::TextView);
	textView.setText("Esto es un mensaje");
	window.addView(textView);
	//TextBox2
	UIManager::View textView1 = UIManager::View(UIManager::TextView);
	textView1.setText("Hola Erni");
	textView1.setLocation(70, 70);
	window.addView(textView1);
}

void onFocus(HWND hwnd, bool focused) {
	if (focused) {
		//Do stuff on focused....
	}
}

void onDestroy(HWND hwnd) {
	MessageBox(0, "Good Bye!", "see U", MB_OK);
}
