#pragma once

#include"Node.hpp"
#include<iostream>

using namespace std;

namespace mgc {
    namespace ast {
        class Infer : public Statement {
        public:
            Infer() : Statement(NODE_INFER) {}
            ~Infer() {}
            virtual void show() {
                cout << "infer{" << endl;
                for (auto it = m_members.begin(); it != m_members.end(); it++) {
                    (*it).get()->show();
                }
                cout << "tnum:" << m_tnum << endl;
                cout << "}" << endl;
            }

        public:
            std::list<std::shared_ptr<ast::Identifier>> m_members;
            int m_tnum = -1;
        };
    }
}