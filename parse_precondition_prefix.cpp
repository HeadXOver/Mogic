#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition_prefix() {
	std::shared_ptr<PrePrefix> e(new PrePrefix());
	e->m_token = m_curr;
	e->m_operator = m_curr.literal();
	int precedence = curr_token_precedence();
	next_token();
	e->m_body = parse_precondition(precedence);
	return e;
}