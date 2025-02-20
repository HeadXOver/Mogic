#include "Lexer.hpp"

using namespace mgc::lexer;

Lexer::Lexer(const string & file) {
	m_file = file;
	m_ch = 0;
	m_pos = 0;
	m_next_pos = 0;
	m_line = 1;
	m_column = 1;

	ifstream ifs(file);
	if (!ifs.good()) {
		std::cout<<"Error:\n Lexer.cpp\n Lexer\n File not found\n"<<file<<endl;
		return;
	}
	
	ostringstream oss;
	oss<<ifs.rdbuf();
    m_input = oss.str();
}

Lexer::Lexer(const string text, size_t s) {
	m_file = "repling...";
	m_ch = 0;
	m_pos = 0;
	m_next_pos = 0;
	m_line = 1;
	m_column = 1;

	m_input = text;
}

Lexer::~Lexer() {}
Lexer::Lexer() {
	m_file = "";
	m_ch = 0;
	m_pos = 0;
	m_next_pos = 0;
	m_line = 1;
	m_column = 1;
}

void Lexer::read_char() {
	if (m_next_pos >= m_input.length()) {
		m_ch = 0;
	}
	else {
		m_ch = m_input[m_next_pos];
	}
	m_pos = m_next_pos;
	m_next_pos++;
}

char Lexer::peek_char() {
	if (m_next_pos >= m_input.length()) {
        return 0;
	}
	else {
        return m_input[m_next_pos];
	}
}

void Lexer::skip_white_space() {
	while (m_ch == ' ' || m_ch == '\t' || m_ch == '\n' || m_ch == '\r') {
		if (m_ch == '\n') {
            m_line++;
            m_column = 1;
		}
		else if (m_ch == ' ') {
            m_column++;
		}
		else if (m_ch == '\t') {
			m_column += 4;
		}
		read_char();
	}
}

Token Lexer::next_token() {
	read_char();
	skip_white_space();
	switch (m_ch) {
		case '(': 
			return new_token(Token::TOKEN_LPAREN, "(");
		case ')':
            return new_token(Token::TOKEN_RPAREN, ")");
        case ',':
            return new_token(Token::TOKEN_COMMA, ",");
        case '.':
			return new_token(Token::TOKEN_DOT, ".");
		case '^':
            return new_token(Token::TOKEN_EXP, "^");
        case '{':
            return new_token(Token::TOKEN_LBRACKET, "{");
        case '}':
            return new_token(Token::TOKEN_RBRACKET, "}");
        case ';':
            return new_token(Token::TOKEN_SEMICOLON, ";");
		case 0:
            return new_token(Token::TOKEN_EOF, "EOF");
		case '?':
            return new_token(Token::TOKEN_QUESTION, "?");
        case ':':
			return new_token(Token::TOKEN_COLON, ":");
		case '!':
            if (peek_char() == '=') {
                read_char();
                return new_token(Token::TOKEN_NOT_EQUAL, "!=");
            }
            return new_token(Token::TOKEN_EXCLAMATION, "!");
		case '+':
            return new_token(Token::TOKEN_PLUS, "+");
		case '-':
			if (peek_char() == '>') {
				read_char();
				return new_token(Token::TOKEN_IFTHEN, "->");
			}
            return new_token(Token::TOKEN_MINUS, "-");
        case '*':
            return new_token(Token::TOKEN_MULTIPLY, "*");
        case '/':
			if (peek_char() == '/') {
				read_char();
				while (m_ch != '\n' && m_ch != 0) {
					read_char();
				}
				return next_token();
			}
			else if (peek_char() == '*') {
				read_char();
				while (!(m_ch == '*' && peek_char() == '/')) {
					read_char();
				}
				read_char();
				return next_token();
			}
            return new_token(Token::TOKEN_DIVIDE, "/");
		case'<':
            if (peek_char() == '=') {
                read_char();
                return new_token(Token::TOKEN_LESS_EQUAL, "<=");
            }
            return new_token(Token::TOKEN_LESS, "<");
        case'>':
            if (peek_char() == '=') {
                read_char();
                return new_token(Token::TOKEN_GREATER_EQUAL, ">=");
            }
			else if (peek_char() == '>') {
				read_char();
				return new_token(Token::TOKEN_OUTPUT, ">>");
			}
            return new_token(Token::TOKEN_GREATER, ">");
        case '=':
            if (peek_char() == '=') {
                read_char();
                return new_token(Token::TOKEN_EQUAL, "==");

            }
            return new_token(Token::TOKEN_SOIT, "=");
		case '\'': {
			read_char();
            string literal = read_string();
            return new_token(Token::TOKEN_STRING, literal);
		}

		default: {
			if (is_digit(m_ch)) {
				string integer = read_number();
				unread_char();
				return new_token(Token::TOKEN_NUMBER, integer);
			}

			else if (is_letter(m_ch) || m_ch == '_') {
				string identifier = read_identifier();
                unread_char();

				Token::Type type;
				auto it = m_keywords.find(identifier);

				if (it != m_keywords.end()) {
					type = it->second;
					return new_token(type, identifier);
				}

				else {
					return new_token(Token::TOKEN_IDENTIFIER, identifier);
				}
			}

			else {
				string literal;
				literal += m_ch;
				return new_token(Token::TOKEN_ILLEGAL, literal);
			}
		}
	}
}

void Lexer::unread_char() {
	m_next_pos = m_pos;
	m_pos--;
}

bool Lexer::is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool Lexer::is_letter(char ch){
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

string Lexer::read_number() {
	int pos = m_pos;
	while (is_digit(m_ch)) {
		read_char();
	}
	return m_input.substr(pos, m_next_pos - pos - 1);
}

string Lexer::read_identifier() {
    int pos = m_pos;
    while (is_letter(m_ch) || m_ch == '_' || is_digit(m_ch)) {
		read_char();
    }
    return m_input.substr(pos, m_next_pos - pos - 1);
}

string Lexer::read_string() {
	int pos = m_pos;
	while (m_ch != '\'') {
		read_char();
	}
	return m_input.substr(pos, m_next_pos - pos - 1);
}

Token Lexer::new_token(Token::Type type, const string & literal) {
	Token token(type, literal, m_line, m_column);
	return token;
}

bool Lexer::is_unknownchar(char ch) {
	return !is_letter(ch) && !is_digit(ch) && ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\'' && ch != '\"' && ch != 0;
}