//������Ҫ��Դ�ڣ�http://blog.csdn.net/wqvbjhc/article/details/7662931
//���Ȿ�˲�����һЩ

#include <iostream>  
#include <vector>
#include <string>
#include "../../rapidxml.hpp"  
#include "../../rapidxml_utils.hpp"  
#include "../../rapidxml_print.hpp"  

using namespace rapidxml;
using namespace std;

//ע�⣬RapidXML��������ָ��������մ�����˲���Ҫ���������ֶ�����Ŷ��

void OptionRapidXML_Write1() {
	xml_document<> doc;//�������ڵ㣬���ָΪXML�ĵ�
	xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));//���XML�汾�����ͱ�������
	doc.append_node(rot);//��XML�������ӵ����ڵ���
	xml_node<>* node = doc.allocate_node(node_element, "config", NULL);//����һ���ڵ�ָ�룬��Ÿ��ڵ��µĵ�һ���ӽڵ�
	doc.append_node(node);//��node��ӵ�doc��

	///�½�һ���ڵ�ָ�룬ר�����������ɫ��
	xml_node<>* color = doc.allocate_node(node_element, "color", NULL);//����һ���ڵ�ָ�룬ר�����������ɫ�ڵ��
	color->append_node(doc.allocate_node(node_element, "red", "0.1"));
	color->append_node(doc.allocate_node(node_element, "green", "0.1"));
	color->append_node(doc.allocate_node(node_element, "blue", "0.1"));
	color->append_node(doc.allocate_node(node_element, "alpha", "1.0"));
	node->append_node(color);//��color��ӵ�node��


	//�½�һ���ڵ�ָ�룬ר��������Ŵ�С��
	xml_node<>* size = doc.allocate_node(node_element, "size", NULL);
	size->append_node(doc.allocate_node(node_element, "x", "640"));
	size->append_node(doc.allocate_node(node_element, "y", "480"));
	node->append_node(size);


	//��������ַ�������
	const char* Str1 = "screen mode";
	const char* Str2 = "false";

	xml_node<>* mode = doc.allocate_node(rapidxml::node_element, "mode", doc.allocate_string(Str1));
	mode->append_attribute(doc.allocate_attribute("fullscreen", Str2));//�Ƽ�ʹ��doc.allocate_string(Str2)��������ֱ����Str2
	node->append_node(mode);


	std::string TempArr[] = { "�����������","����ɽӴ�����","alfjdLfjaf����" };
	std::vector<std::string> MyStrArr(TempArr, TempArr + sizeof(TempArr)/sizeof(std::string));
	//�½�һ�����ڵ㣬���SongInfo�������
	xml_node<>* SongInfoNode = doc.allocate_node(rapidxml::node_element, "SongInfo", NULL);
	//ѭ������
	for (size_t i = 0; i < MyStrArr.size(); i++)
	{
		std::cout << MyStrArr[i] << std::endl;
		SongInfoNode->append_node(doc.allocate_node(rapidxml::node_element, "Info", doc.allocate_string(MyStrArr[i].c_str())));//�Ƽ�д��
		//SongInfoNode->append_node(doc.allocate_node(rapidxml::node_element, "Info", MyStrArr[i].c_str()));//���Ƽ�д��
	}

	node->append_node(SongInfoNode);

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;

	std::ofstream out("config.xml");
	out << doc;
	out.close();
	system("PAUSE");
}


void OptionRapidXML_Write2()
{

	xml_document<> doc; //�ǽ�����  
	char a[] = "<top>"//���������, �Ͳ��ܼ���xml��ͷ����Ϣ��  
		//����ᱨ��  
		"<name>tangqiang</name>"
		"<age>22</age>"
		"</top>";
	char* p = a;
	doc.parse<0>(p);

	xml_node<>* node = doc.first_node();//ȥ�������  
	cout << (node->name()) << endl;
	node = node->first_node();
	while (node) {
		cout << node->name() << node->value() << endl;//name() value()���ص��ַ�������ȥ����β�Ŀհ��ַ�  
		node = node->next_sibling();
	}

	ofstream out("test.xml");//ofstream Ĭ��ʱ������ļ�������Ḳ��ԭ�������ݣ�����������½�  
	out << doc;//doc �������ʱ��Ŀ���ļ��в�����xml ͷ��Ϣ---<?xml version='1.0' encoding='utf-8' >  
	out.close();
	system("pause");
}

