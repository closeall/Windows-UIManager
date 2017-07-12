

#ifndef _UI_MANAGER_NAMESPACE_HEADER
#define _UI_MANAGER_NAMESPACE_HEADER

#define _AFXDLL
#include <afxwin.h>

namespace UIManager {
	//Window
	class WindowManager;
	enum wStartState;
	//Views
	class View;
	enum ViewType;
	enum ViewMargin;
	enum CaseType;
	struct InputRule;
	//Managers
	HBITMAP BitMap(std::string url);
}

#endif //_UI_MANAGER_NAMESPACE_HEADER