/*Copyright 2017 Onelio

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#ifndef _UI_MANAGER_VIEW_HEADER
#define _UI_MANAGER_VIEW_HEADER

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Namespace.h"
#include "Interface.h"

enum UIManager::ViewType { TextView, EditText, PictureBox, Button, ListBox, ComboBox };

class UIManager::View {
	friend class WindowManager;
private:
	UIManager::ViewType vType;
	HWND vHWND;
	int vId;
	DWORD vFlags = WS_CHILD | WS_VISIBLE;
	std::string vText;
	HBITMAP vBitMap;
	HFONT hFont;
	std::string vFont = "Segoe UI";
	COLORREF vFontColor = RGB(250,250,250);
	int vFontSize = 13;
	int startX;
	int startY;
	int endX;
	int endY;
	bool vCreated = false;
	bool vEnabled = true;
	void updateFont();
	//Callback
	//
	static std::vector<vOnClick> onClick;
	static std::vector<vOnTextChange> onTextChange;
public:
	View();
	View(UIManager::ViewType view, int startX = 50, int startY = 50, int endX = 150, int endY = 25);
	void setType(UIManager::ViewType view);
	void setText(std::string text);
	void setLocation(int xloc, int yloc);
	void setSize(int xsize, int ysize);
	void setEnabled(bool enabled);
	void setTextFont(std::string fname);
	void setTextSize(int size);
	void setTextColor(int r, int g, int b);
	void setPictureBoxRessource(HBITMAP bitmap);
	std::string getText();
	//Others
	void setOnClick(vOnClick callback);
	void setOnTextChange(vOnTextChange callback);
};

#endif //#define _UI_MANAGER_VIEW_HEADER