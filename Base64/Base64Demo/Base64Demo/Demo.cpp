#include <iostream>
#include <string>
#include "..\..\Base64.h"
using namespace std;

void main()
{
	cout << "���ַ�������Base64����������ʾ" << endl;
	string DecodeStr = "ǧ�����أ�һͳ����";
	cout << DecodeStr << "�����" << endl << Base64::encode(DecodeStr) << endl;
	system("pause");

	cout << "��Base64�ַ������н���������ʾ" << endl;
	string EncodeStr = "x6fH783y1NijrNK7zbO9rbr+";
	cout << EncodeStr << "�����" << endl << Base64::decode(EncodeStr) << endl;
	system("pause");
}