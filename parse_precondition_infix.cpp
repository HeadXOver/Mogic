#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition_infix(const std::shared_ptr<Precondition>& left) {
	std::shared_ptr<PreInfix> e(new PreInfix());
	e->m_token = m_curr;
	e->m_operator = m_curr.literal();
	e->m_left = left;
	int precedence = curr_token_precedence();
	next_token();
	e->m_right = parse_precondition(precedence);
	return e;
}