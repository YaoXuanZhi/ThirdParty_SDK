#include <cstring>
#include "Extensions.h"

using namespace std;
using namespace htmlcxx;

Extensions::Extensions(const string &exts)
{
	const char *begin = exts.c_str();
	while (*begin)
	{
		while (*begin == ' ') ++begin;
		if (*begin == 0) break;

		const char *end = begin + 1;
		while (*end && *end != ' ') ++end;

		insert(ci_string(begin, end));

		begin = end;
	}
}

bool Extensions::check(const string &url)
{
	const char *slash;
	const char *dot;
	const char *question;

	question = strchr(url.c_str(), '?');

	if (question) return false;
	
	slash = strrchr(url.c_str(), '/');
	dot = strrchr(url.c_str(), '.');

	if (slash >= dot) return false;
	
	ci_string ext(dot);
	
	return mExts.find(ext) != mExts.end();
}





//将字符串里的小写转换成大写
std::string Extensions::SmallCharToBigChar(const char* Str)
{
	std::string TempStr(Str);
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//将所有小写字母转换成大写
	return TempStr;
}




//定义一个函数来判断一个字符串里是否含有脏字，第一个参数是待判断的字符串，第二个参数是脏字库
bool Extensions::FilterStr(std::string Str, std::vector<std::string>& FilterLib, int ModeFlag)
{
	int FilterCount = FilterLib.size();//获得容器里元素的个数
	int MatchCount = 0;//定义一个匹配个数计数器
	//定义一个变量来判断
	bool ResultFlag = false;//如果始终为0(false)，那么说明这个字符串里没有脏字
	switch (ModeFlag)
	{
	case 1://全字匹配保存
	{
			   ModeFlag = FilterCount;
			   //由于这个FilterLib只有在初始化时才能知道其值的，所以这里不能够使用sizeof(FilterLib) / sizeof(FilterLib[1])的方式来获得此数组的个数，必须预先指定，所以为其设置一个计数器，和argc argv相似
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//添加两个处理机制，1.搜索完所有脏字库或者是找到一个匹配后就中止，节省时间
			   {
				   //首先，这个找到的位置标记绝对不会大于字符串本身长度，而且索引好必定大于-1，本来应该设置为-1的，不过由于编译器在编译时有时候会将其认定为
				   //Str.find(FilterLib[i]) < strlen(Str.c_str()) ? cout << "Yes" << endl : cout << "No" << endl;
				   //Str.find(FilterLib[i])>-1 ? cout << "Yes" << endl : cout << "No" << endl;//通过这个判断可以知道，有时候-1会被认定为其它数值，以此作为判断并不可靠，将>-1改为>=0即可
				   //Str.find(FilterLib[i])>=0 ? cout << "Yes" << endl : cout << "No" << endl;//这里就能够很好地证明了
				   if (Str.find(FilterLib[i].c_str()) < strlen(Str.c_str()) && Str.find(FilterLib[i].c_str()) >= 0)
				   {
					   //ResultFlag = Str.find(FilterLib[i]);
					   MatchCount++;
				   }
			   }
			   if (MatchCount == ModeFlag)
			   {
				   ResultFlag = true;
			   }
	}; break;
	case 2://部分匹配保存
	{
			   ModeFlag = 1;
			   //由于这个FilterLib只有在初始化时才能知道其值的，所以这里不能够使用sizeof(FilterLib) / sizeof(FilterLib[1])的方式来获得此数组的个数，必须预先指定，所以为其设置一个计数器，和argc argv相似
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//添加两个处理机制，1.搜索完所有脏字库或者是找到一个匹配后就中止，节省时间
			   {
				   if (Str.find(FilterLib[i].c_str()) < strlen(Str.c_str()) && Str.find(FilterLib[i].c_str()) >= 0)
				   {
					   MatchCount++;
				   }
			   }
			   if (MatchCount == ModeFlag)
			   {
				   ResultFlag = true;
			   }
	}; break;
	}
	return ResultFlag;
}



//SourceStr:被分割的字符串
//FirstFlag:分割的起始标记
//FinalFlag:分割的末尾标记
std::vector<std::string> Extensions::GetArrBySpliteString(std::string SourceStr, std::string FirstFlag, std::string FinalFlag)
{
	int ROffset = 0;
	std::vector<std::string>SpliteResult;
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//得到起始标记De所在index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//得到末尾标记的所在index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult.push_back(SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str())));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}





//全局替换字符串
void Extensions::GlobalReStr(std::string&   str, std::string old_value, std::string new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
}
