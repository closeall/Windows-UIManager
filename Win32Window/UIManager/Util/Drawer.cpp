#include "Drawer.h"

HBRUSH UIDrawer::CreateBrush(COLORREF color)
{
	return CreateSolidBrush(color);
}

HBRUSH UIDrawer::CreateComplexGradientBrush(LPDRAWITEMSTRUCT &item, COLORREF fcolor, COLORREF scolor, DWORD def) {
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hDC);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hDC, item->rcItem.right - item->rcItem.left, item->rcItem.bottom - item->rcItem.top);
	SelectObject(hdcmem, hbitmap);
	TRIVERTEX vertex[2];
	vertex[0].x = 0;
	vertex[0].y = 0;
	vertex[0].Red = GetRValue(fcolor);
	vertex[0].Green = GetGValue(fcolor);
	vertex[0].Blue = GetBValue(fcolor);
	vertex[0].Alpha = 0xffff;

	vertex[1].x = item->rcItem.right;
	vertex[1].y = item->rcItem.bottom;
	vertex[1].Red = GetRValue(scolor);
	vertex[1].Green = GetGValue(scolor);
	vertex[1].Blue = GetBValue(scolor);
	vertex[1].Alpha = 0x0000;
	GRADIENT_RECT gRect;
	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;
	GradientFill(hdcmem, vertex, 2, &gRect, 1, def);
	HBRUSH pattern = CreatePatternBrush(hbitmap);
	return pattern;
}

HBRUSH UIDrawer::CreateGradientBrush(LPDRAWITEMSTRUCT &item, COLORREF top, COLORREF bottom)
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hDC);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hDC, item->rcItem.right - item->rcItem.left, item->rcItem.bottom - item->rcItem.top);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
	for (int i = 0; i < item->rcItem.bottom - item->rcItem.top; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rcItem.bottom - item->rcItem.top));
		g = int(g1 + double(i * (g2 - g1) / item->rcItem.bottom - item->rcItem.top));
		b = int(b1 + double(i * (b2 - b1) / item->rcItem.bottom - item->rcItem.top));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i;
		temp.right = item->rcItem.right - item->rcItem.left;
		temp.bottom = i + 1;
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);

	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);

	return pattern;
}

HBRUSH UIDrawer::CreateBitmapBrush(HBITMAP bitmap) {
	HBRUSH pattern = CreatePatternBrush(bitmap);
	return pattern;
}

HFONT UIDrawer::DrawFont(int size, int angle, DWORD weight, bool italic, bool underline, bool strike, std::string font)
{
	if (size == 0) {
		size = DEF_FONT_SIZE;
	}
	return CreateFont(size, 0, angle, 0,
		weight, italic, underline, strike,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		font.c_str());
}

BOOL UIDrawer::DrawBitmap(LPDRAWITEMSTRUCT &item, INT x, INT y, HBITMAP hBitmap, DWORD dwROP)
{
	HDC       hDCBits;
	BITMAP    Bitmap;
	BOOL      bResult;

	if (!item->hDC || !hBitmap)
		return FALSE;

	hDCBits = CreateCompatibleDC(item->hDC);
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	SelectObject(hDCBits, hBitmap);
	bResult = BitBlt(item->hDC, x, y, Bitmap.bmWidth, Bitmap.bmHeight, hDCBits, 0, 0, dwROP);
	DeleteDC(hDCBits);

	return bResult;
}

BOOL UIDrawer::DrawCircle(LPDRAWITEMSTRUCT & item, RECT rect, INT linesize, UIDrawer::LineType line, COLORREF linecolor, HBRUSH hbr)
{
	DWORD nline;
	switch (line) {
	case UIDrawer::DotLine:
		nline = PS_DOT;
		break;
	case UIDrawer::SolidLine:
		nline = PS_SOLID;
		break;
	case UIDrawer::DashLine:
		nline = PS_DASH;
		break;
	case UIDrawer::NullLine:
		nline = PS_NULL;
		break;
	}
	//Create pen for button border
	HPEN pen = CreatePen(nline, linesize, linecolor);
	//select object
	HGDIOBJ old_pen = SelectObject(item->hDC, pen);
	HBRUSH hOld = (HBRUSH)SelectObject(item->hDC, hbr);
	//Create
	bool success = Ellipse(item->hDC, rect.left, rect.top, rect.right, rect.bottom);
	//delete
	SelectObject(item->hDC, hOld);
	SelectObject(item->hDC, old_pen);
	DeleteObject(hbr);
	DeleteObject(pen);
	return success;
}

BOOL UIDrawer::DrawRectangle(LPDRAWITEMSTRUCT &item, RECT rect, INT border, INT linesize, UIDrawer::LineType line, COLORREF linecolor, HBRUSH fillcolor)
{
	DWORD nline;
	switch (line) {
	case UIDrawer::DotLine:
		nline = PS_DOT;
		break;
	case UIDrawer::SolidLine:
		nline = PS_SOLID;
		break;
	case UIDrawer::DashLine:
		nline = PS_DASH;
		break;
	case UIDrawer::NullLine:
		nline = PS_NULL;
		break;
	}
	//Create pen for button border
	HPEN pen = CreatePen(nline, linesize, linecolor);
	//Select brush and keep them for being deleted next
	HGDIOBJ old_pen = SelectObject(item->hDC, pen);
	HGDIOBJ old_brush = SelectObject(item->hDC, fillcolor);
	//Create Rect
	bool success = RoundRect(item->hDC, rect.left, rect.top, rect.right, rect.bottom, border, border);
	//Clean up
	SelectObject(item->hDC, old_pen);
	SelectObject(item->hDC, old_brush);
	DeleteObject(pen);
	return success;
}

BOOL DrawFocus(LPDRAWITEMSTRUCT & item) {
	return DrawFocusRect(item->hDC, &item->rcItem);
}

BOOL UIDrawer::DrawString(LPDRAWITEMSTRUCT & item, RECT rect, std::string text, INT size, UIDrawer::TextMargin horizontal, UIDrawer::TextMargin vertical, COLORREF color, HFONT font)
{
	DWORD flags = DWORD();
	switch (horizontal) {
	case UIDrawer::Left:
		flags = flags | DT_LEFT;
		break;
	case UIDrawer::Center:
		flags = flags | DT_CENTER;
		break;
	case UIDrawer::Right:
		flags = flags | DT_RIGHT;
		break;
	}
	switch (vertical) {
	case UIDrawer::Top:
		flags = flags | DT_TOP;
		flags = flags | DT_SINGLELINE;
		break;
	case UIDrawer::Center:
		flags = flags | DT_VCENTER;
		flags = flags | DT_SINGLELINE;
		break;
	case UIDrawer::Bottom:
		flags = flags | DT_BOTTOM;
		flags = flags | DT_SINGLELINE;
		break;
	}
	SelectObject(item->hDC, font);
	SetTextColor(item->hDC, color);
	bool success = DrawText(item->hDC, text.c_str(), -1, &item->rcItem, flags);
	DeleteObject(font);
	return success;
}

