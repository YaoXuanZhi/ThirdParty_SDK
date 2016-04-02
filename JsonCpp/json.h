// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef JSON_JSON_H_INCLUDED
#define JSON_JSON_H_INCLUDED

#include "autolink.h"
#include "value.h"
#include "reader.h"
#include "writer.h"
#include "features.h"

#include <string>
#include <vector>


//本人拓展的JSON读取函数函数
namespace JsonEx{
	using namespace std;
	Json::Value GetValueByJSON(string JSONPath)
	{
		Json::Value ResValue;
		ifstream ifs;
		ifs.open(JSONPath);
		if (!ifs.is_open())
		{
			std::cout << "没有打开JOSN文件" << std::endl;
		}
		else
		{
			Json::Reader reader;
			Json::Value JSONRoot;
			if (!reader.parse(ifs, JSONRoot, false))
			{
				std::cout << "此.json文件数据结构已损坏" << std::endl;
			}
			else
			{
				ResValue = JSONRoot;
			}
			ifs.close();
		}
		return ResValue;
	}


	void CreateFileByJSONObj(string JSONPath, Json::Value JSONRoot)
	{
		//将JSON对象转化为字符串
		Json::FastWriter writer;
		std::string json_file = writer.write(JSONRoot);
		//写入到文件中
		std::ofstream ofs;
		ofs.open(JSONPath.c_str());
		ofs << json_file;
		ofs.close();
	}



	//定义一个函数模板来读取JSON对象里的一维组哦
	bool ReadSingleArraryInJSON(Json::Value SingleArraryValue, std::vector<string> &TemplateTypeVector)
	{
		bool IsOK = true;
		if (SingleArraryValue.isArray())
		{
			if (SingleArraryValue.size() > 0)
			{
				for (size_t n = 0; n < SingleArraryValue.size(); n++)
				{
					TemplateTypeVector.push_back(SingleArraryValue[n].asString());
				}
			}
			else
			{
				IsOK = false;
			}
		}
		else
		{
			IsOK = false;
		}
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
				{
					TemplateTypeVector.push_back(SingleArraryValue[n].asString());
				}
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
				else{
					IsOK = false;
				}
			}
		}
		else
		{
			//cout << "此数据不是数组" << endl;
			IsOK = false;
		}
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
#endif // JSON_JSON_H_INCLUDED
