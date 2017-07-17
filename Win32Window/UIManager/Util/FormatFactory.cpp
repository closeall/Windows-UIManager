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

static int HexadecimalToDecimal(std::string hex) {
	size_t hexLength = hex.length();
	double dec = 0;

	for (unsigned int i = 0; i < hexLength; ++i)
	{
		char b = hex[i];

		if (b >= 48 && b <= 57)
			b -= 48;
		else if (b >= 65 && b <= 70)
			b -= 55;

		dec += b * pow(16, ((hexLength - i) - 1));
	}

	return (int)dec;
}

COLORREF FormatFactory::hexToColor(std::string hex)
{
	if (hex[0] == '#')
		hex = hex.erase(0, 1);
	unsigned int r = (unsigned char)HexadecimalToDecimal(hex.substr(0, 2));
	unsigned int g = (unsigned char)HexadecimalToDecimal(hex.substr(2, 2));
	unsigned int b = (unsigned char)HexadecimalToDecimal(hex.substr(4, 2));
	return RGB(r, g, b);
}
