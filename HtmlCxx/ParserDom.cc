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


//�˺������ձ����˱�д�ģ�ר������������tree<HTML::Node>::iterator������HTMLת�����ַ�����������������HTML��DOM��ת��Ϊ�ַ������Ӷ�ʵ�ֱ�����ĵĹ���
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

			// for�Υ��󥯥���Ȥ��ӥΩ`�ɤ��w�Ф�
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

//ItNode=it->node;������ItNode=(tree<HTML::Node>::iterator_base)it;
std::string HTML::unparseDom(tree<HTML::Node>::iterator_base ItNode, bool bUnparseEnd)
{
	return HTML::unparseDom((tree<HTML::Node>)ItNode);
}






//����DOM�������б�ǩ����
void MyExtension::BrowAllPropInDOM(tree<HTML::Node> dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//���������ǩ�ڵ�
		if (MyExtension::IsAvailableTagNode(it))
		{
			//�����ڵ����������
			it->parseAttributes();
			std::map<std::string, std::string> NodeProperties = it->attributes();
			std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
			std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
			int i = 0;
			//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
			//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
			if (Propit->first.length() > 0 && Propit->first.length()<100)
			{
				std::cout << "��ǰ��ǩΪΪ��" << it->tagName() << std::endl;
				std::cout << "�������д˱�ǩ���������ԣ�" << std::endl;
				for (; Propit != Propend; Propit++)
				{
					std::string PropName = Propit->first;
					std::string PropValue = Propit->second;
					//cout << "��" << i << "�����Ե�����Ϊ��" << PropName << endl;
					//cout << "��" << i << "�����Ե���ֵΪ��" << PropValue << endl;
					std::cout << "��" << i + 1 << "�����ԣ�" << std::string("\"") + PropName + std::string("\"") << "=" << std::string("\"") + PropValue + std::string("\"") << std::endl;
					i++;
				}
			}
			else
			{
				std::cout << "�˱�ǩ��û���κ�����" << std::endl;
			}
		}
	}
}






//��ȡ��ǰ�ڵ�������Ч�ӽڵ�
bool MyExtension::GetAllSubNode(tree_node_<HTML::Node> *CurrentNode, std::vector<tree<HTML::Node>> &SiblingNodeArr)
{
	bool IsOK = true;
	//�ҵ��˸��ڵ�ĵ�һ���ӽڵ�
	tree_node_<HTML::Node> *BeginNode = CurrentNode->first_child;
	//��������ͬ���ڵ㣬ֱ���Ҳ���ͬ���ڵ�Ϊֹ������ҪCurrentNode->last_child��Ϊ�������
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




//��ȡ��ǰ�ڵ���ָ����ǩ���������ӽڵ�
bool MyExtension::GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::vector<tree<HTML::Node>> &SubNodeArr, std::string TagName)
{
	bool IsOK = false;
	//�ҵ��˸��ڵ�ĵ�һ���ӽڵ�
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


//��ȡ��ǰ�ڵ���ָ����ǩ���������ӽڵ�
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::string TagName)
{
	std::vector<tree<HTML::Node>> SubNodeArr;
	if (MyExtension::GetSubNodeByTagName(CurrentNode, SubNodeArr, TagName))
	{
		return SubNodeArr;
	}
	return SubNodeArr;
}



