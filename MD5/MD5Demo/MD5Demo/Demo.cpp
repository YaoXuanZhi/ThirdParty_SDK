#include <iostream>
#include <string>
#include "..\..\md5.h"
using namespace std;

void main()
{
	//针对字符串
	cout << "对字符串进行MD5编码如下所示" << endl;
	string DecodeStr = "千秋万载，一统江湖";
	MD5 MD5Instance;
	cout << DecodeStr << "编码后：" << endl << MD5Instance.ToMD5(DecodeStr) << endl;
	system("pause");

	//针对文件
	cout << "检测文件的MD5值如下所示" << endl;
	string FilePath = "test.txt";
	cout << FilePath << "的MD5值为：" << endl << MyMD5::CheckMD5(FilePath) << endl;
	system("pause");
}