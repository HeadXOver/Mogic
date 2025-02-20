#pragma once

#include"Node.hpp"

namespace mgc {
	namespace ast {
		class Identifier :public Expression {
		public:
			Identifier() : Expression(NODE_IDENTIFIER), m_name("") {}
			~Identifier() {}
			virtual void show() {
				cout << m_name << endl;
			}

		public:
			string m_name;
		};

		class PreIdentifier :public Precondition {
		public:
			PreIdentifier() : Precondition(NODE_PREIDENTIFIER), m_name("") {}
			~PreIdentifier() {}
			virtual void show() {
				cout << m_name << endl;
			}

		public:
			string m_name;
		};
	}
}