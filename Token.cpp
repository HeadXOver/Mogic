#include "Token.hpp"

using namespace mgc::token;

Token::Token() : m_column(0), m_line(0), m_type(Token::Type::TOKEN_UNKNOWN) {}

Token::Token(Type type, const string& literal, int line, int column) {
	Token::m_type = type;
    Token::m_literal = literal;
    Token::m_line = line;
    Token::m_column = column;
}

Token::Type Token::type() const {
    return m_type;
}

string Token::name() const {
    auto it = Token::m_typeName.find(m_type);
    if (it != Token::m_typeName.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

Token::~Token() {}

string Token::literal() const{
    return m_literal;
}

int Token::line() const {
    return m_line;
}

int Token::column() const {
    return m_column;
}

void Token::show() const {
    printf("type=%d name=%s literal=%s\n", m_type, name().c_str(), m_literal.c_str());
}

