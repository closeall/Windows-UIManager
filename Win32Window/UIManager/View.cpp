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
	setType(view);
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	onClick.push_back(NULL);
	onTextChange.push_back(NULL);
	onCursorEnter.push_back(NULL);
	onCursorLeave.push_back(NULL);
}

void UIManager::View::setType(UIManager::ViewType view)
{
	vType = view;
	switch (view) {
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
	case EditText: //Hover
	{
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

std::string UIManager::View::getText()
{
	return vText;
}

void UIManager::View::setOnClick(vOnClick callback)
{
	if (!vCreated) {
		onClick.at(onClick.size() - 1) = callback;
	}
	else {
		onClick.at(vId) = callback;
	}
}

void UIManager::View::setOnCursorEnter(vOnCursorEnter callback)
{
	if (!vCreated) {
		onCursorEnter.at(onCursorEnter.size() - 1) = callback;
	}
	else {
		onCursorEnter.at(vId) = callback;
	}
}

void UIManager::View::setOnCursorLeave(vOnCursorLeave callback)
{
	if (!vCreated) {
		onCursorLeave.at(onCursorLeave.size() - 1) = callback;
	}
	else {
		onCursorLeave.at(vId) = callback;
	}
}

void UIManager::View::setOnTextChange(vOnTextChange callback)
{
	if (!vCreated) {
		onTextChange.at(onClick.size() - 1) = callback;
	}
	else {
		onTextChange.at(vId) = callback;
	}
}
