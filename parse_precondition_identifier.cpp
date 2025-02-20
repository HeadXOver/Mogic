#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition_identifier() {
	std::shared_ptr<PreIdentifier> e(new PreIdentifier());
	if (m_curr.type() != Token::TOKEN_IDENTIFIER) {
		cout << "error:\n parse_precondition_identifier():\n expect identifier\n" << "errorend" << endl;
	}
	e->m_token = m_curr;
	e->m_name = m_curr.literal().c_str();
	return e;
}
