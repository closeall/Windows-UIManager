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

#include "View.h"

std::vector<vOnClick> UIManager::View::onClick;
std::vector<vOnDoubleClick> UIManager::View::onDoubleClick;
std::vector<vOnTextChange> UIManager::View::onTextChange;
std::vector<vOnCursorEnter> UIManager::View::onCursorEnter;
std::vector<vOnCursorLeave> UIManager::View::onCursorLeave;

void UIManager::View::updateFont()
{
	hFont = CreateFont(vFontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, vFont.c_str());
	if (vCreated) {
		SendMessage(vHWND, WM_SETFONT, (WPARAM)hFont, TRUE);
	}
}

UIManager::View::View()
{
	vType = UIManager::TextView;
	setType(UIManager::TextView);
}

UIManager::View::View(UIManager::ViewType view, int startX, int startY, int endX, int endY)
{
	vType = view;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	onClick.push_back(NULL);
	onDoubleClick.push_back(NULL);
	onTextChange.push_back(NULL);
	onCursorEnter.push_back(NULL);
	onCursorLeave.push_back(NULL);
	setType(view);
}

void UIManager::View::setType(UIManager::ViewType view)
{
	vType = view;
	switch (view) {
	case EditText:
	{
		vFlags = vFlags | ES_AUTOHSCROLL;
		break;
	}
	case Button:  //Hover
	{
		vFlags = vFlags | BS_NOTIFY;
		break;
	}
	case ImageButton: //Hover, Bitmap
	{
		vFlags = vFlags | SS_BITMAP;
		vFlags = vFlags | BS_NOTIFY;
		break;
	}
	case CustomButton: //Hover, Edit Control
	{
		vFlags = vFlags | BS_OWNERDRAW;
		vFlags = vFlags | BS_NOTIFY;
		break;
	}
	case PictureBox: //Bitmap
	{
		vFlags = vFlags | SS_BITMAP;
		break;
	}
	}
}

void UIManager::View::setText(std::string text)
{
	vText = text;
	if (vCreated) {
		SendMessage(vHWND, WM_SETTEXT, 0, (LPARAM)vText.c_str());
	}
}

void UIManager::View::setLocation(int xloc, int yloc)
{
	this->startX = xloc;
	this->startY = yloc;
}

void UIManager::View::setSize(int xsize, int ysize)
{
	this->endX = xsize;
	this->endY = ysize;
}

void UIManager::View::setEnabled(bool enabled)
{
	vEnabled = enabled;
	if (vCreated) {
		EnableWindow(vHWND, vEnabled);
	}
}

void UIManager::View::setTextFont(std::string fname)
{
	vFont = fname;
	updateFont();
}

void UIManager::View::setTextSize(int size)
{
	vFontSize = size;
	updateFont();
}

void UIManager::View::setTextColor(COLORREF color) //Pending
{
	vFontColor = color;
	if (vCreated) {
		RedrawWindow(vHWND, 0, 0, RDW_INVALIDATE);
	}
}

//Buttons, EditText
void UIManager::View::setTextMargin(ViewLoc loc)
{
	if (!vCreated) {
		switch (loc)
		{
		case UIManager::Left:
			if (vType == EditText) {
				vFlags = vFlags | ES_LEFT;
			} else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_LEFT;
			}
			break;
		case UIManager::Right:
			if (vType == EditText) {
				vFlags = vFlags | ES_RIGHT;
			} else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_RIGHT;
			}
			break;
		case UIManager::Center:
			if (vType == EditText) {
				vFlags = vFlags | ES_CENTER;
			} else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_CENTER;
			}
			break;
		default:
			break;
		}
	}
}

//EditText
void UIManager::View::setInputRule(InputRule rule)
{
	if (!vCreated)
		if (vType == EditText) {
			maxInput = rule.charLimit;
			if (rule.readOnly) {
				vFlags = vFlags | ES_READONLY;
			}
			if (rule.passWord) {
				vFlags = vFlags | ES_PASSWORD;
			}
			if (rule.numbersOnly) {
				vFlags = vFlags | ES_NUMBER;
			}
			if (rule.keepSel) {
				vFlags = vFlags | ES_NOHIDESEL;
			}
			if (rule.multiLine) {
				vFlags = vFlags | ES_MULTILINE | ES_AUTOVSCROLL;
			}
			switch (rule.textCase)
			{
			case Uppercase: {
				vFlags = vFlags | ES_UPPERCASE;
				break;
			}
			case Lowercase: {
				vFlags = vFlags | ES_LOWERCASE;
				break;
			}
			}
		}
}

//PictureBox, ImageButton
void UIManager::View::setPictureRessource(HBITMAP bitmap)
{
	vBitMap = bitmap;
	if (vCreated) {
		if (vType == PictureBox) {
			SendMessage(vHWND, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)vBitMap);
		}
		if (vType == ImageButton) {
			SendMessage(vHWND, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)vBitMap);
		}
	}
}

//All
std::string UIManager::View::getText()
{
	return vText;
}

//Buttons, PictureBox, Label
void UIManager::View::setOnClick(vOnClick callback)
{
	if (!vCreated) {
		onClick.at(onClick.size() - 1) = callback;
		if (vType == PictureBox || vType == TextView) {
			vFlags = vFlags | SS_NOTIFY;
		}
	}
	else {
		onClick.at(vId) = callback;
	}
}

//Buttons, PictureBox, Label
void UIManager::View::setOnDoubleClick(vOnDoubleClick callback)
{
	if (!vCreated) {
		onDoubleClick.at(onDoubleClick.size() - 1) = callback;
		if (vType == PictureBox || vType == TextView) {
			vFlags = vFlags | SS_NOTIFY;
		}
	}
	else {
		onDoubleClick.at(vId) = callback;
	}
}

//EditText, Buttons
void UIManager::View::setOnCursorEnter(vOnCursorEnter callback)
{
	if (!vCreated) {
		onCursorEnter.at(onCursorEnter.size() - 1) = callback;
	}
	else {
		onCursorEnter.at(vId) = callback;
	}
}

//EditText, Buttons
void UIManager::View::setOnCursorLeave(vOnCursorLeave callback)
{
	if (!vCreated) {
		onCursorLeave.at(onCursorLeave.size() - 1) = callback;
	}
	else {
		onCursorLeave.at(vId) = callback;
	}
}

//EditText
void UIManager::View::setOnTextChange(vOnTextChange callback)
{
	if (!vCreated) {
		onTextChange.at(onClick.size() - 1) = callback;
	}
	else {
		onTextChange.at(vId) = callback;
	}
}
