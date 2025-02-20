#pragma once

#include "Node.hpp"

namespace mgc {
	namespace ast {
		class Program :public Statement {
		public:
			Program() : Statement(NODE_PROGRAM) {}
			~Program() {}
			virtual void show() {
				for (auto& statement : m_statements) {
					statement->show();
				}
			}

		public:
			std::list<std::shared_ptr<Statement>> m_statements;
		};
	}
}