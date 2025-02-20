#pragma once

#include"Node.hpp"

namespace mgc {
	namespace ast {
		class Integer :public Expression {
		public:
			Integer() : Expression(NODE_INTEGER), m_value(0) {}
			~Integer() {}
			virtual void show() {
				cout << m_value << endl;
			}

		public:
			int64_t m_value;
		};
	}
}