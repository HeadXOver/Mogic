#include "Paser.hpp"

using namespace mgc::paser;

std::map<Token::Type, int> Paser::m_precedences = {
	{Token::TOKEN_PLUS,			SUM},
	{Token::TOKEN_MINUS,		SUM},
	{Token::TOKEN_MULTIPLY,		PRODUCT},
	{Token::TOKEN_DIVIDE,		PRODUCT},
	{Token::TOKEN_EXCLAMATION,	NOT},
	{Token::TOKEN_NOT,			NOT},
	{Token::TOKEN_EQUAL,		EQUAL},
	{Token::TOKEN_NOT_EQUAL,	EQUAL},
	{Token::TOKEN_XOR,			EQUAL},
	{Token::TOKEN_GREATER,		COMPARISON},
	{Token::TOKEN_LESS,			COMPARISON},
    {Token::TOKEN_GREATER_EQUAL,COMPARISON},
    {Token::TOKEN_LESS_EQUAL,	COMPARISON},
	{Token::TOKEN_IFTHEN,		IFTHEN},
	{Token::TOKEN_OR,			ORAND},
	{Token::TOKEN_AND,			ORAND},
	{Token::TOKEN_NAME,			NAME},
	{Token::TOKEN_BE,			BE},
	{Token::TOKEN_ETRE,			ETRE},
	{Token::TOKEN_SOIT,			SOIT},
	{Token::TOKEN_COLON,		SOIT},
	{Token::TOKEN_DOT,			STRUCT},
	{Token::TOKEN_EXP,			STRUCT},
};

std::map<Token::Type, Paser::prefix_parse_fn> Paser::m_prefix_parse_fns = {
	{Token::TOKEN_NUMBER,		&Paser::parse_integer},
	{Token::TOKEN_STRING,		&Paser::parse_string},
	{Token::TOKEN_LPAREN,		&Paser::parse_group},
	{Token::TOKEN_TRUE,			&Paser::parse_boolean},
	{Token::TOKEN_FALSE,		&Paser::parse_boolean},
	{Token::TOKEN_PLUS,			&Paser::parse_prefix},
	{Token::TOKEN_MINUS,		&Paser::parse_prefix},
	{Token::TOKEN_EXCLAMATION,	&Paser::parse_prefix},
	{Token::TOKEN_NOT,			&Paser::parse_prefix},
	{Token::TOKEN_OBJ,			&Paser::parse_prefix},
	{Token::TOKEN_PROPO,		&Paser::parse_prefix},
	{Token::TOKEN_PREDI,		&Paser::parse_prefix},
	{Token::TOKEN_INT,			&Paser::parse_prefix},
	{Token::TOKEN_BOOL,			&Paser::parse_prefix},
	{Token::TOKEN_IDENTIFIER,	&Paser::parse_identifier},
};
std::map<Token::Type, Paser::infix_parse_fn> Paser::m_infix_parse_fns = {
	{Token::TOKEN_PLUS,			&Paser::parse_infix},
	{Token::TOKEN_MINUS,		&Paser::parse_infix},
	{Token::TOKEN_MULTIPLY,		&Paser::parse_infix},
	{Token::TOKEN_DIVIDE,		&Paser::parse_infix},
	{Token::TOKEN_OR,			&Paser::parse_infix},
	{Token::TOKEN_AND,			&Paser::parse_infix},
	{Token::TOKEN_XOR,			&Paser::parse_infix},
	{Token::TOKEN_NAME,			&Paser::parse_infix},
	{Token::TOKEN_BE,			&Paser::parse_infix},
	{Token::TOKEN_ETRE,			&Paser::parse_infix},
	{Token::TOKEN_IFTHEN,		&Paser::parse_infix},
	{Token::TOKEN_GREATER,		&Paser::parse_infix},
	{Token::TOKEN_LESS,			&Paser::parse_infix},
	{Token::TOKEN_GREATER_EQUAL,&Paser::parse_infix},
	{Token::TOKEN_LESS_EQUAL,	&Paser::parse_infix},
	{Token::TOKEN_EQUAL,		&Paser::parse_infix},
	{Token::TOKEN_NOT_EQUAL,	&Paser::parse_infix},
	{Token::TOKEN_SOIT,			&Paser::parse_infix},
	{Token::TOKEN_COLON,		&Paser::parse_infix},
	{Token::TOKEN_DOT,			&Paser::parse_infix},
	{Token::TOKEN_EXP,			&Paser::parse_infix},
};

std::map<Token::Type, Paser::precondition_prefix_parse_fn> Paser::m_precondition_prefix_parse_fns = {
	{Token::TOKEN_LPAREN,		&Paser::parse_precondition_group},
	{Token::TOKEN_TRUE,			&Paser::parse_precondition_boolean},
	{Token::TOKEN_FALSE,		&Paser::parse_precondition_boolean},
	{Token::TOKEN_EXCLAMATION,	&Paser::parse_precondition_prefix},
	{Token::TOKEN_NOT,			&Paser::parse_precondition_prefix},
	{Token::TOKEN_IDENTIFIER,	&Paser::parse_precondition_identifier},
};
std::map<Token::Type, Paser::precondition_infix_parse_fn> Paser::m_precondition_infix_parse_fns = {
	{Token::TOKEN_OR,			&Paser::parse_precondition_infix},
	{Token::TOKEN_AND,			&Paser::parse_precondition_infix},
	{Token::TOKEN_XOR,			&Paser::parse_precondition_infix},
	{Token::TOKEN_IFTHEN,		&Paser::parse_precondition_infix},
	{Token::TOKEN_EQUAL,		&Paser::parse_precondition_infix},
	{Token::TOKEN_NOT_EQUAL,	&Paser::parse_precondition_infix},
};


Paser::Paser() {}

Paser::Paser(const std::shared_ptr<Lexer> & lexer) : m_lexer(lexer) {
	//初始化调用两次 
	next_token();
	next_token();
}

Paser::~Paser() {}

void Paser::next_token() {
	m_curr = m_peek;
	m_peek = m_lexer->next_token();
}

bool Paser::curr_token_is(Token::Type type) {
	return m_curr.type() == type;
}

bool Paser::peek_token_is(Token::Type type) {
	return m_peek.type() == type;
}

bool Paser::expect_peek_token(Token::Type type) {
	if (peek_token_is(type)) {
		next_token();
		return true;
	}
	else {
		peek_error(type);
		return false;
	}
}

void Paser::peek_error(Token::Type type) {
	std::ostringstream oss;
	oss << "error\n Paser.cpp\n peek_error\n expects(token) " << type << " but got " << m_peek.type();
	m_errors.push_back(oss.str());
}

int Paser::curr_token_precedence() {
	auto it = m_precedences.find(m_curr.type());
    if (it != m_precedences.end()) {
		return it->second;
    }
	return LOWEST;
}

int Paser::peek_token_precedence() {
	auto it = m_precedences.find(m_peek.type());
	if (it != m_precedences.end()) {
		return it->second;
	}
	return LOWEST;
}

void Paser::no_prefix_parse_fn_error(Token::Type type) {
	std::ostringstream oss;
	oss<<"error\n Pasr.cpp\n no_prefix_parse_fn_error\n no prefix parse function for " << type;
	m_errors.push_back(oss.str());
}

void Paser::no_precondition_prefix_parse_fn_error(Token::Type type) {
	std::ostringstream oss;
	oss << "error\n Pasr.cpp\n no_precondition_prefix_parse_fn_error\n no precondition prefix parse function for " << type;
	m_errors.push_back(oss.str());
}

std::list<string>& Paser::errors() {
	return m_errors;
}
