//Դ����Ҫ��Դ�ڣ�http://www.cnblogs.com/kex1n/archive/2011/12/02/2272328.html
#include <stdio.h>
#include <iostream>
#include <tchar.h>
////��ͷ�ļ������ҷ�װ�Ĳ��ֺ�������Ҫ�Ƕ�ȡJSON��д��JSON�������ռ�ΪJsonEx
#include "JsonCpp\json.h"

using namespace std;
int Example001()
{
	ifstream ifs;
	ifs.open("testjson1.json");
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		return -1;
	}
	std::string name = root["name"].asString();
	int age = root["age"].asInt();
	std::cout << name << std::endl;
	std::cout << age << std::endl;
	return 0;

}


int Example002()
{
	ifstream ifs;
	ifs.open("testjson2.json");
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		return -1;
	}
	std::string name;
	int age;
	int size = root.size();
	for (int i = 0; i<size; ++i)
	{
		name = root[i]["name"].asString();
		age = root[i]["age"].asInt();
		std::cout << name << " " << age << std::endl;
	}
	return 0;
}


int Example003()
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;
	person["name"] = "hello world";
	person["age"] = 100;
	root.append(person);
	std::string json_file = writer.write(root);
	ofstream ofs;
	ofs.open("test1.json");
	ofs << json_file;
	return 0;
}


void main()
{
	Json::Value root;
	root["name"] = "hello world";
	root["age"] = 100;
	root["dfadf"] = "������";
	root["aaaa"] = "009";
	cout << root << endl;
	system("pause");

	//����ͬ���ڵ�
#define USEARRINDEX
#ifndef USEARRINDEX
	//��������ʽ
	//Json::Value::Members member;//Members ���������vector<string>��typedef�˶���
	for (Json::Value::iterator itr = root.begin(); itr != root.end(); itr++)
	{
		cout << itr.name() << "=" << (*itr).asString() << endl;
	}
#else
	//���鷽ʽ
	Json::Value::Members NodeArr = root.getMemberNames();
	for (size_t m = 0; m < NodeArr.size(); m++)
	{
		cout << NodeArr[m].c_str() << "="<< root[NodeArr[m]].asString() << endl;
	}
#endif
	system("pause");
}