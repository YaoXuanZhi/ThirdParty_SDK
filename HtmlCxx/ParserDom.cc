#include "ParserDom.h"
#include "wincstring.h"
#include "Extensions.h"
#include <iostream>

//#define DEBUG
#include "debug.h"

#define TAG_NAME_MAX 10

using namespace htmlcxx; 
using namespace HTML; 
using namespace kp; 

const tree<HTML::Node>& ParserDom::parseTree(const std::string &html)
{
	this->parse(html);
	return this->getTree();
}
void ParserDom::beginParsing()
{
	mHtmlTree.clear();
	tree<HTML::Node>::iterator top = mHtmlTree.begin();
	HTML::Node lambda_node;
	lambda_node.offset(0);
	lambda_node.length(0);
	lambda_node.isTag(true);
	lambda_node.isComment(false);
	mCurrentState = mHtmlTree.insert(top,lambda_node);
}

void ParserDom::endParsing()
{
	tree<HTML::Node>::iterator top = mHtmlTree.begin();
	top->length(mCurrentOffset);
}

void ParserDom::foundComment(Node node)
{
	//Add child content node, but do not update current state
	mHtmlTree.append_child(mCurrentState, node);
}

void ParserDom::foundText(Node node)
{
	//Add child content node, but do not update current state
	mHtmlTree.append_child(mCurrentState, node);
}

void ParserDom::foundTag(Node node, bool isEnd)
{
	if (!isEnd) 
	{
		//append to current tree node
		tree<HTML::Node>::iterator next_state;
		next_state = mHtmlTree.append_child(mCurrentState, node);
		mCurrentState = next_state;
	} 
	else 
	{
		//Look if there is a pending open tag with that same name upwards
		//If mCurrentState tag isn't matching tag, maybe a some of its parents
		// matches
		std::vector< tree<HTML::Node>::iterator > path;
		tree<HTML::Node>::iterator i = mCurrentState;
		bool found_open = false;
		while (i != mHtmlTree.begin())
		{
#ifdef DEBUG
			cerr << "comparing " << node.tagName() << " with " << i->tagName()<<endl<<":";
			if (!i->tagName().length()) cerr << "Tag with no name at" << i->offset()<<";"<<i->offset()+i->length();
#endif
			assert(i->isTag());
			assert(i->tagName().length());

			bool equal;
			const char *open = i->tagName().c_str();
			const char *close = node.tagName().c_str();
			equal = !(strcasecmp(open,close));


			if (equal) 
			{
				DEBUGP("Found matching tag %s\n", i->tagName().c_str());
				//Closing tag closes this tag
				//Set length to full range between the opening tag and
				//closing tag
				i->length(node.offset() + node.length() - i->offset());
				i->closingText(node.text());

				mCurrentState = mHtmlTree.parent(i);
				found_open = true;
				break;
			} 
			else 
			{
				path.push_back(i);
			}

			i = mHtmlTree.parent(i);
		}

		if (found_open)
		{
			//If match was upper in the tree, so we need to invalidate child
			//nodes that were waiting for a close
			for (unsigned int j = 0; j < path.size(); ++j)
			{
//				path[j]->length(node.offset() - path[j]->offset());
				mHtmlTree.flatten(path[j]);
			}
		} 
		else 
		{
			DEBUGP("Unmatched tag %s\n", node.text().c_str());

			// Treat as comment
			node.isTag(false);
			node.isComment(true);
			mHtmlTree.append_child(mCurrentState, node);
		}
	}
}

std::ostream &HTML::operator<<(std::ostream &stream, const tree<HTML::Node> &tr)
{

	tree<HTML::Node>::pre_order_iterator it = tr.begin();
	tree<HTML::Node>::pre_order_iterator end = tr.end();

	int rootdepth = tr.depth(it);
	stream << "-----" << std::endl;

	unsigned int n = 0;
	while ( it != end ) 
	{

		int cur_depth = tr.depth(it);
		for(int i=0; i < cur_depth - rootdepth; ++i) stream << "  ";
		stream << n << "@";
		stream << "[" << it->offset() << ";";
		stream << it->offset() + it->length() << ") ";
		stream << (std::string)(*it) << std::endl;
		++it, ++n;
	}
	stream << "-----" << std::endl;
	return stream;
}


