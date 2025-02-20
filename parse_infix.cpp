#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_infix(const std::shared_ptr<Expression>& left) {
	std::shared_ptr<Infix> e(new Infix());
	e->m_token = m_curr;
	e->m_operator = m_curr.literal();
	e->m_left = left;
	int precedence = curr_token_precedence();
	next_token();
	e->m_right = parse_expression(precedence);
 	return e;
}