//�жϵ�ǰ�ڵ��Ƿ�Ϊ��Ч��ǩ�ڵ�
bool MyExtension::IsAvailableTagNode(tree<HTML::Node> Node)
{
	bool IsAvailable = false;
	std::string tempstr = Node.begin()->tagName();
	//�жϵ�ǰ�ڵ������Ƿ�Ϊ��ǩ�����ұ�ǩ�������Ҳ�Ϊ?
	if (Node.begin()->isTag() && tempstr != std::string("?"))
	{
		//ȥ����ǩ������ܴ��ڵ������ַ�
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





//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ�
bool MyExtension::IsAvailableTextNode(tree<HTML::Node>::iterator it)
{
	bool IsAvailable = false;
	if (!it->isComment() && !it->isTag())
	{
		//��������htmlcxx�������Щ�����Ļ��з�Ҳ����Ϊһ���ı�����ȡ�ģ�
		//������Ҫ�������������ı��ڵ�������
		std::string tempstr = it->tagName();
		htmlcxx::Extensions::GlobalReStr(tempstr, " ", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\n", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\r", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "\t", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "<br/>", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "<br>", "");
		htmlcxx::Extensions::GlobalReStr(tempstr, "&nbsp;", "");//ȥ�������еĿհ׸�
		htmlcxx::Extensions::GlobalReStr(tempstr, "&ensp;", "");//�뷽��Ŀհ�
		htmlcxx::Extensions::GlobalReStr(tempstr, "&emsp;", "");//ȫ����Ŀհ�

		if (tempstr.length() > 0)
		{
			IsAvailable = true;
		}

	}
	return IsAvailable;
}



//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
bool MyExtension::IsAvailableTextNodeEx(tree<HTML::Node>::iterator it)
{
	bool IsAvailable = false;
	if (MyExtension::IsAvailableTextNode(it))
	{
		////���˵�JS�ű�����Ӧ�ı�ǩ��
		////���ǵ�htmlcxx��htm�Ĵ�Сд���У������Ƚ���ǩ���Ӣ��ȫ��ת��Ϊ��д
		const char* PreTagName = it.node->parent->data.tagName().c_str(); //�ı���ǩ�ĸ���ǩ
		////unsigned int SubNumInPreNode = ((tree<HTML::Node>)it.node->parent).begin().number_of_children();//����ǩ�µ��ӽڵ����

		//��Gumbo������ȡ������
		std::string empty_tags = "|area|base|basefont|bgsound|br|command|col|embed|event-source|frame|hr|image|img|input|keygen|link|menuitem|meta|param|source|spacer|track|wbr|";
		std::string preserve_whitespace = "|pre|textarea|script|style|";
		//vector<string> FilterLIB = { "SCRIPT", "STYLE", "BODY", "LINK" };
		std::vector<std::string> empty_tagsLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(empty_tags.c_str()), "|", "|");
		std::vector<std::string> preserve_whitespaceLIB = htmlcxx::Extensions::GetArrBySpliteString(htmlcxx::Extensions::SmallCharToBigChar(preserve_whitespace.c_str()), "|", "|");
		std::vector<std::string> FilterLIB;
		FilterLIB.insert(FilterLIB.begin(), empty_tagsLIB.begin(), empty_tagsLIB.end());
		FilterLIB.insert(FilterLIB.begin(), preserve_whitespaceLIB.begin(), preserve_whitespaceLIB.end());
		//�������ֿ�������б�ǩ
		if (!htmlcxx::Extensions::FilterStr(htmlcxx::Extensions::SmallCharToBigChar(PreTagName), FilterLIB, 2))
		{
			//�����ж�֮�󣬿���ȷ���˵�������Ӧ���ı��ڵ�����Ч��
			IsAvailable = true;
		}
	}

	return IsAvailable;
}



//���DOM���ı�ǩ���
std::string MyExtension::GetFullDOM(tree<HTML::Node> dom)
{
	std::string FullDOMStr = "";
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	tree_node_<HTML::Node> *TempNode = NULL;
	bool IsJump = false;
	//�ҵ��˽ڵ��µ�һ����Ч�ı�ǩ�ڵ�
	for (; it != end&&!IsJump; ++it)
	{
		//cout << "��ǰ�� ���ǩ��Ϊ��"<< it->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(it))
		{
			//cout << "��ǰ�ҵ��Ľڵ��ǩ��Ϊ��" << it->tagName() << endl;
			IsJump = true;
			std::vector<tree<HTML::Node>> TempArrNode = MyExtension::GetAllSubNode(it.node);//�õ��ӽڵ�
			std::string TagBlank = "";
			FullDOMStr += it->text() + std::string("\n");
			MyExtension::GetSubDOM(TempArrNode, TagBlank, FullDOMStr);
			FullDOMStr += it->closingText() + std::string("\n");
		}
	}
	return FullDOMStr;
}




//���DOM���ı�ǩ���
void MyExtension::PrintFullDOM(tree<HTML::Node> dom)
{
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	tree_node_<HTML::Node> *TempNode = NULL;
	bool IsJump = false;
	//�ҵ��˽ڵ��µ�һ����Ч�ı�ǩ�ڵ�
	for (; it != end&&!IsJump; ++it)
	{
		//cout << "��ǰ�� ���ǩ��Ϊ��"<< it->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(it))
		{
			//cout << "��ǰ�ҵ��Ľڵ��ǩ��Ϊ��" << it->tagName() << endl;
			IsJump = true;
			std::vector<tree<HTML::Node>> TempArrNode = MyExtension::GetAllSubNode(it.node);//�ҵ��˽ڵ��µ������ӽڵ�
			std::string TagBlank = "";
			std::cout << "<" << it->tagName() << ">" << std::endl;
			//PrintSiblingDOM(TempArrNode, TagBlank);
			MyExtension::PrintSubDOM(TempArrNode, TagBlank);//��ӡ�����ӽڵ�ı�ǩ��Ϣ
			std::cout << it->closingText() << std::endl;
		}
	}
}






//���DOM�����ӽڵ�ı�ǩ�ڵ���Ϣ
void MyExtension::GetSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank, std::string &DOMStr)
{
	TagBlank += std::string("  ");
	std::string TempBlank = TagBlank;
	for (size_t n = 0; n < TempArrNode.size(); n++)
	{
		//cout << "�ӽڵ�����Ϊ��" <<TempArrNode[n].begin()->tagName() << endl;
		//if (TempArrNode[n].begin()->isTag() && TempArrNode[n].begin()->tagName() != string("?") && TempArrNode[n].begin()->tagName().length()>0)
		if (MyExtension::IsAvailableTagNode(TempArrNode[n]))
		{
			DOMStr += TempBlank + TempArrNode[n].begin()->text() + std::string("\n");
			MyExtension::GetSubDOM(GetAllSubNode(TempArrNode[n].begin().node), TagBlank, DOMStr);
			if (TempArrNode[n].begin()->closingText().length()>0)//���<xxx ID="afd" />֮��Ľڵ��������ж�
			{
				DOMStr += TempBlank + TempArrNode[n].begin()->closingText() + std::string("\n");
			}
		}
	}
}



