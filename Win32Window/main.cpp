
#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\File.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

//CallBacks
void onCreate(HWND hwnd);
void onDestroy(HWND hwnd);
void onButtonClick(HWND object);
void onTextChange(HWND object, std::string text);

//Objects
UIManager::WindowManager window;
UIManager::View textView;
UIManager::View button;
UIManager::View editText;
UIManager::View pictureBox;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(400, 480);
	window.allowResize(false);
	window.disallowTitleBar(true);
	window.allowDragAndMove(true);
	//Callbacks
	window.setOnCreate(onCreate);
	window.setOnDestroy(onDestroy);
	window.build();
}

void onCreate(HWND hwnd) {
	//TextBox1
	textView = UIManager::View(UIManager::TextView);
	textView.setText("This is a message");
	window.addView(textView);
	//Button1
	button = UIManager::View(UIManager::Button);
	button.setText("Click here");
	button.setLocation(70, 80);
	button.setOnClick(onButtonClick);
	window.addView(button);
	//EditText1
	editText = UIManager::View(UIManager::EditText);
	editText.setText("Prueba");
	editText.setLocation(70, 120);
	editText.setOnTextChange(onTextChange);
	window.addView(editText);
	//PictureBox1
	pictureBox = UIManager::View(UIManager::PictureBox, 70, 160, 300, 300);
	pictureBox.setPictureBoxRessource(UIManager::BitMap("header.bmp"));
	window.addView(pictureBox);
	window.setTransparentKeyColor(RGB(255, 0, 0));
}

void onButtonClick(HWND object) {
	//window.test();
	button.setText("Clicked!");
	button.setEnabled(false);
	//button.setTextFont("Chiller");
	//button.setTextSize(15);
	textView.setText("ola k ase");
}

void onTextChange(HWND object, std::string text) {
	MessageBox(0, text.c_str(), "see U", MB_OK);
}

void onDestroy(HWND hwnd) {
	MessageBox(0, "Bye!", "see U", MB_OK);
}
