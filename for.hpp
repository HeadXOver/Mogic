#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class For :public Statement {
		public:
			For() : Statement(NODE_FOR) {}
			~For() {}
			virtual void show() {
				std::cout << "For(" << std::endl;
				m_time->show();
				std::cout << "){" << std::endl;
				m_block->show();
				std::cout << "}" << std::endl;
			}

		public:
			std::shared_ptr<Expression> m_time;
			std::shared_ptr<Block> m_block;
		};
	}
}