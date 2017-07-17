

#ifndef _UI_MANAGER_NAMESPACE_HEADER
#define _UI_MANAGER_NAMESPACE_HEADER

#define _AFXDLL
#include <SDKDDKVer.h>
#include <afxwin.h>

#define DEF_FONT_SIZE 13
const std::string DEF_FONT_TYPE = "Segoe UI";

namespace UIManager {
	//Window
	class WindowManager;
	enum StartState;
	//Views
	class View;
	enum ViewType;
	enum ViewMargin;
	enum CaseType;
	enum ProgressState;
	struct InputRule;
	//Namespace H
	struct Coordinates;
	//Managers
	HBITMAP Bitmap(std::string url);
	HICON Icon(std::string url);
}

namespace UIDrawer {
	//Drawer
	enum LineType;
	enum TextMargin;
	HBRUSH CreateBrush(COLORREF color);
	HBRUSH CreateGradientBrush(LPDRAWITEMSTRUCT &item, COLORREF top, COLORREF bottom);
	HBRUSH CreateComplexGradientBrush(LPDRAWITEMSTRUCT &item, COLORREF fcolor, COLORREF scolor, DWORD def);
	HBRUSH CreateBitmapBrush(HBITMAP bitmap);
	HFONT DrawFont(int size, int angle, DWORD weight, bool italic, bool underline, bool strike, std::string font);
	BOOL DrawBitmap(LPDRAWITEMSTRUCT &item, INT x, INT y, HBITMAP hBitmap, DWORD dwROP);
	BOOL DrawCircle(LPDRAWITEMSTRUCT & item, RECT rect, INT linesize, UIDrawer::LineType line, COLORREF linecolor, HBRUSH hbr);
	BOOL DrawRectangle(LPDRAWITEMSTRUCT &item, RECT rect, INT border, INT linesize, UIDrawer::LineType line, COLORREF linecolor, HBRUSH fillcolor);
	BOOL DrawString(LPDRAWITEMSTRUCT & item, RECT rect, std::string text, INT size, UIDrawer::TextMargin horizontal, UIDrawer::TextMargin vertical, COLORREF color, HFONT font);
	BOOL DrawFocus(LPDRAWITEMSTRUCT & item);
}

struct UIManager::Coordinates {
	int x = 0;
	int y = 0;
	WPARAM flags = NULL; //MK_CONTROL, MK_LBUTTON, MK_MBUTTON, MK_RBUTTON, MK_SHIFT
};

#endif //_UI_MANAGER_NAMESPACE_HEADER