//���DOM�����ӽڵ�ı�ǩ�ڵ���Ϣ
void MyExtension::PrintSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank)
{
	TagBlank += std::string("  ");
	std::string TempBlank = TagBlank;
	for (size_t n = 0; n < TempArrNode.size(); n++)
	{
		//cout << "�ӽڵ�����Ϊ��" <<TempArrNode[n].begin()->tagName() << endl;
		if (MyExtension::IsAvailableTagNode(TempArrNode[n]))
		{
			std::cout << TempBlank << TempArrNode[n].begin()->text() << std::endl;
			MyExtension::PrintSubDOM(MyExtension::GetAllSubNode(TempArrNode[n].begin().node), TagBlank);
			if (TempArrNode[n].begin()->closingText().length()>0)//���<xxx ID="afd" />֮��Ľڵ��������ж�
			{
				std::cout << TempBlank << TempArrNode[n].begin()->closingText() << std::endl;
			}
		}
	}
}



//��ʾ��ǩ�ڵ������������Ϣ
void MyExtension::ShowPropInfoInNode(tree<HTML::Node>::iterator it)
{
	//if (it->isTag())//���������ǩ�ڵ��������Ϣ
	if (MyExtension::IsAvailableTagNode(it))
	{
		//�����ڵ����������
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
		//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			std::cout << "��ǰ��ǩΪΪ��" << it->tagName() << std::endl;
			std::cout << "�������д˱�ǩ���������ԣ�" << std::endl;
			for (; Propit != Propend; Propit++)
			{
				std::string PropName = Propit->first;
				std::string PropValue = Propit->second;
				std::cout << "��" << i + 1 << "�����ԣ�" << std::string("\"") + PropName + std::string("\"") << "=" << std::string("\"") + PropValue + std::string("\"") << std::endl;
				i++;
			}
		}
		else
		{
			std::cout << "�˱�ǩ��û���κ�����" << std::endl;
		}
	}
}