//此函数是日本友人编写的，专门用来将两个tree<HTML::Node>::iterator包含的HTML转换成字符串，可以用它来将HTML的DOM树转换为字符串，从而实现保存更改的功能
bool HTML::unparseDom(tree<Node>::iterator itrbegin,
	tree<Node>::iterator itrend,
	std::string &strbuff,
	bool bUnparseEnd){
	if (bUnparseEnd) itrend.skip_children(), itrend++;

	tree<Node>::iterator itr = itrbegin;
	for (; itr != itrend; itr++){
		if (itr->isTag()){
			strbuff += itr->text();
			std::string strendtag(itr->closingText());
			if (itr.number_of_children() > 0)
				HTML::unparseDom(itr.node->first_child
				, itr.node->last_child, strbuff, true);
			strbuff += strendtag;

			// forのインクリメントで子ノードを飛ばす
			itr.skip_children();
		}
		else{
			strbuff += itr->text();
		}
	}
	return true;
}


std::string HTML::unparseDom(tree<Node> dom, bool bUnparseEnd)
{
	std::string strbuff;
	tree<Node>::iterator itrbegin = dom.begin();
	tree<Node>::iterator itrend = dom.end();
	bool IsSuccess=HTML::unparseDom(itrbegin,itrend,strbuff);
	if (!IsSuccess)
	{
		strbuff = "";
	}
	return strbuff;
}

//ItNode=it->node;或者是ItNode=(tree<HTML::Node>::iterator_base)it;
std::string HTML::unparseDom(tree<HTML::Node>::iterator_base ItNode, bool bUnparseEnd)
{
	return HTML::unparseDom((tree<HTML::Node>)ItNode);
}






//遍历DOM树里所有标签属性
void MyExtension::BrowAllPropInDOM(tree<HTML::Node> dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//仅仅输出标签节点
		if (MyExtension::IsAvailableTagNode(it))
		{
			//遍历节点的所有属性
			it->parseAttributes();
			std::map<std::string, std::string> NodeProperties = it->attributes();
			std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
			std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
			int i = 0;
			//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
			//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
			if (Propit->first.length() > 0 && Propit->first.length()<100)
			{
				std::cout << "当前标签为为：" << it->tagName() << std::endl;
				std::cout << "下面罗列此标签的所有属性：" << std::endl;
				for (; Propit != Propend; Propit++)
				{
					std::string PropName = Propit->first;
					std::string PropValue = Propit->second;
					//cout << "第" << i << "个属性的名称为：" << PropName << endl;
					//cout << "第" << i << "个属性的数值为：" << PropValue << endl;
					std::cout << "第" << i + 1 << "个属性：" << std::string("\"") + PropName + std::string("\"") << "=" << std::string("\"") + PropValue + std::string("\"") << std::endl;
					i++;
				}
			}
			else
			{
				std::cout << "此标签并没有任何属性" << std::endl;
			}
		}
	}
}






//获取当前节点所有有效子节点
bool MyExtension::GetAllSubNode(tree_node_<HTML::Node> *CurrentNode, std::vector<tree<HTML::Node>> &SiblingNodeArr)
{
	bool IsOK = true;
	//找到此父节点的第一个子节点
	tree_node_<HTML::Node> *BeginNode = CurrentNode->first_child;
	//遍历所有同级节点，直到找不到同级节点为止，不需要CurrentNode->last_child作为结束标记
	for (tree_node_<HTML::Node>* LoopNode = BeginNode; LoopNode; LoopNode = LoopNode->next_sibling)
	{
		tree<HTML::Node> TempNode = (tree<HTML::Node>)LoopNode;
		if (MyExtension::IsAvailableTagNode(TempNode))
		{
			//std::cout << HTML::unparseDom(TempNode) << std::endl;
			SiblingNodeArr.push_back(TempNode);
		}
	}
	return IsOK;
}


std::vector<tree<HTML::Node>> MyExtension::GetAllSubNode(tree_node_<HTML::Node> *CurrentNode)
{
	std::vector<tree<HTML::Node>> SiblingNodeArr;
	if (MyExtension::GetAllSubNode(CurrentNode, SiblingNodeArr))
	{
		return SiblingNodeArr;
	}
	return SiblingNodeArr;
}