void OptionRapidXML_Read()
{
	file<> fdoc("config.xml");
	std::cout << fdoc.data() << std::endl;
	xml_document<>   doc;
	doc.parse<0>(fdoc.data());

	std::cout << doc.name() << std::endl;

	//! ��ȡ���ڵ�  
	xml_node<>* root = doc.first_node();
	std::cout << root->name() << std::endl;

	//! ��ȡ���ڵ��һ���ڵ�  
	xml_node<>* node1 = root->first_node();
	std::cout << node1->name() << std::endl;

	xml_node<>* node11 = node1->first_node();
	std::cout << node11->name() << std::endl;
	std::cout << node11->value() << std::endl;

	//! ���֮���ٴα���  
	//��Ҫ˵������rapidxml������һ��bug  
	//�Ǿ���append_node(doc.allocate_node(node_element,"h","0"));��ʱ�򲢲����Ǹö����Ƿ����!  
	xml_node<>* size = root->first_node("size");
	size->append_node(doc.allocate_node(node_element, "w", "0"));
	size->append_node(doc.allocate_node(node_element, "h", "0"));

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;

	std::ofstream out("config.xml");
	out << doc;

	system("PAUSE");
}


void OptionRapidXML_Delete()
{
	file<> fdoc("config.xml");
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	xml_node<>* root = doc.first_node();

	xml_node<>* sec = root->first_node();

	root->remove_node(sec); //�Ƴ����ڵ��µ�sec���(�����ý�������н��)  
	text = "ɾ��һ���ڵ�\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	root->remove_all_nodes(); //�Ƴ����ڵ������н��  
	text = "ɾ�����нڵ�\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	std::ofstream out("test.xml");
	out << doc;
	system("pause");
}


void OptionRapidXML_Modify()
{
	file<> fdoc("config.xml");
	std::cout << fdoc.data() << std::endl;
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	std::cout << doc.name() << std::endl;

	//! ��ȡ���ڵ�  
	xml_node<>* root = doc.first_node();
	xml_node<>* delnode = root->first_node("color");
	root->remove_node(delnode);//��ɾ��address�ڵ�  
	//  
	xml_node<>* lnode = root->first_node("size");//�ҵ�post�ڵ�  
	xml_node<>* mynode = doc.allocate_node(node_element, "address", "�ӱ�");
	root->insert_node(lnode, mynode);

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);


	std::cout << text << std::endl;

	std::ofstream out("version.xml");
	out << doc;
	system("pause");
}


void BrowerAttitude(xml_node<>* CurrentElement)
{
	if (CurrentElement->first_attribute() != NULL)
	{
		for (rapidxml::xml_attribute<char> * attr = CurrentElement->first_attribute(); attr != NULL; attr = attr->next_attribute())
			printf("%s==%s\n", attr->name(), attr->value());
	}
}



//��������Ԫ��
void BrowerElement(xml_node<>* RootElement)
{
	if (RootElement != NULL)
	{
		BrowerAttitude(RootElement);
		if (RootElement->first_node())
		{
			for (xml_node<>* ElementPos = RootElement->first_node(); ElementPos != NULL; ElementPos = ElementPos->next_sibling())
				BrowerElement(ElementPos);
		}else
			cout << RootElement->name() << "��������Ԫ��" << endl;
	}
}


void main()
{
	file<> fdoc("skin(ANSI).xml");
	//std::cout << fdoc.data() << std::endl;
	xml_document<>   doc;
	doc.parse<0>(fdoc.data());
	//cout << doc << endl;

	//��������Ԫ��
	xml_node<>* RootElement = doc.first_node();
	BrowerElement(RootElement);
	//delete RootElement;//����Ҫ�ֶ�����ָ��������ڴ�
	system("pause");
}