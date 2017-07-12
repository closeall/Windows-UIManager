//Developed by Onelio
//Created on 11/07/2017
//Easy variable parser

#ifndef _UI_MANAGER_UTIL_DRAWER_HEADER
#define _UI_MANAGER_UTIL_DRAWER_HEADER

#define _AFXDLL
#include <afxwin.h>
#include <string>

BOOL DrawBitmap(HDC hDC, INT x, INT y, HBITMAP hBitmap, DWORD dwROP = SRCCOPY);

#endif //_UI_MANAGER_UTIL_DRAWER_HEADER

/*case WM_DRAWITEM: //Draw control data
	{
		LPDRAWITEMSTRUCT lpDrawItem;
		HBRUSH hBrush;
		int state;

		lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
		SetTextAlign(lpDrawItem->hDC, TA_CENTER | TA_BOTTOM);
		hBrush = CreateSolidBrush(RGB(255, 255, 0)); //Text Ellipse color
		SelectObject(lpDrawItem->hDC, hBrush);
		SetPolyFillMode(lpDrawItem->hDC, ALTERNATE);
		SetBkColor(lpDrawItem->hDC, RGB(255, 255, 0)); //Text Back color

		if (lpDrawItem->CtlType != ODT_BUTTON)
			return FALSE;

		state = lpDrawItem->itemState;

		if (state & ODS_SELECTED)
		{
			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = 70;
			rect.bottom = 70;
			Ellipse(lpDrawItem->hDC, 0, 0, 50, 50);
			FillRect(lpDrawItem->hDC, &rect, NULL);
DrawBitmap(lpDrawItem->hDC, 0, 0, UIManager::BitMap("m.bmp"), SRCCOPY);
TextOut(lpDrawItem->hDC, 25, 35, "Xy", 2);
		}
		else
		{
			TRIVERTEX vertex[2];
			vertex[0].x = 0;
			vertex[0].y = 0;
			vertex[0].Red = 0x0000;
			vertex[0].Green = 0x8000;
			vertex[0].Blue = 0x8000;
			vertex[0].Alpha = 0x0000;

			vertex[1].x = 300;
			vertex[1].y = 80;
			vertex[1].Red = 0x0000;
			vertex[1].Green = 0xd000;
			vertex[1].Blue = 0xd000;
			vertex[1].Alpha = 0x0000;

			// Create a GRADIENT_RECT structure that 
			// references the TRIVERTEX vertices. 
			GRADIENT_RECT gRect;
			gRect.UpperLeft = 0;
			gRect.LowerRight = 1;

			// Draw a shaded rectangle. 
			GradientFill(lpDrawItem->hDC, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
			Ellipse(lpDrawItem->hDC, 0, 0, 50, 50);
			TextOut(lpDrawItem->hDC, 25, 35, "5", 1);
		}

		DeleteObject(hBrush);
		return true;
	}*/