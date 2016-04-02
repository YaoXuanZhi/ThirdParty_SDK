#ifndef __EXTENSIONS_H__
#define __EXTENSIONS_H__

#include <set>
#include <string>
#include "ci_string.h"
#include "ParserDom.h"
namespace htmlcxx
{
	class Extensions
	{
		public:
			Extensions() {}

			Extensions(const std::string &exts);

			~Extensions() {}

			bool check(const std::string &url);
			void insert(const ci_string &ext) { mExts.insert(ext); }

			//SourceStr:被分割的字符串
			//FirstFlag:分割的起始标记
			//FinalFlag:分割的末尾标记
			static std::vector<std::string> GetArrBySpliteString(std::string SourceStr, std::string FirstFlag, std::string FinalFlag);

			//将字符串里的小写转换成大写
			static std::string SmallCharToBigChar(const char* Str);
			//定义一个函数来判断一个字符串里是否含有脏字，第一个参数是待判断的字符串，第二个参数是脏字库
			static bool FilterStr(std::string Str, std::vector<std::string>& FilterLib, int ModeFlag);
			//全局替换字符串
			static void GlobalReStr(std::string& str, std::string old_value, std::string new_value);
		private:
			std::set<ci_string> mExts;
	};
}

#endif
