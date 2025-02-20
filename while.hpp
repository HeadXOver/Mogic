#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class While :public Statement {
		public:
			While() : Statement(NODE_WHILE) {}
			~While() {}
			virtual void show() {
				std::cout << "While(" << std::endl;
				m_condition->show();
				std::cout << "){" << std::endl;
				m_block->show();
				std::cout << "}" << std::endl;
			}

		public:
			std::shared_ptr<Expression> m_condition;
			std::shared_ptr<Block> m_block;
		};
	}
}