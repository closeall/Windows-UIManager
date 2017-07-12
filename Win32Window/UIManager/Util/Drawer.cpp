#include "Drawer.h"

BOOL DrawBitmap(HDC hDC, INT x, INT y, HBITMAP hBitmap, DWORD dwROP)
{
	HDC       hDCBits;
	BITMAP    Bitmap;
	BOOL      bResult;

	if (!hDC || !hBitmap)
		return FALSE;

	hDCBits = CreateCompatibleDC(hDC);
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	SelectObject(hDCBits, hBitmap);
	bResult = BitBlt(hDC, x, y, Bitmap.bmWidth, Bitmap.bmHeight, hDCBits, 0, 0, dwROP);
	DeleteDC(hDCBits);

	return bResult;
}
