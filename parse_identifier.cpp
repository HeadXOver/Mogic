#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_identifier() {
	std::shared_ptr<Identifier> e(new Identifier());
	if (m_curr.type() != Token::TOKEN_IDENTIFIER) {
		cout << "error:\n parse_identifier():\n expect identifier\n" << "errorend" << endl;
	}
	e->m_token = m_curr;
	e->m_name = m_curr.literal().c_str();
	return e;
}
