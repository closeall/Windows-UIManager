
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

//Exit Button
UIManager::View exitButton;
void onExit(HWND object);
void onExitHover(HWND object);
void onExitHoverEnd(HWND object);
//Minimize Button
UIManager::View minimButton;
void onMinimize(HWND object);
void onMinimizeHover(HWND object);
void onMinimizeHoverEnd(HWND object);
//ProgressBar
UIManager::View progress;

//Objects
UIManager::WindowManager window;
UIManager::View textView;
UIManager::View button;
UIManager::View editText;
UIManager::View pictureBox;


UIManager::View customb;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 240, 120);
	window.setSize(850, 520);
	window.setIcon(UIManager::Icon("g.ico"));
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
	//Exit Button
	exitButton = UIManager::View(UIManager::PictureBox, 791, 53);
	exitButton.setPictureRessource(UIManager::BitMap("u.bmp"));
	exitButton.setOnClick(onExit);
	exitButton.setOnCursorEnter(onExitHover);
	exitButton.setOnCursorLeave(onExitHoverEnd);
	window.addView(exitButton);
	//Minimize Button
	minimButton = UIManager::View(UIManager::PictureBox, 770, 53);
	minimButton.setPictureRessource(UIManager::BitMap("m.bmp"));
	minimButton.setOnClick(onMinimize);
	minimButton.setOnCursorEnter(onMinimizeHover);
	minimButton.setOnCursorLeave(onMinimizeHoverEnd);
	window.addView(minimButton);
	//ProgressBar
	progress = UIManager::View(UIManager::ProgressBar, 105, 370);
	progress.setSize(475, 30);
	progress.setProgress(33);
	window.addView(progress);
	//progress.setProgressState(UIManager::ErrorProgress);
	progress.setProgressState(UIManager::UndefinedProgress);
	//TextBox1
	textView = UIManager::View(UIManager::TextView, 100, 100);
	textView.setText("This is a message");
	textView.setTextColor(RGB(255, 0, 0));
	textView.setOnCursorEnter(onButtonHover);
	window.addView(textView);
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
	editText.setMargin(UIManager::ViewMargin::Center);
	editText.setLocation(70, 120);
	editText.setOnTextChange(onTextChange);
	window.addView(editText);
	//Custom one
	customb = UIManager::View(UIManager::CustomButton);
	customb.setLocation(500, 50);
	window.addView(customb);
}

void onButtonHover(HWND object) {
	button.setText("Mouse In!");
}

void onButtonEndHover(HWND object) {
	button.setText("Mouse Out!");
}

void onButtonClick(HWND object) {
	button.setText("Clicked!");
	button.setLocation(70, 220);
	textView.setLocation(190, 100);
	button.setTextFont("Arial");
	button.setTextSize(24);
	button.setTextColor(HEX("#666666"));
	textView.setTextFont("Arial");
	textView.setTextSize(24);
	textView.setTextColor(HEX("#666666"));
	editText.setMargin(UIManager::ViewMargin::Left);
}

void onButtonDoubleClick(HWND object) {
	button.setText("Double Clicked!");
}


void onTextChange(HWND object, std::string text) {
	//MessageBox(0, text.c_str(), "see U", MB_OK);
}

void onExit(HWND object)
{
	exitButton.setPictureRessource(UIManager::BitMap("up.bmp"));
	Sleep(150);
	window.destroy();
}

void onExitHover(HWND object)
{
	exitButton.setPictureRessource(UIManager::BitMap("us.bmp"));
}

void onExitHoverEnd(HWND object)
{
	exitButton.setPictureRessource(UIManager::BitMap("u.bmp"));
}

void onMinimize(HWND object)
{
	minimButton.setPictureRessource(UIManager::BitMap("mp.bmp"));
	Sleep(150);
	window.minimize();
}

void onMinimizeHover(HWND object)
{
	minimButton.setPictureRessource(UIManager::BitMap("ms.bmp"));
}

void onMinimizeHoverEnd(HWND object)
{
	minimButton.setPictureRessource(UIManager::BitMap("m.bmp"));
}

void onDestroy(HWND hwnd) {
}
