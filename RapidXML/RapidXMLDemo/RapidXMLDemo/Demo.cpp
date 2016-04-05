//代码来源于：http://blog.csdn.net/wqvbjhc/article/details/7662931

#include <iostream>  
#include <vector>
#include <string>
#include "../../rapidxml.hpp"  
#include "../../rapidxml_utils.hpp"  
#include "../../rapidxml_print.hpp"  

using namespace rapidxml;
using namespace std;

void OptionRapidXML_Write1() {
	xml_document<> doc;//创建根节点，其代指为XML文档
	xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));//添加XML版本声明和编码声明
	doc.append_node(rot);//将XML声明链接到根节点中
	xml_node<>* node = doc.allocate_node(node_element, "config", NULL);//生成一个节点指针，存放根节点下的第一个子节点
	doc.append_node(node);//将node添加到doc下

	///新建一个节点指针，专门用来存放颜色的
	xml_node<>* color = doc.allocate_node(node_element, "color", NULL);//生成一个节点指针，专门用来存放颜色节点的
	color->append_node(doc.allocate_node(node_element, "red", "0.1"));
	color->append_node(doc.allocate_node(node_element, "green", "0.1"));
	color->append_node(doc.allocate_node(node_element, "blue", "0.1"));
	color->append_node(doc.allocate_node(node_element, "alpha", "1.0"));
	node->append_node(color);//将color添加到node下


	//新建一个节点指针，专门用来存放大小的
	xml_node<>* size = doc.allocate_node(node_element, "size", NULL);
	size->append_node(doc.allocate_node(node_element, "x", "640"));
	size->append_node(doc.allocate_node(node_element, "y", "480"));
	node->append_node(size);


	//下面操作字符串变量
	const char* Str1 = "screen mode";
	const char* Str2 = "false";

	xml_node<>* mode = doc.allocate_node(rapidxml::node_element, "mode", doc.allocate_string(Str1));
	mode->append_attribute(doc.allocate_attribute("fullscreen", Str2));//推荐使用doc.allocate_string(Str2)，而不是直接用Str2
	node->append_node(mode);


	std::string TempArr[] = { "拉交电费链接","龙达飞接待来访","alfjdLfjaf阿飞" };
	std::vector<std::string> MyStrArr(TempArr, TempArr + sizeof(TempArr)/sizeof(std::string));
	//新建一个父节点，存放SongInfo里的数据
	xml_node<>* SongInfoNode = doc.allocate_node(rapidxml::node_element, "SongInfo", NULL);
	//循环放置
	for (size_t i = 0; i < MyStrArr.size(); i++)
	{
		std::cout << MyStrArr[i] << std::endl;
		SongInfoNode->append_node(doc.allocate_node(rapidxml::node_element, "Info", doc.allocate_string(MyStrArr[i].c_str())));//推荐写法
		//SongInfoNode->append_node(doc.allocate_node(rapidxml::node_element, "Info", MyStrArr[i].c_str()));//不推荐写法，详情请见：http://www.cnblogs.com/kex1n/archive/2013/08/27/3285900.html
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

	xml_document<> doc; //是解析器  
	char a[] = "<top>"//如果单独传, 就不能加上xml的头部信息，  
		//否则会报错  
		"<name>tangqiang</name>"
		"<age>22</age>"
		"</top>";
	char* p = a;
	doc.parse<0>(p);

	xml_node<>* node = doc.first_node();//去顶级结点  
	cout << (node->name()) << endl;
	node = node->first_node();
	while (node) {
		cout << node->name() << node->value() << endl;//name() value()返回的字符串不会去掉首尾的空白字符  
		node = node->next_sibling();
	}

	ofstream out("test.xml");//ofstream 默认时，如果文件存在则会覆盖原来的内容，不存在则会新建  
	out << doc;//doc 这样输出时在目标文件中不会有xml 头信息---<?xml version='1.0' encoding='utf-8' >  
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

	//! 获取根节点  
	xml_node<>* root = doc.first_node();
	std::cout << root->name() << std::endl;

	//! 获取根节点第一个节点  
	xml_node<>* node1 = root->first_node();
	std::cout << node1->name() << std::endl;

	xml_node<>* node11 = node1->first_node();
	std::cout << node11->name() << std::endl;
	std::cout << node11->value() << std::endl;

	//! 添加之后再次保存  
	//需要说明的是rapidxml明显有一个bug  
	//那就是append_node(doc.allocate_node(node_element,"h","0"));的时候并不考虑该对象是否存在!  
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

	root->remove_node(sec); //移除根节点下的sec结点(包括该结点下所有结点)  
	text = "删除一个节点\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	root->remove_all_nodes(); //移除根节点下所有结点  
	text = "删除所有节点\r\n";
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

	//! 获取根节点  
	xml_node<>* root = doc.first_node();
	xml_node<>* delnode = root->first_node("color");
	root->remove_node(delnode);//先删除address节点  
	//  
	xml_node<>* lnode = root->first_node("size");//找到post节点  
	xml_node<>* mynode = doc.allocate_node(node_element, "address", "河北");
	root->insert_node(lnode, mynode);

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);


	std::cout << text << std::endl;

	std::ofstream out("version.xml");
	out << doc;
	system("pause");
}


/*
//遍历所有节点
for(rapidxml::xml_node<char> * node = parent_node->first_node("node name");
node != NULL;
node = node->next_sibling())
{
...
}
*/


/*
//遍历所有属性
for(rapidxml::xml_attribute<char> * attr = node->first_attribute("node name");
attr != NULL;
attr = attr->next_attribute())
{
char * value = attr->value();
}
*/


/*
//判断解析能否成功
try {
doc.parse<0>((char*)tmpbuf);//会改变参数的内容,tmpbuf的生命周期必须到解析完
} catch (rapidxml::parse_error &e) {
err="parse xml error. ";
err+=e.what();
delete []tmpbuf;
return s_stl_ruleinfo;
}
*/


void main()
{
	OptionRapidXML_Write2();
}