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

void UIManager::View::updateFont()
{
	hFont = CreateFont(vFontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, vFont.c_str());
	if (vCreated) {
		SendMessage(vHWND, WM_SETFONT, (WPARAM)hFont, TRUE);
		redrawView();
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
	setType(view);
}

//All || Before
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

//All || Always
void UIManager::View::setText(std::string text)
{
	vText = text;
	if (vCreated) {
		SendMessage(vHWND, WM_SETTEXT, 0, (LPARAM)vText.c_str());
	}
}

//All || Always
void UIManager::View::setLocation(int xloc, int yloc)
{
	this->startX = xloc;
	this->startY = yloc;
	if (vCreated) {
		MoveWindow(vHWND, xloc, yloc, endX, endY, 1);
	}
}

//All || Always
void UIManager::View::setSize(int xsize, int ysize)
{
	this->endX = xsize;
	this->endY = ysize;
	if (vCreated) {
		MoveWindow(vHWND, startX, startY, xsize, ysize, 1);
	}
}

//All || Always
void UIManager::View::setEnabled(bool enabled)
{
	vEnabled = enabled;
	if (vCreated) {
		EnableWindow(vHWND, vEnabled);
	}
}

//All || Always
void UIManager::View::setTextFont(std::string fname)
{
	vFont = fname;
	updateFont();
}

//All || Always
void UIManager::View::setTextSize(int size)
{
	vFontSize = size;
	updateFont();
}

void UIManager::View::setBackgroundColor(COLORREF color)
{
	vBackColor = color;
	if (vCreated) {
		redrawView();
	}
}

//Edit, Static || Always
void UIManager::View::setTextColor(COLORREF color) //Pending
{
	vFontColor = color;
	if (vCreated) {
		redrawView();
	}
}

//Buttons, EditText || Always
void UIManager::View::setMargin(ViewMargin loc)
{
	if (!vCreated) {
		switch (loc)
		{
		case UIManager::Left:
			if (vType == EditText) {
				vFlags = vFlags | ES_LEFT;
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_LEFT;
			}
			break;
		case UIManager::Right:
			if (vType == EditText) {
				vFlags = vFlags | ES_RIGHT;
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_RIGHT;
			}
			break;
		case UIManager::Center:
			if (vType == EditText) {
				vFlags = vFlags | ES_CENTER;
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_CENTER;
			}
			break;
		default:
			break;
		}
	} else {
		switch (loc)
		{
		case UIManager::Left:
			if (vType == EditText) {
				vFlags = vFlags | ES_LEFT;
				vFlags = vFlags & ~ES_RIGHT;
				vFlags = vFlags & ~ES_CENTER;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_LEFT;
				vFlags = vFlags & ~BS_RIGHT;
				vFlags = vFlags & ~BS_CENTER;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			break;
		case UIManager::Right:
			if (vType == EditText) {
				vFlags = vFlags | ES_RIGHT;
				vFlags = vFlags & ~ES_LEFT;
				vFlags = vFlags & ~ES_CENTER;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_RIGHT;
				vFlags = vFlags & ~BS_LEFT;
				vFlags = vFlags & ~BS_CENTER;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			break;
		case UIManager::Center:
			if (vType == EditText) {
				vFlags = vFlags | ES_CENTER;
				vFlags = vFlags & ~ES_RIGHT;
				vFlags = vFlags & ~ES_LEFT;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			else if (vType == Button || vType == CustomButton || vType == ImageButton) {
				vFlags = vFlags | BS_CENTER;
				vFlags = vFlags & ~BS_RIGHT;
				vFlags = vFlags & ~BS_LEFT;
				SetWindowLong(vHWND, GWL_STYLE, vFlags);
			}
			break;
		default:
			break;
		}
		InvalidateRect(vHWND, NULL, TRUE);
	}
}

//EditText || Before
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

//PictureBox, ImageButton || Always
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

//All || Always
std::string UIManager::View::getText()
{
	return vText;
}

//ProgressBar || Always
void UIManager::View::setProgress(int progress)
{
	this->aProgress = progress;
	if (vCreated) {
		SendMessage(vHWND, PBM_SETPOS, (WPARAM)aProgress, 0);
	}
}

//ProgressBar || Always
void UIManager::View::setProgressMax(int progress)
{
	this->mProgress = progress;
	if (vCreated) {
		SendMessage(vHWND, PBM_SETRANGE, 0, MAKELPARAM(0, mProgress));
	}
}

//ProgressBar || After
void UIManager::View::setProgressVertical(bool vertical)
{
	if (vertical) {
		vFlags = vFlags | PBS_VERTICAL;
	}
	else {
		vFlags = vFlags & ~PBS_VERTICAL;
	}
}

//ProgressBar || After
void UIManager::View::setProgressState(ProgressState state)
{
	if (vCreated) {
		DWORD dwStyle = GetWindowLong(vHWND, GWL_STYLE);
		switch (state) {
		case ProgressState::NormalProgress:
			SendMessage(vHWND, (UINT)PBM_SETMARQUEE, FALSE, (LPARAM)0);
			SetWindowLong(vHWND, GWL_STYLE, dwStyle & ~PBS_MARQUEE);
			SendMessage(vHWND, PBM_SETSTATE, PBST_NORMAL, 0);
			break;
		case ProgressState::ErrorProgress:
			SendMessage(vHWND, (UINT)PBM_SETMARQUEE, FALSE, (LPARAM)0);
			SetWindowLong(vHWND, GWL_STYLE, dwStyle & ~PBS_MARQUEE);
			SendMessage(vHWND, PBM_SETSTATE, PBST_ERROR, 0);
			break;
		case ProgressState::PausedProgress:
			SendMessage(vHWND, (UINT)PBM_SETMARQUEE, FALSE, (LPARAM)0);
			SetWindowLong(vHWND, GWL_STYLE, dwStyle & ~PBS_MARQUEE);
			SendMessage(vHWND, PBM_SETSTATE, PBST_PAUSED, 0);
			break;
		case ProgressState::UndefinedProgress:
			SetWindowLong(vHWND, GWL_STYLE, dwStyle | PBS_MARQUEE);
			SendMessage(vHWND, (UINT)PBM_SETMARQUEE, TRUE, (LPARAM)0);
			break;
		}
	}
}

//All || Always
HWND UIManager::View::getHWND()
{
	return vHWND;
}

RECT UIManager::View::getSizeRECT()
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = endX;
	rect.bottom = endY;
	return rect;
}

int UIManager::View::getLeft()
{
	return startX;
}

int UIManager::View::getTop()
{
	return startY;
}

int UIManager::View::getRight()
{
	return endX;
}

int UIManager::View::getBottom()
{
	return endY;
}


void UIManager::View::redrawView()
{
	RECT rect;
	GetClientRect(vHWND, &rect);
	InvalidateRect(vHWND, &rect, TRUE);
	MapWindowPoints(vHWND, wHWND, (POINT *)&rect, 2);
	RedrawWindow(wHWND, &rect, NULL, RDW_ERASE | RDW_INVALIDATE); //Redraw
	SetWindowPos(vHWND, vHWND, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); //Bring to top again
}

//Buttons, Static || Always
void UIManager::View::setOnClick(vOnClick callback)
{
	if (vType == PictureBox || vType == TextView) {
		if (!vCreated) {
			vFlags = vFlags | SS_NOTIFY;
		}
		else {
			DWORD dwStyle = GetWindowLong(vHWND, GWL_STYLE);
			SetWindowLong(vHWND, GWL_STYLE, dwStyle | SS_NOTIFY);
		}
	}
	onClick = callback;
}

//Buttons, Static || Always
void UIManager::View::setOnDoubleClick(vOnDoubleClick callback)
{
	if (vType == PictureBox || vType == TextView) {
		if (!vCreated) {
			vFlags = vFlags | SS_NOTIFY;
		}
		else {
			DWORD dwStyle = GetWindowLong(vHWND, GWL_STYLE);
			SetWindowLong(vHWND, GWL_STYLE, dwStyle | SS_NOTIFY);
		}
	}
	onDoubleClick = callback;
}

//All || Always
void UIManager::View::setOnCursorEnter(vOnCursorEnter callback)
{
	onCursorEnter = callback;
}

//All || Always
void UIManager::View::setOnCursorLeave(vOnCursorLeave callback)
{
	onCursorLeave = callback;
}

//EditText || Always
void UIManager::View::setOnTextChange(vOnTextChange callback)
{
	onTextChange = callback;
}

void UIManager::View::setOnNormalRedraw(vOnNormalRedraw callback)
{
	onNormalRedraw = callback;
}

void UIManager::View::setOnPressRedraw(vOnPressRedraw callback)
{
	onPressRedraw = callback;
}

void UIManager::View::setOnHoverRedraw(vOnHoverRedraw callback)
{
	onHoverRedraw = callback;
}