//获取当前节点下指定标签名的所有子节点
bool MyExtension::GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::vector<tree<HTML::Node>> &SubNodeArr, std::string TagName)
{
	bool IsOK = false;
	//找到此父节点的第一个子节点
	tree<HTML::Node>::iterator it = CurrentNode.begin();
	tree<HTML::Node>::iterator end = CurrentNode.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTagNode(it))
		{
			if (TagName == it->tagName())
			{
				tree<HTML::Node> TempNode = (tree<HTML::Node>)it.node;
				//std::cout << it->tagName() << std::endl;
				SubNodeArr.push_back(TempNode);
			}

		}
	}
	if (SubNodeArr.size() > 0)
	{
		IsOK = true;
	}

	return IsOK;
}


//获取当前节点下指定标签名的所有子节点
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::string TagName)
{
	std::vector<tree<HTML::Node>> SubNodeArr;
	if (MyExtension::GetSubNodeByTagName(CurrentNode, SubNodeArr, TagName))
	{
		return SubNodeArr;
	}
	return SubNodeArr;
}



//判断当前节点是否为有效标签节点
bool MyExtension::IsAvailableTagNode(tree<HTML::Node> Node)
{
	bool IsAvailable = false;
	std::string tempstr = Node.begin()->tagName();
	//判断当前节点类型是否为标签，而且标签名存在且不为?
	if (Node.begin()->isTag() && tempstr != std::string("?"))
	{
		//去掉标签名里可能存在的特殊字符
		htmlcxx::Extensions::GlobalReStr(tempstr, "\n", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\r", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\t", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, " ", "");
		
		if (tempstr.length() > 0)
		{
			IsAvailable = true;
		}
	}
	return IsAvailable;
}





//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点
bool MyExtension::IsAvailableTextNode(tree<HTML::Node>::iterator it)
{
	bool IsAvailable = false;
	if (!it->isComment() && !it->isTag())
	{
		//但是由于htmlcxx里面对那些单独的换行符也是作为一个文本来读取的，
		//所以需要针对这种特殊的文本节点作过滤
		std::string tempstr = it->tagName();
		htmlcxx::Extensions::GlobalReStr(tempstr, " ", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\n", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\r", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\t", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "<br/>", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "<br>", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "&nbsp;", "");//去掉不断行的空白格
		htmlcxx::Extensions::GlobalReStr(tempstr, "&ensp;", "");//半方大的空白
		htmlcxx::Extensions::GlobalReStr(tempstr, "&emsp;", "");//全方大的空白

		if (tempstr.length() > 0)
		{
			IsAvailable = true;
		}

	}
	return IsAvailable;
}



//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
bool MyExtension::IsAvailableTextNodeEx(tree<HTML::Node>::iterator it)
{
	bool IsAvailable = false;
	if (MyExtension::IsAvailableTextNode(it))
	{
		////过滤掉JS脚本所对应的标签。
		////考虑到htmlcxx对htm的大小写敏感，所以先将标签里的英文全部转换为大写
		const char* PreTagName = it.node->parent->data.tagName().c_str(); //文本标签的父标签
		////unsigned int SubNumInPreNode = ((tree<HTML::Node>)it.node->parent).begin().number_of_children();//父标签下的子节点个数

		//从Gumbo里面提取过来哒
		std::string empty_tags = "|area|base|basefont|bgsound|br|command|col|embed|event-source|frame|hr|image|img|input|keygen|link|menuitem|meta|param|source|spacer|track|wbr|";
		std::string preserve_whitespace = "|pre|textarea|script|style|";
		//vector<string> FilterLIB = { "SCRIPT", "STYLE", "BODY", "LINK" };
		std::vector<std::string> empty_tagsLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(empty_tags.c_str()), "|", "|");
		std::vector<std::string> preserve_whitespaceLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(preserve_whitespace.c_str()), "|", "|");
		std::vector<std::string> FilterLIB;
		FilterLIB.insert(FilterLIB.begin(), empty_tagsLIB.begin(), empty_tagsLIB.end());
		FilterLIB.insert(FilterLIB.begin(), preserve_whitespaceLIB.begin(), preserve_whitespaceLIB.end());
		//跳过脏字库里的所有标签
		if (!htmlcxx::Extensions::FilterStr(htmlcxx::Extensions::SmallCharToBigChar(PreTagName), FilterLIB, 2))
		{
			//经过判断之后，可以确定此迭代器对应的文本节点是有效的
			IsAvailable = true;
		}
	}

	return IsAvailable;
}



