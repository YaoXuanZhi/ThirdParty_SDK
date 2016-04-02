#include <iostream>
#include <string>
#include "..\..\Base64.h"
using namespace std;

void main()
{
	cout << "对字符串进行Base64编码如下所示" << endl;
	string DecodeStr = "千秋万载，一统江湖";
	cout << DecodeStr << "编码后：" << endl << Base64::encode(DecodeStr) << endl;
	system("pause");

	cout << "对Base64字符串进行解码如下所示" << endl;
	string EncodeStr = "x6fH783y1NijrNK7zbO9rbr+";
	cout << EncodeStr << "解码后：" << endl << Base64::decode(EncodeStr) << endl;
	system("pause");
}