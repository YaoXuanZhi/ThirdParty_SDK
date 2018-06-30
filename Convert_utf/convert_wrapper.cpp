#include "convert_wrapper.h"
#include "convert_utf.h"

#define UTF16_STR_BUFF_SIZE		4096
#define UTF8_STR_BUFF_SIZE		8192

#ifndef COUNT_OF
#define COUNT_OF(array)			(sizeof(array)/sizeof(array[0]))
#endif

namespace UtfSetHelper
{
	//MBCS字符集里，0~127都是一个字符对应一个字节，其余字符对应两个字节
	//UTF16字符集里，一个字符直接对应两个字节
	//Note:	wcstombs、mbstowcs受到local的影响哦，需要设置setlocale(LC_ALL, "chs");
	//Refrence:https://blog.csdn.net/harry_lyc/article/details/6573147
	static size_t GetWCharCount(const std::string &str)
	{
		size_t size = 0;
		size_t length = str.length();
		for (size_t n = 0; n < length; n++)
		{
			n += (str.at(n) >= 0 && str.at(n) <= 127) ? 0 : 2;
			size += sizeof(wchar_t);
		}
		return size;
	}

	static void WChar2Mbcs(const std::wstring &utf16, std::string &mbcs)
	{
		if (utf16.length() < 1) return;
		size_t size = utf16.length() * sizeof(wchar_t);
		mbcs.resize(size);
		wcstombs(&mbcs[0], &utf16[0],size);
	}

	static void Mbcs2WChar(const std::string &mbcs, std::wstring &utf16)
	{
		if (mbcs.length() < 1) return;
		size_t size_wc = GetWCharCount(mbcs);
		utf16.resize(size_wc);
		mbstowcs(&utf16[0], &mbcs[0], size_wc);
	}
}

void UtfSet::UTF8ToUTF16(const char *utf8, size_t length, std::wstring &utf16)
{
	wchar_t output[UTF16_STR_BUFF_SIZE] = { 0 };
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

void UtfSet::UTF16ToUTF8(const std::wstring &utf16, std::string &utf8)
{
	UTF16ToUTF8(utf16.c_str(), utf16.length(), utf8);
}

void UtfSet::UTF16ToMBCS(const std::wstring &utf16, std::string &mbcs)
{
	UtfSetHelper::WChar2Mbcs(utf16,mbcs);
}

void UtfSet::MBCSToUTF16(const std::string &mbcs, std::wstring &utf16)
{
	UtfSetHelper::Mbcs2WChar(mbcs, utf16);
}

void UtfSet::UTF16ToUTF8(const wchar_t *utf16, size_t length, std::string &utf8)
{
	char output[UTF8_STR_BUFF_SIZE];
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

void UtfSet::UTF8ToUTF16(const std::string &utf8, std::wstring &utf16)
{
	UTF8ToUTF16(utf8.c_str(), utf8.length(), utf16);
}

#undef COUNT_OF
#undef UTF8_STR_BUFF_SIZE
#undef UTF16_STR_BUFF_SIZE
