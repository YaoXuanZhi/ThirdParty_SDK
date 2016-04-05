#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "TinyXML2\tinyxml2.h"
using namespace std;

void BroweAllElement(tinyxml2::XMLElement* ParentElement);
void PrintElementInfo(tinyxml2::XMLElement* CurrentElement);

//���UTF-8��ANSI�ļ������˵��
//ע�⣬��Ĭ�������TinyXML(2)���ַ����봦��ʽ����xml�ļ����������TinyXML��TinyXML2��API������ͬ
void main()
{
	tinyxml2::XMLDocument doc;
	//doc.LoadFile("skin(UTF-8).xml");
	doc.LoadFile("skin(ANSI).xml");
	//doc.Print();//��ӡ����XML DOM
	//printf("�ڵ���Ϊ��%s����һ������ֵΪ��%s\n", doc.FirstChildElement()->Name(), doc.FirstChildElement()->FirstAttribute()->Value());
	//������Ϣ
	tinyxml2::XMLElement* RootElement = doc.FirstChildElement("Window");
	//���Ԫ��
	tinyxml2::XMLElement* AddEle = doc.NewElement("addelement");
	AddEle->SetAttribute("alfsjd", "�˽Ⱒ��");
	AddEle->SetAttribute("kjj", "777777777777");
	AddEle->SetText("�뿪�Ұ�������ŵ�");
	//RootElement->LinkEndChild(AddEle);
	RootElement->InsertEndChild(AddEle);//�����XMLDocument��ͬ���ı䣬��ͬһ��XMLDocument�£�Ч����LinkEndChild()һ��
	//RootElement->InsertFirstChild(AddEle);
	doc.Print();
	system("pause");
	//ɾ������
	cout << "����ִ��ɾ������" << endl;
	tinyxml2::XMLElement* NewEle = RootElement->FirstChildElement("addelement");//Attribute("kjj") << endl;
	PrintElementInfo(NewEle);
	//doc.Print();
	system("pause");
	//ɾ������
	cout << "����ִ��ɾ������" << endl;
	NewEle->DeleteAttribute("kjj");
	PrintElementInfo(NewEle);
	system("pause");
	cout << "����ִ��ɾ��Ԫ��" << endl;
	doc.Print();
	system("pause");
	//ɾ��ĳ����Ԫ��
	RootElement->DeleteChild(RootElement->FirstChildElement("addelement"));
	doc.Print();
	system("pause");
	//ɾ��������Ԫ��
	RootElement->DeleteChildren();
	doc.Print();
	system("pause");
	//��������Ԫ��
	//BroweAllElement(RootElement);
	//���浽�ļ���
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
			//��������ͬ����Ԫ��
			tinyxml2::XMLElement* ElementPos = NULL;
			for (ElementPos = ParentElement->FirstChildElement(); ElementPos != NULL; ElementPos = ElementPos->NextSiblingElement())
				BroweAllElement(ElementPos);
		}
		else
			cout << "�ײ�Ԫ������" << ParentElement->Name() << endl;
	}
	else
		cout << "��Ԫ�ز�����" << endl;
}


//���Ԫ�ص�������Ϣ
void PrintElementInfo(tinyxml2::XMLElement* CurrentElement)
{
	if (CurrentElement->FirstAttribute() != NULL)
	{
		printf("�ڵ���Ϊ��%s\n", CurrentElement->FirstAttribute()->Name());
		//�ж�ĳ�����Ƿ����
		const char* PropName1 = "roundcorner";
		printf("%s�����Ƿ���ڣ� %d\n", PropName1, CurrentElement->BoolAttribute(PropName1));
		//��ѯĳ�ڵ�ķ��ַ�����������ֵ���ٷ��ṩ��Int��float��double��bool��unsigned int������֧��
		const char* PropName2 = "IntValue";
		int PropValue2 = 10;
		CurrentElement->QueryAttribute(PropName2, &PropValue2);//�˺���������4�Σ��ֱ��Ӧ������������
		if (CurrentElement->BoolAttribute(PropName2))
			printf("%s���Ե���ֵ�� %d\n", PropName2, PropValue2);
		//��ѯĳ�ڵ���ַ�����������ֵ
		const char* PropName3 = "sizebox";
		const char* PropValue3 = CurrentElement->Attribute(PropName3);
		if (CurrentElement->BoolAttribute(PropName3))
		{
			printf("%s���Ե���ֵ�� %s\n", PropName3, PropValue3);
			//��������
			CurrentElement->SetAttribute("Custom","�����");//�������
			CurrentElement->SetAttribute("sizebox","10000");//�޸�����
			system("pause");
		}
		//������������
		const tinyxml2::XMLAttribute* AttributePos = NULL;
		for (AttributePos = CurrentElement->FirstAttribute(); AttributePos != NULL; AttributePos = AttributePos->Next())
			printf("��������%s  ������ֵ��%s\n", AttributePos->Name(), AttributePos->Value());
	}
}