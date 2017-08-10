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

#include "WindowManager.h"

std::vector<wLeftClickCallBack> UIManager::WindowManager::onLeftClick;
std::vector<wRightClickCallBack> UIManager::WindowManager::onRightClick;
std::vector<wMiddleClickCallBack> UIManager::WindowManager::onMiddleClick;
std::vector<wCreateCallBack> UIManager::WindowManager::onCreate;
std::vector<wFocusCallBack> UIManager::WindowManager::onFocus;
std::vector<wDestroyCallBack> UIManager::WindowManager::onDestroy;
std::vector<wPersonalizedCallBack> UIManager::WindowManager::onMessageRec;

std::vector<HWND> UIManager::WindowManager::wHWND;
bool UIManager::WindowManager::wDragAndMove;
int UIManager::WindowManager::wObjHover = -1;
std::vector<vObject> UIManager::WindowManager::vObjects;
std::vector<UIManager::WindowManager *> UIManager::WindowManager::wManager;

//Private
//
void UIManager::WindowManager::createView()
{
	//Create Window
	this->wCreated = true;
	CreateWindowEx(
		ExwFlags,
		this->wiName.c_str(),			/* Title Class */
		this->wiName.c_str(),			/* Title Text */
		wFlags,							/* Initial Flags */
		startX,							/* X Start */
		startY,							/* Y Start */
		endX,							/* The programs width */
		endY,							/* and height in pixels */
		HWND_DESKTOP,					/* The window is a child-window to desktop */
		NULL,							/* No menu */
		hInstance,						/* Program Instance handler */
		NULL
	);

	//Messages Manage
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int UIManager::WindowManager::viewLocByRef(LPARAM hwnd)
{
	for (unsigned int i = 0; i < vObjects.size(); i++) {
		if ((HWND)hwnd == vObjects.at(i).view->vHWND) {
			return i;
		}
	}
	return 0;
}

int UIManager::WindowManager::windowLocByRef(HWND hwnd)
{
	for (unsigned int i = 0; i < vObjects.size(); i++) {
		if ((HWND)hwnd == wHWND.at(i)) {
			return i;
		}
	}
	return 0;
}

//Public
//
UIManager::WindowManager::WindowManager() : hInstance(NULL)
{
	setInitialData(hInstance);
	#ifdef _LEGACY_UI
		SetWindowTheme(hwnd, L" ", L" ");
	#endif
}

//Before
void UIManager::WindowManager::setInitialData(HINSTANCE hInstance, std::string wiName, int startX, int startY, int endX, int endY)
{
	this->wiName = wiName;
	this->hInstance = hInstance;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	if (wId < 0) {
		wHWND.push_back(HWND());
		wId = static_cast<int>(wHWND.size()) - 1;
		onLeftClick.push_back(NULL);
		onRightClick.push_back(NULL);
		onMiddleClick.push_back(NULL);
		onCreate.push_back(NULL);
		onFocus.push_back(NULL);
		onDestroy.push_back(NULL);
		onMessageRec.push_back(NULL);
		wManager.push_back(this);
		wDragAndMove = false;
	}
}

//Before
void UIManager::WindowManager::setHInstance(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}

//Always
void UIManager::WindowManager::setText(std::string text)
{
	wiName = text;
	if (wCreated) {
		SetWindowText(wHWND.at(wId), text.c_str());
	}
}

//Always
void UIManager::WindowManager::setLocation(int xloc, int yloc)
{
	startX = xloc;
	startY = yloc;
	if (wCreated) {
		SetWindowPos(wHWND.at(wId), NULL, startX, startY, 0, 0, SWP_NOSIZE);
	}
}

//Always
void UIManager::WindowManager::setSize(int xsize, int ysize)
{
	endX = xsize;
	endY = ysize;
	if (wCreated) {
		SetWindowPos(wHWND.at(wId), NULL, 0, 0, xsize, ysize, SWP_NOMOVE);
	}
}

//Always
void UIManager::WindowManager::setVisible(bool visible)
{
	if (!wCreated) {
		if (visible) {
			wFlags = wFlags | WS_VISIBLE;
		} else {
			wFlags = wFlags & ~WS_VISIBLE;
		}
	}
	else {
		if (visible) {
			SetWindowPos(wHWND.at(wId), NULL, 0, 0, 9, 9, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		}
		else {
			SetWindowPos(wHWND.at(wId), NULL, 0, 0, 9, 9, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
		}
	}
}

//Always
void UIManager::WindowManager::setEnabled(bool enabled)
{
	if (!wCreated) {
		if (enabled) {
			wFlags = wFlags | WS_DISABLED;
		}
		else {
			wFlags = wFlags & ~WS_DISABLED;
		}
	}
	else {
		EnableWindow(wHWND.at(wId), enabled);
	}
}

//Before
void UIManager::WindowManager::setStartState(UIManager::StartState state)
{
	switch(state) {
		case UIManager::Maximized: {
			wFlags = wFlags | WS_MAXIMIZE;
			break;
		}
		case UIManager::Minimized: {
			wFlags = wFlags | WS_MINIMIZE;
			break;
		}
		default: {
			break;
		}
	}
}

//Before
void UIManager::WindowManager::setFocusable(bool focusable)
{
	if (!wCreated) {
		if (!focusable) {
			ExwFlags = ExwFlags | WS_EX_NOACTIVATE;
		}
	}
}

//After
void UIManager::WindowManager::makeTop()
{
	if (wCreated) {
		SetWindowPos(wHWND.at(wId), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

//After
void UIManager::WindowManager::makeBottom()
{
	if (wCreated) {
		SetWindowPos(wHWND.at(wId), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

//Before
void UIManager::WindowManager::setCursor(HCURSOR cursor)
{
	wCursor = cursor;
}

//Before
void UIManager::WindowManager::setIcon(HICON icon)
{
	wIcon = icon;
}

//Before
void UIManager::WindowManager::setBackground(COLORREF brush)
{
	wbColor = CreateSolidBrush(brush);
}

void UIManager::WindowManager::setBackground(HBITMAP brush)
{
	wbColor = UIDrawer::CreateBitmapBrush(brush);
}

//Before
void UIManager::WindowManager::allowMaximizeButton(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_MAXIMIZEBOX;
		}
		else {
			wFlags = wFlags & ~WS_MAXIMIZEBOX;
		}
	}
}

//Before
void UIManager::WindowManager::allowMinimizeButton(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_MINIMIZEBOX;
		}
		else {
			wFlags = wFlags & ~WS_MINIMIZEBOX;
		}
	}
}

//Before
void UIManager::WindowManager::allowResize(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_THICKFRAME;
		}
		else {
			wFlags = wFlags & ~WS_THICKFRAME;
		}
	}
}

//Before
void UIManager::WindowManager::disallowTitleBar(bool allow)
{
	if (!wCreated) {
		if (allow) {
			wFlags = wFlags | WS_POPUP; //WS_POPUPWINDOW
		}
		else {
			wFlags = wFlags & ~WS_POPUP;
		}
	}
}

//Before
void UIManager::WindowManager::allowDragAndMove(bool allow)
{
	wDragAndMove = allow;
}

//After
void UIManager::WindowManager::setTransparentKeyColor(COLORREF color)
{
	if (wCreated) {
		wbColor = CreateSolidBrush(color);
		#ifdef _WIN64
		SetClassLongPtr(wHWND.at(wId), GCLP_HBRBACKGROUND, (LONG)(__int64)wbColor);
		#else
		SetClassLongPtr(wHWND, GCLP_HBRBACKGROUND, (LONG)(long)wbColor);
		#endif
		SetWindowLong(wHWND.at(wId), GWL_EXSTYLE, GetWindowLong(wHWND.at(wId), GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(wHWND.at(wId), color, 0, LWA_COLORKEY);
	}
}

//After
void UIManager::WindowManager::setAlpha(int percent)
{
	SetWindowLong(wHWND.at(wId), GWL_EXSTYLE, GetWindowLong(wHWND.at(wId), GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(wHWND.at(wId), 0, (255 * percent) / 100, LWA_ALPHA);
}

void UIManager::WindowManager::inflateShadow()
{
	wClassStyle = CS_DROPSHADOW;
}

//DEBUG
void UIManager::WindowManager::UIM_VERSION()
{
	//UIMANAGER_VERSION
	MessageBox(0, std::to_string(UIMANAGER_VERSION).c_str(), "UIManager Version", MB_OK);
}

void UIManager::WindowManager::setOnLeftClick(wLeftClickCallBack callback)
{
	onLeftClick.at(wId) = callback;
}

void UIManager::WindowManager::setOnRightClick(wRightClickCallBack callback)
{
	onRightClick.at(wId) = callback;
}

void UIManager::WindowManager::setOnMiddleClick(wMiddleClickCallBack callback)
{
	onMiddleClick.at(wId) = callback;
}

//Before
void UIManager::WindowManager::setTopMost(bool active)
{
	if (!wCreated) {
		if (active) {
			ExwFlags = ExwFlags | WS_EX_TOPMOST;
		}
		else {
			ExwFlags = ExwFlags & ~WS_EX_TOPMOST;
		}
	}
}

//Before
void UIManager::WindowManager::setOnCreate(wCreateCallBack callback)
{
	onCreate.at(wId) = callback;
}

//Before
void UIManager::WindowManager::setOnFocus(wFocusCallBack callback)
{
	onFocus.at(wId) = callback;
}

//Before
void UIManager::WindowManager::setOnDestroy(wDestroyCallBack callback)
{
	onDestroy.at(wId) = callback;
}

//Before
void UIManager::WindowManager::setPersonalizedHandler(wPersonalizedCallBack callback)
{
	onMessageRec.at(wId) = callback;
}

void UIManager::WindowManager::build()
{
	//Create Class
	winClass.cbSize = sizeof(winClass);
	winClass.hInstance = hInstance;
	winClass.lpszClassName = this->wiName.c_str();
	winClass.lpfnWndProc = WndProc; //Execution callback
	//Load default editable ellements
	winClass.style = wClassStyle;
	winClass.hCursor = wCursor;		/*Default*/
	winClass.hIcon = wIcon;								/*Alt+Tab Dialog*/
	winClass.hbrBackground = wbColor;
	winClass.lpszMenuName = NULL;						/* No menu */
	RegisterClassEx(&winClass);

	//Create Window
	createView();
}

//After
void UIManager::WindowManager::minimize()
{
	CloseWindow(wHWND.at(wId));
}

//After
void UIManager::WindowManager::destroy()
{
	DestroyWindow(wHWND.at(wId));
}

HWND UIManager::WindowManager::getHWND()
{
	return wHWND.at(wId);
}

HINSTANCE UIManager::WindowManager::getHINSTANCE()
{
	return hInstance;
}

void UIManager::WindowManager::addView(UIManager::View &view)
{
	vObject object;
	object.view = &view;
	std::string type = vh::getView(view.vType);
	int nextID = (int)vObjects.size();
	HWND hwnd = CreateWindowW(FormatFactory::StringToWString(type).c_str(), FormatFactory::StringToWString(view.vText).c_str(),
		view.vFlags,
		view.startX, view.startY, view.endX, view.endY,
		wHWND.at(wId), (HMENU)(UINT_PTR)nextID, NULL, NULL);
	if (view.vType == PictureBox) {
		SendMessage(hwnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)view.vBitMap);
	}
	if (view.vType == ImageButton) {
		SendMessage(hwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)view.vBitMap);
	}
	if (view.vType == EditText) {
		SendMessage(hwnd, EM_SETLIMITTEXT, view.maxInput, NULL);
	}
	if (view.vType == ProgressBar) {
		SendMessage(hwnd, PBM_SETRANGE, 0, MAKELPARAM(0, view.mProgress));
		SendMessage(hwnd, PBM_SETPOS, (WPARAM)view.aProgress, 0);
	}
	EnableWindow(hwnd, view.vEnabled);
	object.manager = hwnd;
	view.vCreated = true;
	view.vHWND = hwnd;
	view.wHWND = wHWND.at(wId);
	view.vId = nextID;
	view.updateFont();
	vObjects.push_back(object);
}

LRESULT CALLBACK UIManager::WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wId = windowLocByRef(hwnd);
	switch (msg)
	{
	case WM_CREATE: //On Window Create
	{
		wHWND.at(wId) = hwnd;
		if (onCreate.at(wId) != NULL)
			onCreate.at(wId)(wManager.at(wId));
		break;
	}
	case WM_SETCURSOR: //Manage focus
	{
		if (vObjects.size() > 0) { //Only if exist any view
			vObject object = vObjects.at(viewLocByRef(wParam));
			if (object.view->vId != wObjHover) {
				//On enter
				vOnCursorEnter tch = object.view->onCursorEnter;
				if (tch != NULL)
					tch(object.manager);
				//Custom Button Manager
				if (object.view->vType == CustomButton) {
					InvalidateRect(object.manager, NULL, FALSE);
				}
				//On leave
				if (wObjHover != -1) {
					vObject objectl = vObjects.at(wObjHover);
					vOnCursorLeave tch = objectl.view->onCursorLeave;
					if (tch != NULL)
						tch(object.manager);
					//Custom Button Manager
					if (objectl.view->vType == CustomButton) {
						InvalidateRect(objectl.manager, NULL, FALSE);
					}
				}
				wObjHover = object.view->vId;
			}
		}
		break;
	}
	case WM_COMMAND: //Command execution
	{
		switch (HIWORD(wParam)) {
		//EditText Control
		case EN_CHANGE: //Text Changed
		{
			vObject object = vObjects.at(viewLocByRef(lParam));
			UIManager::ViewType vType = object.view->vType;
			TCHAR buff[1024];
			GetWindowText((HWND)lParam, buff, sizeof(buff));
			object.view->vText = buff;
			vOnTextChange tch = object.view->onTextChange;
			if (tch != NULL)
				tch(object.manager, buff);
			break;
		}
		//Button, ImageButton, CustomButton Control
		case BN_DBLCLK:
		{
			vObject object = vObjects.at(viewLocByRef(lParam));
			vOnDoubleClick btton = object.view->onDoubleClick;
			if (btton != NULL)
				btton(object.manager);
			break;
		}
		case BN_CLICKED:
		{
			vObject object = vObjects.at(viewLocByRef(lParam));
			vOnClick btton = object.view->onClick;
			if (btton != NULL)
				btton(object.manager);
			break;
		}
		//PictureBox
		case STN_DBLCLK:
		{
			vObject object = vObjects.at(viewLocByRef(lParam));
			vOnDoubleClick btton = object.view->onDoubleClick;
			if (btton != NULL)
				btton(object.manager);
			break;
		}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		UIManager::Coordinates coord;
		coord.x = GET_X_LPARAM(lParam);
		coord.y = GET_Y_LPARAM(lParam);
		coord.flags = wParam;
		if (onLeftClick.at(wId) != NULL)
			onLeftClick.at(wId)(wManager.at(wId), coord);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		UIManager::Coordinates coord;
		coord.x = GET_X_LPARAM(lParam);
		coord.y = GET_Y_LPARAM(lParam);
		coord.flags = wParam;
		if (onRightClick.at(wId) != NULL)
			onRightClick.at(wId)(wManager.at(wId), coord);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		UIManager::Coordinates coord;
		coord.x = GET_X_LPARAM(lParam);
		coord.y = GET_Y_LPARAM(lParam);
		coord.flags = wParam;
		if (onMiddleClick.at(wId) != NULL)
			onMiddleClick.at(wId)(wManager.at(wId), coord);
		break;
	}
	case WM_SETFOCUS: //Get Focus
	{
		if (onFocus.at(wId) != NULL)
			onFocus.at(wId)(wManager.at(wId), true);
		break;
	}
	case WM_KILLFOCUS: //Lost Focus
	{
		if (onFocus.at(wId) != NULL)
			onFocus.at(wId)(wManager.at(wId), false);
		break;
	}
	case WM_NCHITTEST: //Drag and move window by it's content
	{
		LRESULT hit = DefWindowProc(wHWND.at(wId), msg, wParam, lParam);
		if (GetAsyncKeyState(VK_LBUTTON) & VK_LBUTTON && hit == HTCLIENT && wDragAndMove) hit = HTCAPTION;
		return hit;
	}
	case WM_CTLCOLORBTN: //Draw Buttons view transparent bg
	{
		SetBkMode((HDC)wParam, TRANSPARENT); //Set Text mode transparennt
		vObject object = vObjects.at(viewLocByRef(lParam));
		if (object.view->vBackColor == HOLLOW_BRUSH) {
			return (LRESULT)GetStockObject(HOLLOW_BRUSH);
		}
		else {
			return (LRESULT)CreateSolidBrush(object.view->vBackColor);
		}
	}
	case WM_CTLCOLORSTATIC: //Draw Static views transparent bg
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		vObject object = vObjects.at(viewLocByRef(lParam));
		SetTextColor((HDC)wParam, object.view->vFontColor); //Color
		if (object.view->vBackColor == HOLLOW_BRUSH) {
			if (object.view->vType == EditText) {
				return (LRESULT)GetStockObject(WHITE_BRUSH); //ReadOnly exception bugfix
			}
			else {
				SetBkMode((HDC)wParam, TRANSPARENT); //BG Transp
				return (LRESULT)GetStockObject(HOLLOW_BRUSH);
			}
		}
		else {
			return (LRESULT)CreateSolidBrush(object.view->vBackColor);
		}
		break;
	}
	case WM_DRAWITEM: //Draw Custom control data
	{
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
		vObject object = vObjects.at(viewLocByRef((LPARAM)lpDrawItem->hwndItem));

		if (lpDrawItem->CtlType != ODT_BUTTON || object.view->vType != CustomButton) //Not button??
			return TRUE;

		if (lpDrawItem->itemState & ODS_SELECTED) //Selected??
		{
			//Click
			vOnPressRedraw btton = object.view->onPressRedraw;
			if (btton != NULL)
				btton(object.manager, lpDrawItem);
		} else {
			if (object.view->vId == wObjHover) {
				//Hovered
				vOnHoverRedraw btton = object.view->onHoverRedraw;
				if (btton != NULL)
					btton(object.manager, lpDrawItem);
			} else {
				//Normal
				vOnNormalRedraw btton = object.view->onNormalRedraw;
				if (btton != NULL)
					btton(object.manager, lpDrawItem);
			}
		}
		break;
	}
	case WM_DESTROY: //Form Destroyed
	{
		if (onDestroy.at(wId) != NULL)
			onDestroy.at(wId)(wManager.at(wId));
		PostQuitMessage(0);
		break;
	}
	}
	if (onMessageRec.at(wId) != NULL)
		onMessageRec.at(wId)(wManager.at(wId), msg, wParam, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

COLORREF HEX(std::string color)
{
	return FormatFactory::hexToColor(color);
}

//desktop notifications
//do custom button

//redraw size image
//custom pb
/*
DWORD dwStyle = GetWindowLong(object, GWL_STYLE);
SetWindowLong(object, GWL_STYLE, dwStyle & ~ ES_NUMBER);
*/

/*HWND xd = WindowFromPoint(point);*/