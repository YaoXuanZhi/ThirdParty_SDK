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

			//SourceStr:���ָ���ַ���
			//FirstFlag:�ָ����ʼ���
			//FinalFlag:�ָ��ĩβ���
			static std::vector<std::string> GetArrBySpliteString(std::string SourceStr, std::string FirstFlag, std::string FinalFlag);

			//���ַ������Сдת���ɴ�д
			static std::string SmallCharToBigChar(const char* Str);
			//����һ���������ж�һ���ַ������Ƿ������֣���һ�������Ǵ��жϵ��ַ������ڶ������������ֿ�
			static bool FilterStr(std::string Str, std::vector<std::string>& FilterLib, int ModeFlag);
			//ȫ���滻�ַ���
			static void GlobalReStr(std::string& str, std::string old_value, std::string new_value);
		private:
			std::set<ci_string> mExts;
	};
}

#endif