//�������Ե���������������Ӧ������ֵ
bool MyExtension::GetPropValueByPropIndex(tree<HTML::Node>::iterator it, int PropIndex, MyExtension::NodePropBase &PropInfo)
{
	bool IsOK = false;
	//if (it->isTag())//���������ǩ�ڵ��������Ϣ
	if (MyExtension::IsAvailableTagNode(it))
	{
		//�����ڵ����������
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
		//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			bool ISJump = false;//����ѭ���ı��
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
			std::cout << "�˱�ǩ��û���κ�����" << std::endl;
		}
	}
	return IsOK;
}




//�������Ե�������������Ӧ������ֵ
bool MyExtension::GetPropValueByPropName(tree<HTML::Node>::iterator it, std::string PropName, MyExtension::NodePropBase &PropInfo)
{
	bool IsOK = false;
	//if (it->isTag())//���������ǩ�ڵ��������Ϣ
	if (MyExtension::IsAvailableTagNode(it))
	{
		//�����ڵ����������
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
		//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			bool ISJump = false;//����ѭ���ı��
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
			std::cout << "�˱�ǩ��û���κ�����" << std::endl;
		}
	}
	return IsOK;
}




//��ȡ������Ч���ı��ڵ㣬Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з�
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

//��ȡ��ǰ�ڵ���ı���ǩ����ı����������ӱ�ǩ�ڵ㣬Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з���Ҳ����JS�ű�
std::string MyExtension::GetTextContentCurrentNode(tree<HTML::Node> dom)
{
	std::string ResultStr = "";
	std::vector<unsigned int> SimilDepthNums;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		if (it.node->parent == dom.begin().node)//�жϵ�ǰ�������ĸ��ڵ��Ƿ�����䴫��Ľڵ�
		{
			if (MyExtension::IsAvailableTextNodeEx(it))
			{
				ResultStr += it->text();
			}
		}
	}
	return ResultStr;
}

//������ǰ�ڵ������ӽڵ�����ȡ������Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
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




//��ʾ������Ч���ı��ڵ㣬Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з�
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




//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
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
//ͨ����ǩ���������Ϣ��ȷ����Ӧ�ڵ㣬���ط������������нڵ�
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB)
{
//#define OPENSHOW   //�������������������

	std::vector<tree<HTML::Node>> MatchedNodes;//�������ƥ�������Ľڵ�
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//�����Ա�ǩ�ڵ���������Ϣ�Ƚ�
		if (MyExtension::IsAvailableTagNode(it))
		{
			//�����ڵ����������
			it->parseAttributes();
			if (it->attributes().size() > 0)//�жϴ˱�ǩ�Ƿ��������
			{
				std::map<std::string, std::string> NodeProperties = it->attributes();
				std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
				std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
				int i = 0;
				//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
				//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
				if (Propit->first.length() > 0 && Propit->first.length()<100)
				{
#ifdef OPENSHOW
					std::cout << "��ǰ�ڵ�Ϊ��" << it->tagName() << std::endl;
					int Times = 0;
#endif
					size_t MatchTimes = 0;
					//������ǩ�ڵ���������ԣ�������n�����ԣ�������������m�����պ����Ե�ǰm���͹���������ȫƥ�䣬���ʱ�򣬺���Ľڵ�Ͳ�����Ҫ�����ˣ���˿��Խ�ʡ(n-m)*m�˱Ƚ���
					for (; Propit != Propend&&ConditionLIB.size() != MatchTimes; Propit++)
					{
						std::string PropName = Propit->first;
						std::string PropValue = Propit->second;
						//ÿ����һ�����ԣ���������FilterCondition��������н��бȽ�
						bool IsMatched = false;//�������ٶ����ƥ������ģ�������n�����Թ����������ڵ�2��ƥ��ɹ��󣬾Ϳ��Խ�ʡ����n-2�ζ����ƥ����
						for (size_t n = 0; n < ConditionLIB.size() && !IsMatched; n++)
						{
#ifdef OPENSHOW
							Times++;
							std::cout << "��" << Times << "��ƥ��" << std::endl;
							std::cout << "��������ƥ�䣺" << ConditionLIB[n].PropName << "==" << PropName << std::endl;
							std::cout << "������ֵƥ�䣺" << ConditionLIB[n].PropValue << "==" << PropValue << std::endl;
#endif

							if (ConditionLIB[n].PropName == PropName&&ConditionLIB[n].PropValue == PropValue)
							{
#ifdef OPENSHOW
								std::cout << "��" << MatchTimes + 1 << "��ƥ��ɹ�" << std::endl;
#endif
								MatchTimes++;
								IsMatched = true;
							}
						}
						i++;
					}
#ifdef OPENSHOW
					std::cout << "�ܹ��ɹ�ƥ����" << MatchTimes << "��" << std::endl;
#endif
					//����ȫ���������Ľڵ�����MatchedNodes������
					if (MatchTimes == ConditionLIB.size())
						MatchedNodes.push_back((tree<HTML::Node>)it.node);
				}
#ifdef OPENSHOW
				else
					std::cout << "�˱�ǩ��û���κ�����" << std::endl;
#endif
			}
		}
	}
	return MatchedNodes;
}