//输出DOM树的标签层次
std::string MyExtension::GetFullDOM(tree<HTML::Node> dom)
{
	std::string FullDOMStr = "";
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	tree_node_<HTML::Node> *TempNode = NULL;
	bool IsJump = false;
	//找到此节点下第一个有效的标签节点
	for (; it != end&&!IsJump; ++it)
	{
		//cout << "当前节 点标签名为："<< it->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(it))
		{
			//cout << "当前找到的节点标签名为：" << it->tagName() << endl;
			IsJump = true;
			std::vector<tree<HTML::Node>> TempArrNode = MyExtension::GetAllSubNode(it.node);//得到子节点
			std::string TagBlank = "";
			FullDOMStr += it->text() + std::string("\n");
			MyExtension::GetSubDOM(TempArrNode, TagBlank, FullDOMStr);
			FullDOMStr += it->closingText() + std::string("\n");
		}
	}
	return FullDOMStr;
}




//输出DOM树的标签层次
void MyExtension::PrintFullDOM(tree<HTML::Node> dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	tree_node_<HTML::Node> *TempNode = NULL;
	bool IsJump = false;
	//找到此节点下第一个有效的标签节点
	for (; it != end&&!IsJump; ++it)
	{
		//cout << "当前节 点标签名为："<< it->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(it))
		{
			//cout << "当前找到的节点标签名为：" << it->tagName() << endl;
			IsJump = true;
			std::vector<tree<HTML::Node>> TempArrNode = MyExtension::GetAllSubNode(it.node);//找到此节点下的所有子节点
			std::string TagBlank = "";
			std::cout << "<" << it->tagName() << ">" << std::endl;
			//PrintSiblingDOM(TempArrNode, TagBlank);
			MyExtension::PrintSubDOM(TempArrNode, TagBlank);//打印所有子节点的标签信息
			std::cout << it->closingText() << std::endl;
		}
	}
}






//获得DOM树里子节点的标签节点信息
void MyExtension::GetSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank, std::string &DOMStr)
{
	TagBlank += std::string("  ");
	std::string TempBlank = TagBlank;
	for (size_t n = 0; n < TempArrNode.size(); n++)
	{
		//cout << "子节点名称为：" <<TempArrNode[n].begin()->tagName() << endl;
		//if (TempArrNode[n].begin()->isTag() && TempArrNode[n].begin()->tagName() != string("?") && TempArrNode[n].begin()->tagName().length()>0)
		if (MyExtension::IsAvailableTagNode(TempArrNode[n]))
		{
			DOMStr += TempBlank + TempArrNode[n].begin()->text() + std::string("\n");
			MyExtension::GetSubDOM(GetAllSubNode(TempArrNode[n].begin().node), TagBlank, DOMStr);
			if (TempArrNode[n].begin()->closingText().length()>0)//针对<xxx ID="afd" />之类的节点作特殊判断
			{
				DOMStr += TempBlank + TempArrNode[n].begin()->closingText() + std::string("\n");
			}
		}
	}
}



//输出DOM树里子节点的标签节点信息
void MyExtension::PrintSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank)
{
	TagBlank += std::string("  ");
	std::string TempBlank = TagBlank;
	for (size_t n = 0; n < TempArrNode.size(); n++)
	{
		//cout << "子节点名称为：" <<TempArrNode[n].begin()->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(TempArrNode[n]))
		{
			std::cout << TempBlank << TempArrNode[n].begin()->text() << std::endl;
			MyExtension::PrintSubDOM(MyExtension::GetAllSubNode(TempArrNode[n].begin().node), TagBlank);
			if (TempArrNode[n].begin()->closingText().length()>0)//针对<xxx ID="afd" />之类的节点作特殊判断
			{
				std::cout << TempBlank << TempArrNode[n].begin()->closingText() << std::endl;
			}
		}
	}
}



//显示标签节点的所有属性信息
void MyExtension::ShowPropInfoInNode(tree<HTML::Node>::iterator it)
{
	//if (it->isTag())//仅仅输出标签节点的属性信息
	if (MyExtension::IsAvailableTagNode(it))
	{
		//遍历节点的所有属性
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
		//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			std::cout << "当前标签为为：" << it->tagName() << std::endl;
			std::cout << "下面罗列此标签的所有属性：" << std::endl;
			for (; Propit != Propend; Propit++)
			{
				std::string PropName = Propit->first;
				std::string PropValue = Propit->second;
				std::cout << "第" << i + 1 << "个属性：" << std::string("\"") + PropName + std::string("\"") << "=" << std::string("\"") + PropValue + std::string("\"") << std::endl;
				i++;
			}
		}
		else
		{
			std::cout << "此标签并没有任何属性" << std::endl;
		}
	}
}



