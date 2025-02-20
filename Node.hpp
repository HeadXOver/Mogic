#pragma once

#include "Token.hpp"
#include <map>
#include<list>
#include<memory>
#include<list>
#include<iostream>

using namespace mgc::token;

namespace mgc {
	namespace ast {
		class Node {
		public:
			enum Type
			{
				NODE_BOOL = 0,					//����ֵ
				NODE_INTEGER,					//����
				NODE_INFIX,						//��׺���ʽ
				NODE_EXPRESSION_STATEMENT,		//���ʽ���
				NODE_PROGRAM,					//���ڵ�
				NODE_PREFIX,					//ǰ׺���ʽ
				NODE_STRING,					//�ַ���
                NODE_DECLARATION,				//��������
				NODE_IDENTIFIER,				//��ʶ��
				NODE_PRECONDITION,				//ǰ�����
				NODE_KNOW,						//֪�����
				NODE_PREINFIX,					//��׺ǰ��ʽ
				NODE_PREPREFIX,					//ǰ׺ǰ��ʽ
				NODE_PREIDENTIFIER,				//ǰ���ʶ��
				NODE_OUTPUT,					//������
				NODE_INFER,						//�������
				NODE_BLOCK,						//�����
				NODE_IF,						//if���
				NODE_WHILE,						//while���
                NODE_FOR,						//for���
				NODE_FUNC,						//����
				NODE_FUNCEXPRESSION,			//�������ʽ

				NODE_NAT_DECLARATION,			//��������
				NODE_JUGE,						//���ʸ������
				NODE_UNKNOWN,					//δ֪
			};

			Node() : m_type(Type::NODE_UNKNOWN) {}
			Node(Type type) : m_type(type) {}

			virtual ~Node() {}

			Type type() const { return m_type; }
			string name() const;

			Type m_type;
			Token m_token;
			static std::map<Type, string> m_names;
		};

		class Expression : public Node {
		public:
			Expression() :Node() {}
			Expression(Type type) :Node(type) {}
			~Expression() {}
			virtual void show() = 0;
		};

		class Statement : public Node {
		public:
			Statement() :Node() {}
			Statement(Type type) :Node(type) {}
			~Statement() {}
			virtual void show() = 0;
		};

		class Precondition : public Node {
		public:
			Precondition() :Node() {}
			Precondition(Type type) :Node(type) {}
			~Precondition() {}
			virtual void show() = 0;
		};
	}
}