#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition(int precedence) {
	auto prefix = m_precondition_prefix_parse_fns.find(m_curr.type());
	if (prefix == m_precondition_prefix_parse_fns.end()) {
		cout << "error: " << m_curr.name() << " is not a precondition prefix operator" << endl;
		no_precondition_prefix_parse_fn_error(m_curr.type());
		return nullptr;
	}
	std::shared_ptr<Precondition> e = (this->*(prefix->second))();
	while (!peek_token_is(Token::TOKEN_SEMICOLON) && precedence < peek_token_precedence()) {
		auto infix = m_precondition_infix_parse_fns.find(m_peek.type());
		if (infix == m_precondition_infix_parse_fns.end()) {
			return e;
		}
		next_token();
		e = (this->*(infix->second))(e);
	}
	return e;
}
