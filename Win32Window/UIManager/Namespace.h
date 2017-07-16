

#ifndef _UI_MANAGER_NAMESPACE_HEADER
#define _UI_MANAGER_NAMESPACE_HEADER

#define _AFXDLL
#include <SDKDDKVer.h>
#include <afxwin.h>

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

struct UIManager::Coordinates {
	int x = 0;
	int y = 0;
	WPARAM flags = NULL; //MK_CONTROL, MK_LBUTTON, MK_MBUTTON, MK_RBUTTON, MK_SHIFT
};

#endif //_UI_MANAGER_NAMESPACE_HEADER