//ͨ����ǩ���������ȷ����Ӧ�ڵ㣬�������з��������Ľڵ���ʾ����
void MyExtension::PrintSubNodeByTagProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB)
{
	//��Ź�������
	//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//�����Ա�ǩ�ڵ���������Ϣ�Ƚ�
		if (MyExtension::IsAvailableTagNode(it))
		{
			//�����ڵ����������
			it->parseAttributes();
			std::map<std::string, std::string> NodeProperties = it->attributes();
			std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
			std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
			int i = 0;
			std::cout << "��ǰ�ڵ�Ϊ��" << it->tagName() << std::endl;
			//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
			//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
			if (Propit->first.length() > 0 && Propit->first.length()<100)
			{
				int MatchTimes = 0;
				int Times = 0;
				//������ǩ�ڵ���������ԣ�������n�����ԣ�������������m�����պ����Ե�ǰm���͹���������ȫƥ�䣬���ʱ�򣬺���Ľڵ�Ͳ�����Ҫ�����ˣ���˿��Խ�ʡ(n-m)*m�˱Ƚ���
				for (; Propit != Propend&&ConditionLIB.size()!=MatchTimes; Propit++)
				{
					std::string PropName = Propit->first;
					std::string PropValue = Propit->second;
					//ÿ����һ�����ԣ���������FilterCondition��������н��бȽ�
					bool IsMatched = false;//�������ٶ����ƥ������ģ�������n�����Թ����������ڵ�2��ƥ��ɹ��󣬾Ϳ��Խ�ʡ����n-2�ζ����ƥ����
					for (size_t n = 0; n < ConditionLIB.size() && !IsMatched; n++)
					{
						Times++;
						std::cout << "��" << Times << "��ƥ��" << std::endl;
						std::cout << "��������ƥ�䣺" << ConditionLIB[n].PropName << "==" << PropName << std::endl;
						std::cout << "������ֵƥ�䣺" << ConditionLIB[n].PropValue << "==" << PropValue << std::endl;
						if (ConditionLIB[n].PropName == PropName&&ConditionLIB[n].PropValue == PropValue)
						{
							std::cout << "��" << MatchTimes + 1 << "��ƥ��ɹ�" << std::endl;
							MatchTimes++;
							IsMatched = true;
						}
					}
					i++;
				}
				std::cout << "�ܹ��ɹ�ƥ����" << MatchTimes << "��" << std::endl;
			}
			else
			{
				std::cout << "�˱�ǩ��û���κ�����" << std::endl;
			}
		}
	}
}








