
#include <iostream>
//Lib
#include "UIManager\File.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"

//CallBacks
void onCreate(HWND hwnd);
void onDestroy(HWND hwnd);
void onButtonClick(HWND object);
void onButtonDoubleClick(HWND object);
void onButtonHover(HWND object);
void onButtonEndHover(HWND object);
void onTextChange(HWND object, std::string text);

void onExit(HWND object);
void onMinimize(HWND object);

//Objects
UIManager::WindowManager window;
UIManager::View textView;
UIManager::View button;
UIManager::View editText;
UIManager::View pictureBox;

UIManager::View imageButton; //Exit
UIManager::View imageButton1; //Minimize

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 240, 120);
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
	window.setTransparentKeyColor(HEX("#484848"));
	//TextBox1
	textView = UIManager::View(UIManager::TextView, 100, 100);
	textView.setText("This is a message");
	textView.setTextColor(RGB(255, 255, 255));
	window.addView(textView);
	//ImageButton
	imageButton = UIManager::View(UIManager::PictureBox, 791, 53);
	imageButton.setPictureRessource(UIManager::BitMap("u.bmp"));
	imageButton.setOnClick(onExit);
	window.addView(imageButton);
	//ImageButton1
	imageButton1 = UIManager::View(UIManager::PictureBox, 770, 53);
	imageButton1.setPictureRessource(UIManager::BitMap("m.bmp"));
	imageButton1.setOnClick(onMinimize);
	window.addView(imageButton1);
	//Button1
	button = UIManager::View(UIManager::Button);
	button.setText("Click here");
	button.setLocation(70, 190);
	button.setOnClick(onButtonClick);
	button.setOnCursorEnter(onButtonHover);
	button.setOnCursorLeave(onButtonEndHover);
	button.setOnDoubleClick(onButtonDoubleClick);
	window.addView(button);
	//EditText1
	UIManager::InputRule rule;
	rule.numbersOnly = true;
	rule.charLimit = 7;
	editText = UIManager::View(UIManager::EditText);
	editText.setText("Prueba");
	editText.setInputRule(rule);
	editText.setTextMargin(UIManager::ViewLoc::Center);
	editText.setLocation(70, 120);
	editText.setOnTextChange(onTextChange);
	window.addView(editText);
}

void onButtonHover(HWND object) {
	button.setText("Mouse In!");
}

void onButtonEndHover(HWND object) {
	button.setText("Mouse Out!");
}

void onButtonClick(HWND object) {
	button.setText("Clicked!");
}

void onButtonDoubleClick(HWND object) {
	button.setText("Double Clicked!");
}


void onTextChange(HWND object, std::string text) {
	//MessageBox(0, text.c_str(), "see U", MB_OK);
}

void onExit(HWND object)
{
	window.destroy();
}

void onMinimize(HWND object)
{
	window.minimize();
}

void onDestroy(HWND hwnd) {
	MessageBox(0, "Bye!", "see U", MB_OK);
}
