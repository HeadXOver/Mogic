#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class If :public Statement {
		public:
			If() : Statement(NODE_IF) {}
			~If() {}
			virtual void show() {
				std::cout << "if(" << std::endl;
				m_condition->show();
				std::cout << "){" << std::endl;
				m_block->show();
				std::cout << "}" << std::endl;
				if (m_else != nullptr) {
					std::cout << "else{" << std::endl;
					m_else->show();
					std::cout << "}" << std::endl;
				}
			}

		public:
			std::shared_ptr<Expression> m_condition;
			std::shared_ptr<Block> m_block;
			std::shared_ptr<Block> m_else = nullptr;
		};
	}
}