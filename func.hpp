#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class Func :public Statement {
		public:
			Func() : Statement(NODE_FUNC) {}
			~Func() {}
			virtual void show() {
				std::cout << "Func " << m_func_name << " (" << std::endl;
				for (auto& id : m_ids) {
					id->show();
				}
				std::cout << "){" << std::endl;
				m_block->show();
				std::cout << "}" << std::endl;
			}

		public:
			std::list<std::shared_ptr<Identifier>> m_ids;
			std::shared_ptr<Block> m_block;
			string m_func_name;
		};

		class FuncExpression :public Expression {
		public:
			FuncExpression() : Expression(NODE_FUNCEXPRESSION) {}
			~FuncExpression() {}
			virtual void show() {
				std::cout << "FuncExpression " << m_func_name << " (" << std::endl;
				for (auto& id : m_expressions) {
					id->show();
				}
				std::cout << ")" << std::endl;
			}

		public:
			std::list<std::shared_ptr<Expression>> m_expressions;
			string m_func_name;
		};
	}
}