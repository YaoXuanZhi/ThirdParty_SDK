#include "convert_wrapper.h"
using namespace UtfSet;

int main()
{
	setlocale(LC_ALL,"chs");
	std::wstring szUtf161 = L"Utf16×Ö·û±àÂë";
	std::string szUtf81;
	UTF16ToUTF8(szUtf161,szUtf81);
	printf("utf8 --> %s\n",szUtf81.c_str());
    std::wstring szUtf162;
	UTF8ToUTF16(szUtf81,szUtf162);
	wprintf(L"utf16 --> %s\n",szUtf162.c_str());
	std::wstring szUtf163 = L"UNICODE×Ö·û¼¯";
	std::string szMbcs1;
    UTF16ToMBCS(szUtf163, szMbcs1);
    printf("mbcs -- > %s\n", szMbcs1.c_str());
	std::wstring szUtf164;
	std::string szMbcs2 = "MBCS×Ö·û¼¯";
    MBCSToUTF16(szMbcs2, szUtf164);
    wprintf(L"wchar --> %s\n", szUtf164.c_str());
	getchar();
	return 0;
}
