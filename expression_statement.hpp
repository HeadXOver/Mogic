#pragma once

#include "Node.hpp"

namespace mgc {
    namespace ast {
        class ExpressionStatement : public Statement {
        public:
            ExpressionStatement() : Statement(NODE_EXPRESSION_STATEMENT) {}
            ~ExpressionStatement() {}
            virtual void show() {
                if(m_expression) {
                    m_expression->show();
                }
            }

        public:
            std::shared_ptr<Expression> m_expression;
        };
    }
}