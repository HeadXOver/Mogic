#pragma once

#include"Node.hpp"

namespace mgc {
    namespace ast {
        class Infix : public Expression {
        public:
            Infix() : Expression(NODE_INFIX) {}
            ~Infix() {}
            virtual void show() {
                cout << "Infix:" << m_operator << "{" << endl;
                cout << "Left:{" << endl;
                m_left->show();
                cout << "}" << endl;
                cout << "Right:{" << endl;
                m_right->show();
                cout << "}" << endl;
                cout << "}" << endl;
            }

        public:
            string m_operator;
            std::shared_ptr<Expression> m_left;
            std::shared_ptr<Expression> m_right;
        };

        class PreInfix : public Precondition {
        public:
            PreInfix() : Precondition(NODE_PREINFIX) {}
            ~PreInfix() {}
            virtual void show() {
                cout << "PreInfix:" << m_operator << "{" << endl;
                cout << "Left:{" << endl;
                m_left->show();
                cout << "}" << endl;
                cout << "Right:{" << endl;
                m_right->show();
                cout << "}" << endl;
                cout << "}" << endl;
            }

        public:
            string m_operator;
            std::shared_ptr<Precondition> m_left;
            std::shared_ptr<Precondition> m_right;
        };
    }
}