//根据属性的索引号来查找相应的属性值
bool MyExtension::GetPropValueByPropIndex(tree<HTML::Node>::iterator it, int PropIndex, MyExtension::NodePropBase &PropInfo)
{
	bool IsOK = false;
	//if (it->isTag())//仅仅输出标签节点的属性信息
	if (MyExtension::IsAvailableTagNode(it))
	{
		//遍历节点的所有属性
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
		//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			bool ISJump = false;//跳出循环的标记
			for (; Propit != Propend&&!ISJump; Propit++)
			{
				i++;
				if (PropIndex == i)
				{
					PropInfo.PropName = Propit->first;
					PropInfo.PropValue = Propit->second;
					IsOK = true;
					ISJump = true;
				}
			}
		}
		else
		{
			std::cout << "此标签并没有任何属性" << std::endl;
		}
	}
	return IsOK;
}




//根据属性的名称来查找相应的属性值
bool MyExtension::GetPropValueByPropName(tree<HTML::Node>::iterator it, std::string PropName, MyExtension::NodePropBase &PropInfo)
{
	bool IsOK = false;
	//if (it->isTag())//仅仅输出标签节点的属性信息
	if (MyExtension::IsAvailableTagNode(it))
	{
		//遍历节点的所有属性
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
		//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			bool ISJump = false;//跳出循环的标记
			for (; Propit != Propend&&!ISJump; Propit++)
			{
				if (PropName == Propit->first)
				{
					PropInfo.PropName = Propit->first;
					PropInfo.PropValue = Propit->second;
					IsOK = true;
					ISJump = true;
				}
			}
		}
		else
		{
			std::cout << "此标签并没有任何属性" << std::endl;
		}
	}
	return IsOK;
}




//获取所有有效的文本节点，也就是文本节点不为空，不是单纯的网址链接也不是换行符
std::string MyExtension::GetTextContentInDOM(tree<HTML::Node> dom)
{
	std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNode(it))
		{
			ResultStr += it->text();
		}
	}
	return ResultStr;
}

//获取当前节点的文本标签里的文本，不遍历子标签节点，也就是文本节点不为空，不是单纯的网址链接也不是换行符，也不是JS脚本
std::string MyExtension::GetTextContentCurrentNode(tree<HTML::Node> dom)
{
	std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (it.node->parent == dom.begin().node)//判断当前迭代器的父节点是否就是其传入的节点
		{
			if (MyExtension::IsAvailableTextNodeEx(it))
			{
				ResultStr += it->text();
			}
		}
	}
	return ResultStr;
}

//遍历当前节点所有子节点来获取所有有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
std::string MyExtension::GetTextContentInDOMEx(tree<HTML::Node> dom)
{
	std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNodeEx(it))
		{
			ResultStr += it->text();
		}
	}
	return ResultStr;
}




//显示所有有效的文本节点，也就是文本节点不为空，不是单纯的网址链接也不是换行符
void MyExtension::PrintTextContentInDOM(tree<HTML::Node> dom)
{
	//std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNode(it))
		{
			//ResultStr += it->text();
			std::cout << it->text() << std::endl;
		}
	}
}




//判断当前节点是否是有效的文本节点，排除那些换行符的文本节点和特定的css、js等文本
void MyExtension::PrintTextContentInDOMEx(tree<HTML::Node> dom)
{
	//std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (MyExtension::IsAvailableTextNodeEx(it))
		{
			//ResultStr += it->text();
			std::cout << it->text() << std::endl;
		}
	}
}




