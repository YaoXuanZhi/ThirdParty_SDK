#include "JsonCpp/json.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
//本人拓展的JSON读取函数函数
namespace JsonEx{
	using namespace std;
	Json::Value GetValueByJSON(string JSONPath)
	{
		Json::Value ResValue;
		ifstream ifs;
		ifs.open(JSONPath);
		if (!ifs.is_open())
			std::cout << "没有打开JOSN文件" << std::endl;
		else{
			Json::Reader reader;
			Json::Value JSONRoot;
			if (!reader.parse(ifs, JSONRoot, false))
				std::cout << "此.json文件数据结构已损坏" << std::endl;
			else
				ResValue = JSONRoot;
			ifs.close();
		}
		return ResValue;
	}

	void CreateFileByJSONObj(string JSONPath, Json::Value JSONRoot){
		//将JSON对象转化为字符串
		Json::FastWriter writer;
		std::string json_file = writer.write(JSONRoot);
		//写入到文件中
		std::ofstream ofs;
		ofs.open(JSONPath.c_str());
		ofs << json_file;
		ofs.close();
	}

	//定义一个函数来读取JSON对象里的一维组哦
	bool ReadSingleArraryInJSON(Json::Value SingleArraryValue, std::vector<string> &TemplateTypeVector)
	{
		bool IsOK = true;
		if (SingleArraryValue.isArray())
		{
			if (SingleArraryValue.size() > 0)
			{
				for (size_t n = 0; n < SingleArraryValue.size(); n++)
					TemplateTypeVector.push_back(SingleArraryValue[n].asString());
			}
			else
				IsOK = false;
		}
		else
			IsOK = false;
		return IsOK;
	}

	//定义一个函数模板来读取JSON对象里的一维组哦
	std::vector<string> ReadSingleArraryInJSON(Json::Value SingleArraryValue)
	{
		std::vector<string> TemplateTypeVector;
		if (SingleArraryValue.isArray())
		{
			if (SingleArraryValue.size() > 0)
			{
				for (size_t n = 0; n < SingleArraryValue.size(); n++)
					TemplateTypeVector.push_back(SingleArraryValue[n].asString());
			}
		}
		return TemplateTypeVector;
	}

	//定义一个二维数组结构体类型
	struct TwoDArray{
		std::string one;
		std::string two;
		//重载内部运算符==，在重载内部运算符时，自身将作为一个输入参数哦
		//正如==，需要两个输入参数，但由于其重载的是内部运算符，所以仅需输入一个参数即可
		bool operator==(TwoDArray value2)
		{
			return (value2.one == one && value2.two == two);
		};

		//重载输出流运算符<<，需要声明其为友元函数
		friend std::ostream& operator<<(std::ostream& out,TwoDArray& value) {
			out << "one=" << value.one << "\n" << "two=" << value.two;
			return out;
		}
	};

	bool ReadMultipleArraryInJSON(Json::Value MultipleArraryValue, std::vector<TwoDArray> &TemplateTypeVector)
	{
		bool IsOK = true;
		//判断当前数据是否是一个包含子数组的数组
		if (MultipleArraryValue.isArray() && MultipleArraryValue[0].isArray())
		{
			//cout << MultipleArraryValue.size() << endl;
			for (size_t n = 0; n < MultipleArraryValue.size(); n++)
			{
				TwoDArray TempBase;
				//遍历当前数组下的子数组，初始化临时变量TempBase
				Json::Value SubArraryValue = MultipleArraryValue[n];
				if (SubArraryValue.size() == 2)
				{
					TempBase.one = SubArraryValue[0].asString();
					TempBase.two = SubArraryValue[1].asString();
					//将初始化后的TempBase添加到NodePropLIB容器中
					TemplateTypeVector.push_back(TempBase);
				}
				else
					IsOK = false;
			}
		}else
			//cout << "此数据不是数组" << endl;
			IsOK = false;
		return IsOK;
	}


	std::vector<TwoDArray>  ReadMultipleArraryInJSON(Json::Value MultipleArraryValue)
	{
		std::vector<TwoDArray> TemplateTypeVector;
		//判断当前数据是否是一个包含子数组的数组
		if (MultipleArraryValue.isArray() && MultipleArraryValue[0].isArray())
		{
			//cout << MultipleArraryValue.size() << endl;
			for (size_t n = 0; n < MultipleArraryValue.size(); n++)
			{
				TwoDArray TempBase;
				//遍历当前数组下的子数组，初始化临时变量TempBase
				Json::Value SubArraryValue = MultipleArraryValue[n];
				if (SubArraryValue.size() == 2)
				{
					TempBase.one = SubArraryValue[0].asString();
					TempBase.two = SubArraryValue[1].asString();
					//将初始化后的TempBase添加到NodePropLIB容器中
					TemplateTypeVector.push_back(TempBase);
				}
			}
		}
		return TemplateTypeVector;
	}


}



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
	root["dfadf"] = "辣椒粉";
	root["aaaa"] = "009";
	cout << root << endl;
	system("pause");

	//遍历同级节点
#define USEARRINDEX
#ifndef USEARRINDEX
	//迭代器方式
	//Json::Value::Members member;//Members 这玩意就是vector<string>，typedef了而已
	for (Json::Value::iterator itr = root.begin(); itr != root.end(); itr++)
	{
		cout << itr.name() << "=" << (*itr).asString() << endl;
	}
#else
	//数组方式
	Json::Value::Members NodeArr = root.getMemberNames();
	for (size_t m = 0; m < NodeArr.size(); m++)
	{
		cout << NodeArr[m].c_str() << "="<< root[NodeArr[m]].asString() << endl;
	}
#endif
	system("pause");
}