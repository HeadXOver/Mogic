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
				NODE_BOOL = 0,					//布尔值
				NODE_INTEGER,					//整数
				NODE_INFIX,						//中缀表达式
				NODE_EXPRESSION_STATEMENT,		//表达式语句
				NODE_PROGRAM,					//根节点
				NODE_PREFIX,					//前缀表达式
				NODE_STRING,					//字符串
                NODE_DECLARATION,				//对象声明
				NODE_IDENTIFIER,				//标识符
				NODE_PRECONDITION,				//前提语句
				NODE_KNOW,						//知道语句
				NODE_PREINFIX,					//中缀前提式
				NODE_PREPREFIX,					//前缀前提式
				NODE_PREIDENTIFIER,				//前提标识符
				NODE_OUTPUT,					//输出语句
				NODE_INFER,						//推理语句
				NODE_BLOCK,						//块语句
				NODE_IF,						//if语句
				NODE_WHILE,						//while语句
                NODE_FOR,						//for语句
				NODE_FUNC,						//函数
				NODE_FUNCEXPRESSION,			//函数表达式

				NODE_NAT_DECLARATION,			//性质声明
				NODE_JUGE,						//性质赋予语句
				NODE_UNKNOWN,					//未知
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