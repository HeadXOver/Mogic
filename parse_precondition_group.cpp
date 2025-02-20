#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Precondition> Paser::parse_precondition_group() {
	next_token();
	auto e = parse_precondition(LOWEST);
	if (!expect_peek_token(Token::TOKEN_RPAREN)) {
		return nullptr;
	}
	return e;
}