//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
//通过标签里的属性信息来确定相应节点，返回符合条件的所有节点
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB)
{
//#define OPENSHOW   //定义这个宏控制数据输出

	std::vector<tree<HTML::Node>> MatchedNodes;//存放所有匹配条件的节点
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//仅仅对标签节点作属性信息比较
		if (MyExtension::IsAvailableTagNode(it))
		{
			//遍历节点的所有属性
			it->parseAttributes();
			if (it->attributes().size() > 0)//判断此标签是否包含属性
			{
				std::map<std::string, std::string> NodeProperties = it->attributes();
				std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
				std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
				int i = 0;
				//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
				//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
				if (Propit->first.length() > 0 && Propit->first.length()<100)
				{
#ifdef OPENSHOW
					std::cout << "当前节点为：" << it->tagName() << std::endl;
					int Times = 0;
#endif
					size_t MatchTimes = 0;
					//遍历标签节点的所有属性，假设有n个属性，而过滤条件有m个，刚好属性的前m个和过滤条件完全匹配，这个时候，后面的节点就不再需要遍历了，如此可以节省(n-m)*m此比较了
					for (; Propit != Propend&&ConditionLIB.size() != MatchTimes; Propit++)
					{
						std::string PropName = Propit->first;
						std::string PropValue = Propit->second;
						//每遍历一个属性，就拿它到FilterCondition数组里进行进行比较
						bool IsMatched = false;//用来减少多余的匹配次数的，比如有n个属性过滤条件，在第2次匹配成功后，就可以节省后面n-2次多余的匹配了
						for (size_t n = 0; n < ConditionLIB.size() && !IsMatched; n++)
						{
#ifdef OPENSHOW
							Times++;
							std::cout << "第" << Times << "次匹配" << std::endl;
							std::cout << "属性名称匹配：" << ConditionLIB[n].PropName << "==" << PropName << std::endl;
							std::cout << "属性数值匹配：" << ConditionLIB[n].PropValue << "==" << PropValue << std::endl;
#endif

							if (ConditionLIB[n].PropName == PropName&&ConditionLIB[n].PropValue == PropValue)
							{
#ifdef OPENSHOW
								std::cout << "第" << MatchTimes + 1 << "次匹配成功" << std::endl;
#endif
								MatchTimes++;
								IsMatched = true;
							}
						}
						i++;
					}
#ifdef OPENSHOW
					std::cout << "总共成功匹配了" << MatchTimes << "次" << std::endl;
#endif
					//将完全符合条件的节点存放在MatchedNodes容器里
					if (MatchTimes == ConditionLIB.size())
						MatchedNodes.push_back((tree<HTML::Node>)it.node);
				}
#ifdef OPENSHOW
				else
					std::cout << "此标签并没有任何属性" << std::endl;
#endif
			}
		}
	}
	return MatchedNodes;
}





//通过标签里的属性来确定相应节点，并将所有符合条件的节点显示出来
void MyExtension::PrintSubNodeByTagProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB)
{
	//存放过滤条件
	//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//仅仅对标签节点作属性信息比较
		if (MyExtension::IsAvailableTagNode(it))
		{
			//遍历节点的所有属性
			it->parseAttributes();
			std::map<std::string, std::string> NodeProperties = it->attributes();
			std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
			std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
			int i = 0;
			std::cout << "当前节点为：" << it->tagName() << std::endl;
			//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
			//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
			if (Propit->first.length() > 0 && Propit->first.length()<100)
			{
				int MatchTimes = 0;
				int Times = 0;
				//遍历标签节点的所有属性，假设有n个属性，而过滤条件有m个，刚好属性的前m个和过滤条件完全匹配，这个时候，后面的节点就不再需要遍历了，如此可以节省(n-m)*m此比较了
				for (; Propit != Propend&&ConditionLIB.size()!=MatchTimes; Propit++)
				{
					std::string PropName = Propit->first;
					std::string PropValue = Propit->second;
					//每遍历一个属性，就拿它到FilterCondition数组里进行进行比较
					bool IsMatched = false;//用来减少多余的匹配次数的，比如有n个属性过滤条件，在第2次匹配成功后，就可以节省后面n-2次多余的匹配了
					for (size_t n = 0; n < ConditionLIB.size() && !IsMatched; n++)
					{
						Times++;
						std::cout << "第" << Times << "次匹配" << std::endl;
						std::cout << "属性名称匹配：" << ConditionLIB[n].PropName << "==" << PropName << std::endl;
						std::cout << "属性数值匹配：" << ConditionLIB[n].PropValue << "==" << PropValue << std::endl;
						if (ConditionLIB[n].PropName == PropName&&ConditionLIB[n].PropValue == PropValue)
						{
							std::cout << "第" << MatchTimes + 1 << "次匹配成功" << std::endl;
							MatchTimes++;
							IsMatched = true;
						}
					}
					i++;
				}
				std::cout << "总共成功匹配了" << MatchTimes << "次" << std::endl;
			}
			else
			{
				std::cout << "此标签并没有任何属性" << std::endl;
			}
		}
	}
}








