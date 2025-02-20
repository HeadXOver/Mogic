#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class Block :public Statement {
		public:
			Block() : Statement(NODE_BLOCK) {}
			~Block() {}
			virtual void show() {
				std::cout << "Block{" << std::endl;
				for (auto& statement : m_statements) {
					statement->show();
				}
				std::cout << "}" << std::endl;
			}

		public:
			std::list<std::shared_ptr<Statement>> m_statements;
		};
	}
}