//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
//ͨ����ǩ���������Ϣ���жϴ˽ڵ��Ƿ�����ڴ˹�������֮�ڣ������жϽ����һ����it.node->parent��ʹ�ã�Ŀ�����������������޸Ĳ���ʱʹ��
bool MyExtension::IsNeedTagNodeByNodeProp(tree<HTML::Node> dom, std::vector<MyExtension::NodePropBase> ConditionLIB, MyExtension::MatchedMode MatchFlag)
{
	//��������ǰ��ǩ����
	bool IsNeed = false;
	//std::vector<tree<HTML::Node>> MatchedNodes;//�������ƥ�������Ľڵ�
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	//if (it->isTag())//�����Ա�ǩ�ڵ���������Ϣ�Ƚ�
	if (MyExtension::IsAvailableTagNode(it))
	{
		//�����ڵ����������
		it->parseAttributes();
		std::map<std::string, std::string> NodeProperties = it->attributes();
		std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
		std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
		int i = 0;
		//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
		//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
		if (Propit->first.length() > 0 && Propit->first.length()<100)
		{
			size_t MatchTimes = 0;
			//������ǩ�ڵ���������ԣ�������n�����ԣ�������������m�����պ����Ե�ǰm���͹���������ȫƥ�䣬���ʱ�򣬺���Ľڵ�Ͳ�����Ҫ�����ˣ���˿��Խ�ʡ(n-m)*m�˱Ƚ���
			for (; Propit != Propend&&ConditionLIB.size() != MatchTimes; Propit++)
			{
				std::string PropName = Propit->first;
				std::string PropValue = Propit->second;
				//ÿ����һ�����ԣ���������FilterCondition��������н��бȽ�
				bool IsMatched = false;//�������ٶ����ƥ������ģ�������n�����Թ����������ڵ�2��ƥ��ɹ��󣬾Ϳ��Խ�ʡ����n-2�ζ����ƥ����
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
								 //ֻ����ȫ���������ŷ���
								 if (MatchTimes == ConditionLIB.size())
								 {
									 IsNeed = true;
								 }
			}
				break;
			case MyExtension::PartMatching:
			{
								 //ֻ�貿�ַ�����������������
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
//ͨ����ǩ���ǩ����������Ϣ��ȷ����Ӧ�ڵ㣬���ط������������нڵ�
std::vector<tree<HTML::Node>> MyExtension::GetSubNodeByTagInfo(tree<HTML::Node> dom, std::string TagName, std::vector<MyExtension::NodePropBase> TagPropLIB)
{
	std::vector<tree<HTML::Node>> MatchedNodes;//�������ƥ�������Ľڵ�
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	for (; it != end; ++it)
	{
		//if (it->isTag())//�����Ա�ǩ�ڵ���������Ϣ�Ƚ�
		if (MyExtension::IsAvailableTagNode(it))
		{
			if (it->tagName() == TagName)//���жϵ�ǰ��ǩ���Ƿ���������������ܹ�����ɸѡ�������ж����Եı�ǩ�ڵ�
			{
				//�����ڵ����������
				it->parseAttributes();
				std::map<std::string, std::string> NodeProperties = it->attributes();
				std::map<std::string, std::string>::iterator Propit = NodeProperties.begin();
				std::map<std::string, std::string>::iterator Propend = NodeProperties.end();
				int i = 0;
				//�ҵ��������Եı�ǩ�������ǵĸ�֪�У���������һ�㲻�ᳬ��100���ַ�
				//������������<body>��<title>�ȱ�ǩʱ��Propit->first.length()��õ�һ���ǳ����ֵ��������������������������ƣ�
				if (Propit->first.length() > 0 && Propit->first.length()<100)
				{
					size_t MatchTimes = 0;
					//������ǩ�ڵ���������ԣ�������n�����ԣ�������������m�����պ����Ե�ǰm���͹���������ȫƥ�䣬���ʱ�򣬺���Ľڵ�Ͳ�����Ҫ�����ˣ���˿��Խ�ʡ(n-m)*m�˱Ƚ���
					for (; Propit != Propend&&TagPropLIB.size() != MatchTimes; Propit++)
					{
						std::string PropName = Propit->first;
						std::string PropValue = Propit->second;
						//ÿ����һ�����ԣ���������FilterCondition��������н��бȽ�
						bool IsMatched = false;//�������ٶ����ƥ������ģ�������n�����Թ����������ڵ�2��ƥ��ɹ��󣬾Ϳ��Խ�ʡ����n-2�ζ����ƥ����
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
					//����ȫ���������Ľڵ�����MatchedNodes������
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







