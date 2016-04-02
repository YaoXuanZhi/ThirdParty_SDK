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





//���ַ������Сдת���ɴ�д
std::string Extensions::SmallCharToBigChar(const char* Str)
{
	std::string TempStr(Str);
	transform(TempStr.begin(), TempStr.end(), TempStr.begin(), ::toupper);//������Сд��ĸת���ɴ�д
	return TempStr;
}




//����һ���������ж�һ���ַ������Ƿ������֣���һ�������Ǵ��жϵ��ַ������ڶ������������ֿ�
bool Extensions::FilterStr(std::string Str, std::vector<std::string>& FilterLib, int ModeFlag)
{
	int FilterCount = FilterLib.size();//���������Ԫ�صĸ���
	int MatchCount = 0;//����һ��ƥ�����������
	//����һ���������ж�
	bool ResultFlag = false;//���ʼ��Ϊ0(false)����ô˵������ַ�����û������
	switch (ModeFlag)
	{
	case 1://ȫ��ƥ�䱣��
	{
			   ModeFlag = FilterCount;
			   //�������FilterLibֻ���ڳ�ʼ��ʱ����֪����ֵ�ģ��������ﲻ�ܹ�ʹ��sizeof(FilterLib) / sizeof(FilterLib[1])�ķ�ʽ����ô�����ĸ���������Ԥ��ָ��������Ϊ������һ������������argc argv����
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//�������������ƣ�1.�������������ֿ�������ҵ�һ��ƥ������ֹ����ʡʱ��
			   {
				   //���ȣ�����ҵ���λ�ñ�Ǿ��Բ�������ַ��������ȣ����������ñض�����-1������Ӧ������Ϊ-1�ģ��������ڱ������ڱ���ʱ��ʱ��Ὣ���϶�Ϊ
				   //Str.find(FilterLib[i]) < strlen(Str.c_str()) ? cout << "Yes" << endl : cout << "No" << endl;
				   //Str.find(FilterLib[i])>-1 ? cout << "Yes" << endl : cout << "No" << endl;//ͨ������жϿ���֪������ʱ��-1�ᱻ�϶�Ϊ������ֵ���Դ���Ϊ�жϲ����ɿ�����>-1��Ϊ>=0����
				   //Str.find(FilterLib[i])>=0 ? cout << "Yes" << endl : cout << "No" << endl;//������ܹ��ܺõ�֤����
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
	case 2://����ƥ�䱣��
	{
			   ModeFlag = 1;
			   //�������FilterLibֻ���ڳ�ʼ��ʱ����֪����ֵ�ģ��������ﲻ�ܹ�ʹ��sizeof(FilterLib) / sizeof(FilterLib[1])�ķ�ʽ����ô�����ĸ���������Ԥ��ָ��������Ϊ������һ������������argc argv����
			   for (int i = 0; i < FilterCount&&MatchCount < ModeFlag; i++)//�������������ƣ�1.�������������ֿ�������ҵ�һ��ƥ������ֹ����ʡʱ��
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



//SourceStr:���ָ���ַ���
//FirstFlag:�ָ����ʼ���
//FinalFlag:�ָ��ĩβ���
std::vector<std::string> Extensions::GetArrBySpliteString(std::string SourceStr, std::string FirstFlag, std::string FinalFlag)
{
	int ROffset = 0;
	std::vector<std::string>SpliteResult;
	while (SourceStr.find(FirstFlag, ROffset) >= 0 && SourceStr.find(FirstFlag, ROffset) <= strlen(SourceStr.c_str()))
	{
		int findex = SourceStr.find(FirstFlag, ROffset);//�õ���ʼ���De����index
		int sindex = SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str()));//�õ�ĩβ��ǵ�����index
		if (SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) >= 0 && SourceStr.find(FinalFlag, findex + strlen(FirstFlag.c_str())) <= strlen(SourceStr.c_str()))
		{
			SpliteResult.push_back(SourceStr.substr(findex + strlen(FirstFlag.c_str()), sindex - findex - strlen(FirstFlag.c_str())));
		}
		ROffset = sindex;
	}
	return SpliteResult;
}





//ȫ���滻�ַ���
void Extensions::GlobalReStr(std::string&   str, std::string old_value, std::string new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
}
