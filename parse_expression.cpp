#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_expression(int precedence) {
	if (curr_token_is(Token::TOKEN_IDENTIFIER)) {
		if (m_peek.type() == Token::TOKEN_LPAREN) {
			std::shared_ptr<FuncExpression> s(new FuncExpression());
			s->m_func_name = m_curr.literal().c_str();
			next_token();
			std::shared_ptr<Expression> e;
			do {
				if (m_peek.type() == Token::TOKEN_COMMA) {
					next_token();
				}
				next_token();
				e = parse_expression(LOWEST);
				s->m_expressions.push_back(e);
			} while (m_peek.type() == Token::TOKEN_COMMA);
			expect_peek_token(Token::TOKEN_RPAREN);
			return s;
		}
	}
	auto prefix = m_prefix_parse_fns.find(m_curr.type());
	if (prefix == m_prefix_parse_fns.end()) {
		cout << "error: " << m_curr.name() << " is not a prefix operator" << endl;
		next_token();
		no_prefix_parse_fn_error(m_curr.type());
		return nullptr;
	}
	std::shared_ptr<Expression> e = (this->*(prefix->second))();
	while (!peek_token_is(Token::TOKEN_SEMICOLON) && precedence<peek_token_precedence()) {
		auto infix = m_infix_parse_fns.find(m_peek.type());
		if (infix == m_infix_parse_fns.end()) {
			return e;
		}
		next_token();
		e = (this->*(infix->second))(e);
	}
	return e;
}