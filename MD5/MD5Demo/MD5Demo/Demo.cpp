#include <iostream>
#include <string>
#include "..\..\md5.h"
using namespace std;

void main()
{
	//����ַ���
	cout << "���ַ�������MD5����������ʾ" << endl;
	string DecodeStr = "ǧ�����أ�һͳ����";
	MD5 MD5Instance;
	cout << DecodeStr << "�����" << endl << MD5Instance.ToMD5(DecodeStr) << endl;
	system("pause");

	//����ļ�
	cout << "����ļ���MD5ֵ������ʾ" << endl;
	string FilePath = "test.txt";
	cout << FilePath << "��MD5ֵΪ��" << endl << MyMD5::CheckMD5(FilePath) << endl;
	system("pause");
}