//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
//通过标签里的属性信息来判断此节点是否包含在此过滤条件之内，返回判断结果，一般结合it.node->parent来使用，目的是用来进行数据修改操作时使用
bool MyExtension::IsNeedTagNodeByNodeProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB, MyExtension::MatchedMode MatchFlag)
{
	//仅仅处理当前标签而已
	bool IsNeed = false;
	//std::vector<tree<HTML::Node>> MatchedNodes;//存放所有匹配条件的节点
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	//if (it->isTag())//仅仅对标签节点作属性信息比较
	if (MyExtension::IsAvailableTagNode(it))
	{
		//遍历节点的所有属性
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
		//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			size_t MatchTimes = 0;
			//遍历标签节点的所有属性，假设有n个属性，而过滤条件有m个，刚好属性的前m个和过滤条件完全匹配，这个时候，后面的节点就不再需要遍历了，如此可以节省(n-m)*m此比较了
			for (; Propit != Propend&&ConditionLIB.size() != MatchTimes; Propit++)
			{
				std::string PropName = Propit->first;
				std::string PropValue = Propit->second;
				//每遍历一个属性，就拿它到FilterCondition数组里进行进行比较
				bool IsMatched = false;//用来减少多余的匹配次数的，比如有n个属性过滤条件，在第2次匹配成功后，就可以节省后面n-2次多余的匹配了
				for (size_t n = 0; n < ConditionLIB.size() && !IsMatched; n++)
				{
					if (ConditionLIB[n].PropName == PropName&&ConditionLIB[n].PropValue == PropValue)
					{
						MatchTimes++;
						IsMatched = true;
					}
				}
				i++;
			}
			switch (MatchFlag)
			{
			case MyExtension::FullMatching:
			{
								 //只有完全符合条件才返回
								 if (MatchTimes == ConditionLIB.size())
								 {
									 IsNeed = true;
								 }
			}
				break;
			case MyExtension::PartMatching:
			{
								 //只需部分符合条件就立即返回
								 if (MatchTimes>0)
								 {
									 IsNeed = true;
								 }
			}
				break;
			default:
				break;
			}
		}
	}
	return IsNeed;
}


//vector<MyExtension::NodePropBase> TagPropLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
//通过标签里标签名和属性信息来确定相应节点，返回符合条件的所有节点
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagInfo(tree<HTML::Node> dom, std::string TagName, std::vector<MyExtension::NodePropBase> TagPropLIB)
{
	std::vector<tree<HTML::Node>> MatchedNodes;//存放所有匹配条件的节点
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//仅仅对标签节点作属性信息比较
		if (MyExtension::IsAvailableTagNode(it))
		{
			if (it->tagName() == TagName)//先判断当前标签名是否符合条件，这样能够尽快筛选出所需判断属性的标签节点
			{
				//遍历节点的所有属性
				it->parseAttributes();
				std::map<std::string, std::string> NodeProperties = it->attributes();
				std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
				std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
				int i = 0;
				//找到包含属性的标签，在我们的感知中，属性名字一般不会超过100个字符
				//（由于在遇到<body>、<title>等标签时，Propit->first.length()获得到一个非常大的值，所以添加了属性名的字数限制）
				if (Propit->first.length() > 0 && Propit->first.length()<100)
				{
					size_t MatchTimes = 0;
					//遍历标签节点的所有属性，假设有n个属性，而过滤条件有m个，刚好属性的前m个和过滤条件完全匹配，这个时候，后面的节点就不再需要遍历了，如此可以节省(n-m)*m此比较了
					for (; Propit != Propend&&TagPropLIB.size() != MatchTimes; Propit++)
					{
						std::string PropName = Propit->first;
						std::string PropValue = Propit->second;
						//每遍历一个属性，就拿它到FilterCondition数组里进行进行比较
						bool IsMatched = false;//用来减少多余的匹配次数的，比如有n个属性过滤条件，在第2次匹配成功后，就可以节省后面n-2次多余的匹配了
						for (size_t n = 0; n < TagPropLIB.size() && !IsMatched; n++)
						{
							if (TagPropLIB[n].PropName == PropName&&TagPropLIB[n].PropValue == PropValue)
							{
								MatchTimes++;
								IsMatched = true;
							}
						}
						i++;
					}
					//将完全符合条件的节点存放在MatchedNodes容器里
					if (MatchTimes == TagPropLIB.size())
					{
						MatchedNodes.push_back((tree<HTML::Node>)it.node);
					}
				}
			}
		}
	}
	return MatchedNodes;
}







