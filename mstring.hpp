#pragma once

#include"Node.hpp"

namespace mgc {
	namespace ast {
		class Mstring :public Expression {
		public:
			Mstring() : Expression(NODE_STRING), m_string("") {}
			~Mstring() {}
			virtual void show() {
				cout << m_string << endl;
			}

		public:
			string m_string;
		};
	}
}