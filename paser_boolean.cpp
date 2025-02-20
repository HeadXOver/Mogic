#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_boolean() {
	std::shared_ptr<Bool> e(new Bool());
	e->m_token = m_curr;
	e->m_bool = !(m_curr.type() == Token::TOKEN_FALSE);
	return e;
}
