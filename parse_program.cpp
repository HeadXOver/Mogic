#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Program> Paser::parse_program() {
	while (curr_token_is(Token::TOKEN_SEMICOLON)) {
		next_token();
	}
	std::shared_ptr<Program> s(new Program());
	while (m_curr.type() != Token::TOKEN_EOF) {
		auto stmt = parse_statement();
		if (stmt) {
			s->m_statements.push_back(stmt);
		}
		if (!curr_token_is(Token::TOKEN_RBRACKET)) {
			if (!expect_peek_token(Token::TOKEN_SEMICOLON)) {
				break;
			}
		}
		else {
			next_token();
		}
		while (curr_token_is(Token::TOKEN_SEMICOLON)) {
			next_token();
		}
	}
	return s;
}