#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_group() {
	next_token();
	auto e = parse_expression(LOWEST);
	if (!expect_peek_token(Token::TOKEN_RPAREN)) {
		return nullptr;
	}
	return e;
}