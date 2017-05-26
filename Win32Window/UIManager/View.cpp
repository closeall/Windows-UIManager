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
}

UIManager::View::View(UIManager::ViewType view, int startX, int startY, int endX, int endY)
{
	vType = view;
	this->startX = startX;
	this->startY = startX;
	this->endX = endX;
	this->endY = endY;
	onClick.push_back(NULL);
	onTextChange.push_back(NULL);
}

void UIManager::View::setType(UIManager::ViewType view)
{
	vType = view;
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

void UIManager::View::setTextColor(int r, int g, int b)
{
	vFontColor = RGB(r, g, b);
	RedrawWindow(vHWND, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	//SetTextColor(vHWND, RGB(0, 0, 0));
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

void UIManager::View::setOnTextChange(vOnTextChange callback)
{
	if (!vCreated) {
		onTextChange.at(onClick.size() - 1) = callback;
	}
	else {
		onTextChange.at(vId) = callback;
	}
}
