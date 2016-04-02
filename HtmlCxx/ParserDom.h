#ifndef __HTML_PARSER_DOM_H__
#define __HTML_PARSER_DOM_H__

#include "ParserSax.h"
#include "tree.h"
#include <vector>
#include <algorithm>//��Сдת��������ͷ�ļ�

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
		//�˺������ձ����˱�д�ģ�ר������������tree<HTML::Node>::iterator������HTMLת�����ַ�����������������HTML��DOM��ת��Ϊ�ַ������Ӷ�ʵ�ֱ�����ĵĹ���
		bool unparseDom(tree<Node>::iterator itrbegin, tree<Node>::iterator itrend, std::string &strbuff, bool bUnparseEnd = false);
		std::string unparseDom(tree<Node> dom, bool bUnparseEnd = false);
		std::string unparseDom(tree<HTML::Node>::iterator_base ItNode, bool bUnparseEnd = false);
	} //namespace HTML

	//�Լ���չ�ģ��ų��˲���׼��DOM����Ϣ����ȡ��ص�����
	namespace MyExtension{
		//�趨���ԵĹ�������
		struct NodePropBase
		{
			std::string PropName;//��������it->attributes().begin()->first�õ���������ȫΪСд��ĸ
			std::string PropValue;//������ֵ��it->attributes().begin()->second�õ���������ֵ�ܹ�����ԭ���Ĵ�Сд��ʽ
			//�����ڲ������==
			bool operator==(NodePropBase value2)
			{
				return (value2.PropName == PropName && value2.PropValue == PropValue);
			}

			//��������������<<����Ҫ������Ϊ��Ԫ����
			friend std::ostream& operator<<(std::ostream& out, NodePropBase& value) {
				out << "PropName=" << value.PropName << "\n" << "PropValue=" << value.PropValue;
				return out;
			}
		};

		//���ֿ�ƥ��ģʽ
		typedef enum{
			FullMatching,
			PartMatching
		}MatchedMode;


		//�жϵ�ǰ�ڵ��Ƿ�Ϊ��Ч��ǩ�ڵ�
		bool IsAvailableTagNode(tree<HTML::Node> Node);
		//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ�
		bool IsAvailableTextNode(tree<HTML::Node>::iterator it);
		//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
		bool IsAvailableTextNodeEx(tree<HTML::Node>::iterator it);
		//��ȡ��ǰ�ڵ����е���Ч�ӽڵ�
		bool GetAllSubNode(tree_node_<HTML::Node> *CurrentNode, std::vector<tree<HTML::Node>> &SiblingNodeArr);
		//��ȡ��ǰ�ڵ����е���Ч�ӽڵ�
		std::vector<tree<HTML::Node>> GetAllSubNode(tree_node_<HTML::Node> *CurrentNode);
		//���DOM���ı�ǩ���
		std::string GetFullDOM(tree<HTML::Node> dom);
		//��ӡDOM���ı�ǩ���
		void PrintFullDOM(tree<HTML::Node> dom);
		//���DOM����ͬ���ı�ǩ�ڵ���Ϣ
		void PrintSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank);
		//��ȡDOM����ͬ���ı�ǩ�ڵ���Ϣ
		void GetSubDOM(std::vector<tree<HTML::Node>> TempArrNode, std::string &TagBlank, std::string &DOMStr);
		//��ȡ��ǰ�ڵ���ı���ǩ����ı����������ӱ�ǩ�ڵ�Ŷ��Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з���Ҳ����JS�ű�
		std::string GetTextContentCurrentNode(tree<HTML::Node> dom);
		//������ǰ�ڵ������ӽڵ�����ȡ������Ч���ı��ڵ㣬Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з���Ҳ����JS�ű�
		std::string GetTextContentInDOM(tree<HTML::Node> dom);
		//������ǰ�ڵ������ӽڵ�����ȡ������Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
		std::string GetTextContentInDOMEx(tree<HTML::Node> dom);
		//��ʾ������Ч���ı��ڵ㣬Ҳ�����ı��ڵ㲻Ϊ�գ����ǵ�������ַ����Ҳ���ǻ��з���Ҳ����JS�ű�
		void PrintTextContentInDOM(tree<HTML::Node> dom);
		//�жϵ�ǰ�ڵ��Ƿ�����Ч���ı��ڵ㣬�ų���Щ���з����ı��ڵ���ض���css��js���ı�
		void PrintTextContentInDOMEx(tree<HTML::Node> dom);


		
		//����DOM�������б�ǩ����
		void BrowAllPropInDOM(tree<HTML::Node> dom);
		//��ʾ��ǩ�ڵ������������Ϣ
		void ShowPropInfoInNode(tree<HTML::Node>::iterator it);
		//�������Ե���������������Ӧ������ֵ
		bool GetPropValueByPropIndex(tree<HTML::Node>::iterator it, int PropIndex, NodePropBase &PropInfo);
		//�������Ե�������������Ӧ������ֵ
		bool GetPropValueByPropName(tree<HTML::Node>::iterator it, std::string PropName, NodePropBase &PropInfo);
		//ͨ����ǩ���������Ϣ��ȷ����Ӧ�ڵ㣬���ط������������нڵ�
		std::vector<tree<HTML::Node>> GetSubNodeByTagProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB);
		//ͨ����ǩ���������ȷ����Ӧ�ڵ㣬�������з��������Ľڵ���ʾ����
		void PrintSubNodeByTagProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB);
		//vector<FilterCondition> ConditionLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
		//ͨ����ǩ���������Ϣ���жϴ˽ڵ��Ƿ�����ڴ˹�������֮�ڣ������жϽ����
		//һ����it.node->parent��ʹ�ã������޸�ĳ�������µ��ı�ʱ������Ҫʹ�ô˺�����ɸѡ��
		bool IsNeedTagNodeByNodeProp(tree<HTML::Node> dom, std::vector<NodePropBase> ConditionLIB, MatchedMode MatchFlag);
		//��ȡ��ǰ�ڵ���ָ����ǩ���������ӽڵ�
		bool GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::vector<tree<HTML::Node>> &SubNodeArr, std::string TagName);
		//��ȡ��ǰ�ڵ���ָ����ǩ���������ӽڵ�
		std::vector<tree<HTML::Node>> GetSubNodeByTagName(tree<HTML::Node> CurrentNode, std::string TagName);
		//vector<MyExtension::NodePropBase> TagPropLIB = { { "lkj", "asa4534safdfafga" }, { "ta", "aghse" } };
		//ͨ����ǩ���ǩ����������Ϣ��ȷ����Ӧ�ڵ㣬���ط������������нڵ�
		std::vector<tree<HTML::Node>> GetSubNodeByTagInfo(tree<HTML::Node> dom, std::string TagName, std::vector<NodePropBase> TagPropLIB);
	}

} //namespace htmlcxx

#endif
