#ifndef __CONVERT_WRAPPER_H
#define __CONVERT_WRAPPER_H
#include <string>
namespace UtfSet
{
	void UTF8ToUTF16(const char *utf8, size_t length, std::wstring &utf16);
	void UTF16ToUTF8(const wchar_t *utf16, size_t length, std::string &utf8);
	void UTF8ToUTF16(const std::string &utf8, std::wstring &utf16);
	void UTF16ToUTF8(const std::wstring &utf16, std::string &utf8);
	void UTF16ToMBCS(const std::wstring &utf16, std::string &mbcs);
	void MBCSToUTF16(const std::string &mbcs, std::wstring &utf16);
}
#endif
