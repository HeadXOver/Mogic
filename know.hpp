#pragma once

#include"Node.hpp"
#include<iostream>

using namespace std;

namespace mgc {
    namespace ast {
        class Know : public Statement {
        public:
            Know() : Statement(NODE_KNOW) {}
            ~Know() {}
            virtual void show() {
                cout << "know{" << endl;
                m_precondition->show();
                cout << "}" << endl;
            }

        public:
            std::shared_ptr<Precondition> m_precondition;
        };
    }
}