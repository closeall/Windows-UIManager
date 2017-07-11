#include "FormatFactory.h"

std::wstring FormatFactory::StringToWString(std::string str, int codepage)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), 0, 0);
	std::wstring strTo(size_needed, 0);
	MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &strTo[0], size_needed);
	return strTo;
}

std::string FormatFactory::WStringToString(std::wstring str, int codepage)
{
	if (str.empty()) return std::string();
	int size_needed = WideCharToMultiByte(codepage, 0, &str[0], (int)str.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(codepage, 0, &str[0], (int)str.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
