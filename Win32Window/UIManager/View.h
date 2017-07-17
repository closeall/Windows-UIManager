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

#define _AFXDLL
#include <SDKDDKVer.h>
#include <afxwin.h>
#include <iostream>
#include <string>
#include <vector>

#include "Namespace.h"
#include "Interface.h"
#include "Util/Error.h"

enum UIManager::ViewType { TextView, EditText, PictureBox, Button, ImageButton, CustomButton, ListBox, ComboBox, ProgressBar };
enum UIManager::ViewMargin { Left, Right, Center};
enum UIManager::CaseType { Normalcase, Lowercase, Uppercase};
enum UIManager::ProgressState { NormalProgress, ErrorProgress, PausedProgress, UndefinedProgress};

struct UIManager::InputRule {
	int charLimit = 0;
	bool readOnly = false;
	bool passWord = false;
	bool numbersOnly = false;
	bool keepSel = false;
	bool multiLine = false;
	CaseType textCase = Normalcase;
};

class UIManager::View {
	friend class WindowManager;
private:
	UIManager::ViewType vType;
	HWND vHWND;
	HWND wHWND;
	int vId;
	DWORD vFlags = WS_CHILD | WS_VISIBLE;
	std::string vText;
	HBITMAP vBitMap;
	HFONT hFont;
	std::string vFont = DEF_FONT_TYPE;
	COLORREF vFontColor;
	COLORREF vBackColor = HOLLOW_BRUSH;
	int vFontSize = DEF_FONT_SIZE;
	//Edit
	int maxInput = 0;
	//ProgressBar
	int aProgress = 0;
	int mProgress = 100;
	int startX;
	int startY;
	int endX;
	int endY;
	bool vCreated = false;
	bool vEnabled = true;
	void updateFont();
	//Callback
	//
	vOnClick onClick;
	vOnDoubleClick onDoubleClick;
	vOnTextChange onTextChange;
	vOnCursorEnter onCursorEnter;
	vOnCursorLeave onCursorLeave;

	vOnNormalRedraw onNormalRedraw;
	vOnPressRedraw onPressRedraw;
	vOnHoverRedraw onHoverRedraw;
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
	void setBackgroundColor(COLORREF color);
	//Text controls
	void setTextColor(COLORREF color);
	void setMargin(ViewMargin loc);
	//EditText Controls
	void setInputRule(InputRule rule);
	//Picture controls
	void setPictureRessource(HBITMAP bitmap);
	std::string getText();
	//Progressbar controls
	void setProgress(int progress);
	void setProgressMax(int progress);
	void setProgressVertical(bool vertical = true);
	void setProgressState(ProgressState state);
	//Others
	HWND getHWND();
	RECT getSizeRECT();
	int getLeft();
	int getTop();
	int getRight();
	int getBottom();
	void redrawView();
	void setOnClick(vOnClick callback);
	void setOnDoubleClick(vOnDoubleClick callback);
	void setOnCursorEnter(vOnCursorEnter callback);
	void setOnCursorLeave(vOnCursorLeave callback);
	void setOnTextChange(vOnTextChange callback);
	void setOnNormalRedraw(vOnNormalRedraw callback);
	void setOnPressRedraw(vOnPressRedraw callback);
	void setOnHoverRedraw(vOnHoverRedraw callback);
};

#endif //#define _UI_MANAGER_VIEW_HEADER