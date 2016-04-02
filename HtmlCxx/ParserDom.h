#ifndef __HTML_PARSER_DOM_H__
#define __HTML_PARSER_DOM_H__

#include "ParserSax.h"
#include "tree.h"
#include <vector>
#include <algorithm>//大小写转换函数的头文件

namespace htmlcxx
{
	namespace HTML
	{
		class ParserDom : public ParserSax
		{
			public:
				ParserDom() {}
				~ParserDom() {}

				const tree<Node> &parseTree(const std::string &html);
				const tree<Node> &getTree()
				{ return mHtmlTree; }

			protected:
				virtual void beginParsing();

				virtual void foundTag(Node node, bool isEnd);
				virtual void foundText(Node node);
				virtual void foundComment(Node node);

				virtual void endParsing();
				tree<Node> mHtmlTree;
				tree<Node>::iterator mCurrentState;
		};
		std::ostream &operator<<(std::ostream &stream, const tree<HTML::Node> &tr);
		//此函数是日本友人编写的，专门用来将两个tree<HTML::Node>::iterator包含的HTML转换成字符串，可以用它来将HTML的DOM树转换为字符串，从而实现保存更改的功能
		bool unparseDom(tree<Node>::iterator itrbegin, tree<Node>::iterator itrend, std::string &strbuff, bool bUnparseEnd = false);
		std::string unparseDom(tree<Node> dom, bool bUnparseEnd = false);
		std::string unparseDom(tree<HTML::Node>::iterator_base ItNode, bool bUnparseEnd = false);
	} //namespace HTML

	//自己拓展的，排除了不标准的DOM树信息来获取相关的数据
	namespace MyExtension{
		//设定属性的过滤条件
		struct NodePropBase
		{
			std::string PropName;//属性名，it->attributes().begin()->first得到的属性名全为小写字母
			std::string PropValue;//属性数值，it->attributes().begin()->second得到的属性数值能够保留原来的大小写形式
			//重载内部运算符==
			bool operator==(NodePropBase value2)
			{
				return (value2.PropName == PropName && value2.PropValue == PropValue);
			}

			//重载输出流运算符<<，需要声明其为友元函数
			friend std::ostream& operator<<(std::ostream& out, NodePropBase& value) {
				out << "PropName=" << value.PropName << "\n" << "PropValue=" << value.PropValue;
				return out;
			}
		};

		//脏字库匹配模式
		typedef enum{
			FullMatching,
			PartMatching
		}MatchedMode;


		//判断当前节点是否为有效标签节点
		bool IsAvailableTagNode(tree<HTML::Node> Node);
		//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点
		bool IsAvailableTextNode(tree<HTML::Node>::iterator it);
		//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
		bool IsAvailableTextNodeEx(tree<HTML::Node>::iterator it);
		//获取当前节点所有的有效子节点
		bool GetAllSubNode(tree_node_<HTML::Node> *CurrentNode, std::vector<tree<HTML::Node>> &SiblingNodeArr);
		//获取当前节点所有的有效子节点
		std::vector<tree<HTML::Node>> GetAllSubNode(tree_node_<HTML::Node> *CurrentNode);
		//获得DOM树的标签层次
		std::string GetFullDOM(tree<HTML::Node> dom);
		//打印DOM树的标签层次
		void PrintFullDOM(tree<HTML::Node> dom);
		//输出DOM树里同级的标签节点信息
		void PrintSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank);
		//获取DOM树里同级的标签节点信息
		void GetSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank, std::string &DOMStr);
		//获取当前节点的文本标签里的文本，不遍历子标签节点哦，也就是文本节点不为空，不是单纯的网址链接也不是换行符，也不是JS脚本
		std::string GetTextContentCurrentNode(tree<HTML::Node> dom);
		//遍历当前节点所有子节点来获取所有有效的文本节点，也就是文本节点不为空，不是单纯的网址链接也不是换行符，也不是JS脚本
		std::string GetTextContentInDOM(tree<HTML::Node> dom);
		//遍历当前节点所有子节点来获取所有有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
		std::string GetTextContentInDOMEx(tree<HTML::Node> dom);
		//显示所有有效的文本节点，也就是文本节点不为空，不是单纯的网址链接也不是换行符，也不是JS脚本
		void PrintTextContentInDOM(tree<HTML::Node> dom);
		//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
		void PrintTextContentInDOMEx(tree<HTML::Node> dom);


		
		//遍历DOM树里所有标签属性
		void BrowAllPropInDOM(tree<HTML::Node> dom);
		//显示标签节点的所有属性信息
		void ShowPropInfoInNode(tree<HTML::Node>::iterator it);
		//根据属性的索引号来查找相应的属性值
		bool GetPropValueByPropIndex(tree<HTML::Node>::iterator it, int PropIndex, NodePropBase &PropInfo);
		//根据属性的名称来查找相应的属性值
		bool GetPropValueByPropName(tree<HTML::Node>::iterator it, std::string PropName, NodePropBase &PropInfo);
		//通过标签里的属性信息来确定相应节点，返回符合条件的所有节点
		std::vector<tree<HTML::Node>> GetSubNodeByTagProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB);
		//通过标签里的属性来确定相应节点，并将所有符合条件的节点显示出来
		void PrintSubNodeByTagProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB);
		//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
		//通过标签里的属性信息来判断此节点是否包含在此过滤条件之内，返回判断结果，
		//一般结合it.node->parent来使用，比如修改某个属性下的文本时，就需要使用此函数来筛选了
		bool IsNeedTagNodeByNodeProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB, MatchedMode MatchFlag);
		//获取当前节点下指定标签名的所有子节点
		bool GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::vector<tree<HTML::Node>> &SubNodeArr, std::string TagName);
		//获取当前节点下指定标签名的所有子节点
		std::vector<tree<HTML::Node>> GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::string TagName);
		//vector<MyExtension::NodePropBase> TagPropLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
		//通过标签里标签名和属性信息来确定相应节点，返回符合条件的所有节点
		std::vector<tree<HTML::Node>> GetSubNodeByTagInfo(tree<HTML::Node> dom, std::string TagName, std::vector<NodePropBase> TagPropLIB);
	}

} //namespace htmlcxx

#endif
