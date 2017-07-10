//Created by Onelio

#ifndef _UI_MANAGER_UTIL_VIEW_HANDLER
#define _UI_MANAGER_UTIL_VIEW_HANDLER

#define _AFXDLL
#include <afxwin.h>
#include <string>

#include "..\View.h"

namespace vh {
	std::string	getView(UIManager::ViewType input);
};

#endif //_UI_MANAGER_UTIL_VIEW_HANDLER