#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "TinyXML2\tinyxml2.h"
using namespace std;

void BroweAllElement(tinyxml2::XMLElement* ParentElement);
void PrintElementInfo(tinyxml2::XMLElement* CurrentElement);

//针对UTF-8和ANSI文件编码的说明
//注意，在默认情况下TinyXML(2)的字符编码处理方式依据xml文件编码而定，TinyXML和TinyXML2的API大体相同
void main()
{
	tinyxml2::XMLDocument doc;
	//doc.LoadFile("skin(UTF-8).xml");
	doc.LoadFile("skin(ANSI).xml");
	//doc.Print();//打印整个XML DOM
	//printf("节点名为：%s，第一个属性值为：%s\n", doc.FirstChildElement()->Name(), doc.FirstChildElement()->FirstAttribute()->Value());
	//查找信息
	tinyxml2::XMLElement* RootElement = doc.FirstChildElement("Window");
	//添加元素
	tinyxml2::XMLElement* AddEle = doc.NewElement("addelement");
	AddEle->SetAttribute("alfsjd", "了解阿飞");
	AddEle->SetAttribute("kjj", "777777777777");
	AddEle->SetText("离开家阿费莱解放党");
	//RootElement->LinkEndChild(AddEle);
	RootElement->InsertEndChild(AddEle);//会根据XMLDocument不同而改变，在同一个XMLDocument下，效果和LinkEndChild()一样
	//RootElement->InsertFirstChild(AddEle);
	doc.Print();
	system("pause");
	//删除操作
	cout << "即将执行删除操作" << endl;
	tinyxml2::XMLElement* NewEle = RootElement->FirstChildElement("addelement");//Attribute("kjj") << endl;
	PrintElementInfo(NewEle);
	//doc.Print();
	system("pause");
	//删除属性
	cout << "即将执行删除属性" << endl;
	NewEle->DeleteAttribute("kjj");
	PrintElementInfo(NewEle);
	system("pause");
	cout << "即将执行删除元素" << endl;
	doc.Print();
	system("pause");
	//删除某个子元素
	RootElement->DeleteChild(RootElement->FirstChildElement("addelement"));
	doc.Print();
	system("pause");
	//删除所有子元素
	RootElement->DeleteChildren();
	doc.Print();
	system("pause");
	//遍历所有元素
	//BroweAllElement(RootElement);
	//保存到文件上
	//doc.SaveFile("OtherSave.xml");
	system("pause");
}

void BroweAllElement(tinyxml2::XMLElement* ParentElement)
{
	if (ParentElement != NULL)
	{
		PrintElementInfo(ParentElement);
		if (string(ParentElement->Name()) == string("Button"))
		{
			ParentElement->SetName("lajfdldfj");
		}
		if (!ParentElement->NoChildren())
		{
			//遍历所有同级子元素
			tinyxml2::XMLElement* ElementPos = NULL;
			for (ElementPos = ParentElement->FirstChildElement(); ElementPos != NULL; ElementPos = ElementPos->NextSiblingElement())
				BroweAllElement(ElementPos);
		}
		else
			cout << "底层元素名：" << ParentElement->Name() << endl;
	}
	else
		cout << "此元素不存在" << endl;
}


//输出元素的属性信息
void PrintElementInfo(tinyxml2::XMLElement* CurrentElement)
{
	if (CurrentElement->FirstAttribute() != NULL)
	{
		printf("节点名为：%s\n", CurrentElement->FirstAttribute()->Name());
		//判断某属性是否存在
		const char* PropName1 = "roundcorner";
		printf("%s属性是否存在？ %d\n", PropName1, CurrentElement->BoolAttribute(PropName1));
		//查询某节点的非字符串类型属性值，官方提供了Int、float、double、bool、unsigned int等数据支持
		const char* PropName2 = "IntValue";
		int PropValue2 = 10;
		CurrentElement->QueryAttribute(PropName2, &PropValue2);//此函数重载了4次，分别对应上述数据类型
		if (CurrentElement->BoolAttribute(PropName2))
			printf("%s属性的数值： %d\n", PropName2, PropValue2);
		//查询某节点的字符串类型属性值
		const char* PropName3 = "sizebox";
		const char* PropValue3 = CurrentElement->Attribute(PropName3);
		if (CurrentElement->BoolAttribute(PropName3))
		{
			printf("%s属性的数值： %s\n", PropName3, PropValue3);
			//设置属性
			CurrentElement->SetAttribute("Custom","你好吗？");//添加属性
			CurrentElement->SetAttribute("sizebox","10000");//修改属性
			system("pause");
		}
		//遍历所有属性
		const tinyxml2::XMLAttribute* AttributePos = NULL;
		for (AttributePos = CurrentElement->FirstAttribute(); AttributePos != NULL; AttributePos = AttributePos->Next())
			printf("属性名：%s  属性数值：%s\n", AttributePos->Name(), AttributePos->Value());
	}
}