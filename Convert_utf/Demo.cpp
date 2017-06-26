#include "convert_utf.h"
#include <string>

typedef wchar_t UTF16Char;
typedef char UTF8Char;

#ifndef COUNT_OF
#define COUNT_OF(array)			(sizeof(array)/sizeof(array[0]))
#endif

#define UTF16_STR_BUFF_SIZE		4096
#define UTF8_STR_BUFF_SIZE		8192

void UTF8ToUTF16(const UTF8Char *utf8, size_t length, std::basic_string<UTF16Char> &utf16)
{
	UTF16Char output[UTF16_STR_BUFF_SIZE] = { 0 };
	const UTF8 *src_begin = reinterpret_cast<const UTF8 *>(utf8);
	const UTF8 *src_end = src_begin + length;
	UTF16 *dst_begin = reinterpret_cast<UTF16 *>(output);

	utf16.resize(0);
	while (src_begin < src_end)
	{
		ConversionResult result = ConvertUTF8toUTF16(&src_begin,
			src_end,
			&dst_begin,
			dst_begin + COUNT_OF(output),
			lenientConversion);

		utf16.append(output, dst_begin - reinterpret_cast<UTF16 *>(output));
		dst_begin = reinterpret_cast<UTF16 *>(output);
		if (result == sourceIllegal || result == sourceExhausted)
		{
			utf16.resize(0);
			break;
		}
	}
}

void UTF16ToUTF8(const UTF16Char *utf16, size_t length, std::basic_string<UTF8Char> &utf8)
{
	UTF8Char output[UTF8_STR_BUFF_SIZE];
	const UTF16 *src_begin = reinterpret_cast<const UTF16 *>(utf16);
	const UTF16 *src_end = src_begin + length;
	UTF8 *dst_begin = reinterpret_cast<UTF8 *>(output);

	utf8.resize(0);
	while (src_begin < src_end)
	{
		ConversionResult result = ConvertUTF16toUTF8(&src_begin,
			src_end,
			&dst_begin,
			dst_begin + COUNT_OF(output),
			lenientConversion);

		utf8.append(output, dst_begin - reinterpret_cast<UTF8 *>(output));
		dst_begin = reinterpret_cast<UTF8 *>(output);
		if (result == sourceIllegal || result == sourceExhausted)
		{
			utf8.resize(0);
			break;
		}
	}
}

void UTF8ToUTF16(const std::basic_string<UTF8Char> &utf8, std::basic_string<UTF16Char> &utf16)
{
	UTF8ToUTF16(utf8.c_str(), utf8.length(), utf16);
}

void UTF16ToUTF8(const std::basic_string<UTF16Char> &utf16, std::basic_string<UTF8Char> &utf8)
{
	UTF16ToUTF8(utf16.c_str(), utf16.length(), utf8);
}


int main()
{
	setlocale(LC_ALL,"chinese-simplified");
	std::basic_string<UTF16Char> szUtf161 = L"Utf16×Ö·û±àÂë";
	std::basic_string<UTF8Char> szUtf81;
	UTF16ToUTF8(szUtf161,szUtf81);
	printf("utf8%s\n",&szUtf81[0]);
	std::basic_string<UTF16Char> szUtf162;
	UTF8ToUTF16(szUtf81,szUtf162);
	wprintf(L"utf16%s\n",&szUtf162[0]);
	getchar();
	return 0;
}