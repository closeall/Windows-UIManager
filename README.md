# About the project
This project has been made with the idea of simplifying the creation of any kind of form in windows with the help of the Win32Api
This is an alpha version of the project wich will serve to determinate the structure of the proyect.
At this time, it only allows creating a form and TextView/Buttons but I hope to add more functionalities in the future.

# How to use it!
This project is really easy to implement and you can get a full form with less than 25 lines of code.
First of all, we need to add the header files in our project, I recommend copying the "UIManager" folder to the project and then insert all the libs:
```c++
#include <windows.h>
#include <iostream>
//Actual Project Libs
#include "UIManager\Interface.h"
#include "UIManager\WindowManager.h"
#include "UIManager\View.h"
```
Then, in the main file we need to create a main function using the default windows api like this:
```c++
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//Our code will go here
}
```
Now, we need to declarate the window form and give it the values we want for it. There are a lot of properties and each one has more than one way to be implemented so I sugest to use the most you like.
```c++
UIManager::WindowManager window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Test Window");
	window.setLocation(200, 100);
	window.setSize(400, 480);
	//....
}
```
Then we need to add the functions(call them whatever you want) that will be called when a certain state happen. By Example, creating the form.
It actually have 3 states as default{OnCreate, OnFocus, OnDestroy} but you can add a personalized one by reciving all the WndProc with "setPersonalizedHandler"
```c++
void onCreate(HWND hwnd) {
	//....
}

UIManager::WindowManager window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Test Window");
	window.setLocation(200, 100);
	window.setSize(400, 480);
	//Callbacks
	window.setOnCreate(onCreate);
	window.build(); //Finaly build, Always at the end of the function to prevent stuck on execution
}
```
Finally, we now should create our object from inside the form when the onCreate is Called. You can create your own personalized object using the provided hwnd
```c++
void onCreate(HWND hwnd) {
	//TextBox1
	UIManager::View textView = UIManager::View(UIManager::TextView);
	textView.setText("Esto es un mensaje");
	window.addView(textView);
}
```

# Examples:
Now a Full Example of a window with TopMost, that starts minimized, don't have any minimize/maximize buttons, say "Bye" when closed and cannot be resized which have a text and a button inside that say "Hello" when pressed
```c++
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

//1# Start
UIManager::WindowManager window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.setInitialData(hInstance, "Ventana de Prueba", 200, 100);
	window.setSize(400, 480);
	window.setTopMost(true);
	window.allowMaximizeButton(false);
	window.allowMinimizeButton(false);
	window.setStartState(UIManager::Minimized);
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
```
