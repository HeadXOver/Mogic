#pragma once

#include"Node.hpp"

namespace mgc {
	namespace ast {
		class Declaration :public Expression {
		public:
			Declaration() : Expression(NODE_DECLARATION), m_name("") {}
			~Declaration() {}
			virtual void show() {
				cout << m_name << " declaretion" << endl;
			}

		public:
			string m_name;
		};
	}
}