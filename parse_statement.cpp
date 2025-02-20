#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Statement> Paser::parse_statement() {
	if (m_curr.type() == Token::TOKEN_KNOW) {
		std::shared_ptr<Know> s(new Know());
		s->m_token = m_curr;
		next_token();
		s->m_precondition = parse_precondition(LOWEST);
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_OUTPUT) {
		std::shared_ptr<OutPut> s(new OutPut());
		s->m_token = m_curr;
		next_token();
		s->m_statement = parse_statement();
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_INFER) {
		std::shared_ptr<Infer> s(new Infer());
		s->m_token = m_curr;
		expect_peek_token(Token::TOKEN_LPAREN);
		do {
			if (m_peek.type() == Token::TOKEN_COMMA) {
				next_token();
			}
			expect_peek_token(Token::TOKEN_IDENTIFIER);
			std::shared_ptr<Identifier> id(new Identifier());
			id->m_token = m_curr;
			id->m_name = m_curr.literal().c_str();
			s->m_members.push_back(id);
		} while (m_peek.type() == Token::TOKEN_COMMA);
		expect_peek_token(Token::TOKEN_RPAREN);
		if (m_peek.type() == Token::TOKEN_TRUENUM) {
			next_token();
			expect_peek_token(Token::TOKEN_NUMBER);
			s->m_tnum = std::stol(m_curr.literal().c_str());
		}
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_LBRACKET) {
		return parse_block();
	}
	else if (m_curr.type() == Token::TOKEN_IF) {
		std::shared_ptr<ast::If> s(new If());
		s->m_token = m_curr;
		next_token();
		s->m_condition = parse_expression(LOWEST);
		next_token();
		s->m_block = parse_block();
		if (m_peek.type() == Token::TOKEN_ELSE) {
			next_token();
			next_token();
			s->m_else = parse_block();
		}
		else {
			s->m_else = nullptr;
		}
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_WHILE) {
		std::shared_ptr<ast::While> s(new While());
		s->m_token = m_curr;
		next_token();
		s->m_condition = parse_expression(LOWEST);
		next_token();
		s->m_block = parse_block();
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_FOR) {
		std::shared_ptr<ast::For> s(new For());
		s->m_token = m_curr;
		next_token();
		s->m_time = parse_expression(LOWEST);
		next_token();
		s->m_block = parse_block();
		return s;
	}
	else if (m_curr.type() == Token::TOKEN_FUNC) {
		std::shared_ptr<ast::Func> s(new Func());
		s->m_token = m_curr;
		expect_peek_token(Token::TOKEN_IDENTIFIER);
		s->m_func_name = m_curr.literal().c_str();
		expect_peek_token(Token::TOKEN_LPAREN);
		do {
			if (m_peek.type() == Token::TOKEN_COMMA) {
				next_token();
			}
			expect_peek_token(Token::TOKEN_IDENTIFIER);
			std::shared_ptr<Identifier> id(new Identifier());
			id->m_token = m_curr;
			id->m_name = m_curr.literal().c_str();
			s->m_ids.push_back(id);
		} while (m_peek.type() == Token::TOKEN_COMMA);
		expect_peek_token(Token::TOKEN_RPAREN);
		expect_peek_token(Token::TOKEN_LBRACKET);
		s->m_block = parse_block();
		return s;
	}
	return parse_expression_statement();
}

std::shared_ptr<ExpressionStatement> Paser::parse_expression_statement() {
	std::shared_ptr<ExpressionStatement> s(new ExpressionStatement());
	s->m_token = m_curr;
	s->m_expression = parse_expression(LOWEST);
	return s;
}