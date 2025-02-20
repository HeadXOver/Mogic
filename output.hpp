#pragma once

#include"Node.hpp"
#include<iostream>

using namespace std;

namespace mgc {
    namespace ast {
        class OutPut : public Statement {
        public:
            OutPut() : Statement(NODE_OUTPUT) {}
            ~OutPut() {}
            virtual void show() {
                cout << "output{" << endl;
                m_statement->show();
                cout << "}" << endl;
            }

        public:
            std::shared_ptr<Statement> m_statement;
        };
    }
}