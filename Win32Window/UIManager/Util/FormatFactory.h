//Developed by Onelio
//Created on 26/11/2016
//Easy variable parser

#ifndef _UI_MANAGER_UTIL_FORMAT_FACTORY
#define _UI_MANAGER_UTIL_FORMAT_FACTORY

#define _AFXDLL
#include <afxwin.h>
#include <string>

namespace FormatFactory {
	std::wstring	StringToWString(std::string input, int codepage = CP_UTF8);
	std::string		WStringToString(std::wstring input, int codepage = CP_UTF8);
};

#endif //_UI_MANAGER_UTIL_FORMAT_FACTORY