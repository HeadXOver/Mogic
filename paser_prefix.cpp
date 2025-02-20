#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_prefix() {
	std::shared_ptr<Prefix> e(new Prefix());
	e->m_token = m_curr;
	e->m_operator = m_curr.literal();
	if (e->m_operator == "obj" || e->m_operator == "propo" || e->m_operator == "int" || e->m_operator == "bool" || e->m_operator == "predi") {
		next_token();
		e->m_body = parse_identifier();
		return e;
	}
	int precedence = curr_token_precedence();
	next_token();
	e->m_body = parse_expression(precedence);
	return e;
}