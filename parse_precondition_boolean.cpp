#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition_boolean() {
	std::shared_ptr<PreBool> e(new PreBool());
	e->m_token = m_curr;
	e->m_bool = !(m_curr.type() == Token::TOKEN_FALSE);
	return e;
}