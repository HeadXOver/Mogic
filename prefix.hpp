#pragma once

#include"Node.hpp"

namespace mgc {
    namespace ast {
        class Prefix : public Expression {
        public:
            Prefix() : Expression(NODE_PREFIX) {}
            ~Prefix() {}
            virtual void show() {
                cout << "Prefix:" << m_operator << "{" << endl;
                m_body->show();
                cout << "}" << endl;
            }

        public:
            string m_operator;
            std::shared_ptr<Expression> m_body;
        };

        class PrePrefix : public Precondition {
        public:
            PrePrefix() : Precondition(NODE_PREPREFIX) {}
            ~PrePrefix() {}
            virtual void show() {
                cout << "PrePrefix:"<< m_operator << "{" << endl;
                m_body->show();
                cout << "}" << endl;
            }

        public:
            string m_operator;
            std::shared_ptr<Precondition> m_body;
        };
    }
}