

#ifndef _UI_MANAGER_NAMESPACE_HEADER
#define _UI_MANAGER_NAMESPACE_HEADER

#include <windows.h> //Win32 API Lib

namespace UIManager {
	//Window
	class WindowManager;
	enum wStartState;
	//Views
	class View;
	enum ViewType;
	//Managers
	HBITMAP BitMap(std::string url);
}

#endif //_UI_MANAGER_NAMESPACE_HEADER