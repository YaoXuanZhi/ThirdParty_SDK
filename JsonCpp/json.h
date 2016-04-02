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


//������չ��JSON��ȡ��������
namespace JsonEx{
	using namespace std;
	Json::Value GetValueByJSON(string JSONPath)
	{
		Json::Value ResValue;
		ifstream ifs;
		ifs.open(JSONPath);
		if (!ifs.is_open())
		{
			std::cout << "û�д�JOSN�ļ�" << std::endl;
		}
		else
		{
			Json::Reader reader;
			Json::Value JSONRoot;
			if (!reader.parse(ifs, JSONRoot, false))
			{
				std::cout << "��.json�ļ����ݽṹ����" << std::endl;
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
		//��JSON����ת��Ϊ�ַ���
		Json::FastWriter writer;
		std::string json_file = writer.write(JSONRoot);
		//д�뵽�ļ���
		std::ofstream ofs;
		ofs.open(JSONPath.c_str());
		ofs << json_file;
		ofs.close();
	}



	//����һ������ģ������ȡJSON�������һά��Ŷ
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



	//����һ������ģ������ȡJSON�������һά��Ŷ
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

	//����һ����ά����ṹ������
	struct TwoDArray{
		std::string one;
		std::string two;
		//�����ڲ������==���������ڲ������ʱ��������Ϊһ���������Ŷ
		//����==����Ҫ������������������������ص����ڲ�����������Խ�������һ����������
		bool operator==(TwoDArray value2)
		{
			return (value2.one == one && value2.two == two);
		};

		//��������������<<����Ҫ������Ϊ��Ԫ����
		friend std::ostream& operator<<(std::ostream& out,TwoDArray& value) {
			out << "one=" << value.one << "\n" << "two=" << value.two;
			 return out;
		}

	};

	bool ReadMultipleArraryInJSON(Json::Value MultipleArraryValue, std::vector<TwoDArray> &TemplateTypeVector)
	{
		bool IsOK = true;
		//�жϵ�ǰ�����Ƿ���һ�����������������
		if (MultipleArraryValue.isArray() && MultipleArraryValue[0].isArray())
		{
			//cout << MultipleArraryValue.size() << endl;
			for (size_t n = 0; n < MultipleArraryValue.size(); n++)
			{
				TwoDArray TempBase;
				//������ǰ�����µ������飬��ʼ����ʱ����TempBase
				Json::Value SubArraryValue = MultipleArraryValue[n];
				if (SubArraryValue.size() == 2)
				{
					TempBase.one = SubArraryValue[0].asString();
					TempBase.two = SubArraryValue[1].asString();
					//����ʼ�����TempBase��ӵ�NodePropLIB������
					TemplateTypeVector.push_back(TempBase);
				}
				else{
					IsOK = false;
				}
			}
		}
		else
		{
			//cout << "�����ݲ�������" << endl;
			IsOK = false;
		}
		return IsOK;
	}


	std::vector<TwoDArray>  ReadMultipleArraryInJSON(Json::Value MultipleArraryValue)
	{
		std::vector<TwoDArray> TemplateTypeVector;
		//�жϵ�ǰ�����Ƿ���һ�����������������
		if (MultipleArraryValue.isArray() && MultipleArraryValue[0].isArray())
		{
			//cout << MultipleArraryValue.size() << endl;
			for (size_t n = 0; n < MultipleArraryValue.size(); n++)
			{
				TwoDArray TempBase;
				//������ǰ�����µ������飬��ʼ����ʱ����TempBase
				Json::Value SubArraryValue = MultipleArraryValue[n];
				if (SubArraryValue.size() == 2)
				{
					TempBase.one = SubArraryValue[0].asString();
					TempBase.two = SubArraryValue[1].asString();
					//����ʼ�����TempBase��ӵ�NodePropLIB������
					TemplateTypeVector.push_back(TempBase);
				}
			}
		}
		return TemplateTypeVector;
	}


}
#endif // JSON_JSON_H_INCLUDED
