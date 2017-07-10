
//#include <windows.h>
#include <iostream>
//Lib
#include "UIManager\File.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

#define _LEGACY_UI

//CallBacks
void onCreate(HWND hwnd);
void onDestroy(HWND hwnd);
void onButtonClick(HWND object);
void onButtonHover(HWND object);
void onButtonEndHover(HWND object);
void onTextChange(HWND object, std::string text);

//Objects
UIManager::WindowManager window;
UIManager::View textView;
UIManager::View button;
UIManager::View editText;
UIManager::View pictureBox;
UIManager::View imageButton;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(850, 520);
	window.allowResize(false);
	window.disallowTitleBar(true);
	window.allowDragAndMove(true);
	window.allowMaximizeButton(false);
	//Callbacks
	window.setOnCreate(onCreate);
	window.setOnDestroy(onDestroy);
	window.build();
}

void onCreate(HWND hwnd) {
	//Background
	pictureBox = UIManager::View(UIManager::PictureBox, 0, 0);
	pictureBox.setPictureRessource(UIManager::BitMap("bg.bmp"));
	window.addView(pictureBox);
	window.setTransparentKeyColor(RGB(72, 72, 72));
	//TextBox1
	textView = UIManager::View(UIManager::TextView, 100, 100);
	textView.setText("This is a message");
	textView.setTextColor(RGB(255, 255, 255));
	window.addView(textView);
	//ImageButton
	imageButton = UIManager::View(UIManager::ImageButton, 793, 55, 18, 19);
	imageButton.setText("xd");
	imageButton.setPictureRessource(UIManager::BitMap("u.bmp"));
	window.addView(imageButton);
	//Button1
	button = UIManager::View(UIManager::Button);
	button.setText("Click here");
	button.setLocation(70, 190);
	button.setOnClick(onButtonClick);
	button.setOnCursorEnter(onButtonHover);
	button.setOnCursorLeave(onButtonEndHover);
	window.addView(button);
	//EditText1
	editText = UIManager::View(UIManager::EditText);
	editText.setText("Prueba");
	editText.setLocation(70, 120);
	editText.setOnTextChange(onTextChange);
	window.addView(editText);

	HWND ss = CreateWindowW(L"Button", L"xD",
		WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		120, 250, 100, 40,
		hwnd, (HMENU)111, NULL, NULL);
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = hwnd;
	tme.dwHoverTime = 5000;
	bool resukt = TrackMouseEvent(&tme);
	std::string xd = "xd";

}

void onButtonHover(HWND object) {
	button.setText("Mouse In!");
}

void onButtonEndHover(HWND object) {
	button.setText("Mouse Out!");
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
