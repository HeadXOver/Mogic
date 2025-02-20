#pragma once

#include"Node.hpp"

using namespace std;

namespace mgc {
	namespace ast {
		class Bool :public Expression {
		public:
			Bool() : Expression(NODE_BOOL), m_bool(0) {}
			~Bool() {}
			virtual void show() {
				if (m_bool) {
					cout << "True" << endl;
				}
				else {
					cout << "False" << endl;
				}
			}

		public:
			bool m_bool;
		};

		class PreBool :public Precondition {
		public:
			PreBool() : Precondition(NODE_BOOL), m_bool(0) {}
			~PreBool() {}
			virtual void show() {
				if (m_bool) {
					cout << "True" << endl;
				}
				else {
					cout << "False" << endl;
				}
			}

		public:
			bool m_bool;
		};
	}
}