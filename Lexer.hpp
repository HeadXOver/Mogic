#pragma once

#include <string>
#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;
using namespace mgc::token;

namespace mgc {
	namespace lexer {
		class Lexer {
		public:
			Lexer();
			Lexer(const string& file);
			Lexer(const string text, size_t s);
			~Lexer();

			Token next_token();

			map<string, Token::Type> m_keywords = {
				{"obj",			Token::TOKEN_OBJ},
				{"nat",			Token::TOKEN_NAT},
				{"know",		Token::TOKEN_KNOW},
				{"be",			Token::TOKEN_BE},
				{"name",		Token::TOKEN_NAME},
				{"or",			Token::TOKEN_OR},
				{"and",			Token::TOKEN_AND},
				{"True",		Token::TOKEN_TRUE},
				{"False",		Token::TOKEN_FALSE},
				{"not",			Token::TOKEN_NOT},
				{"etre",		Token::TOKEN_ETRE},
				{"xor",			Token::TOKEN_XOR},
				{"propo",		Token::TOKEN_PROPO},
				{"predi",		Token::TOKEN_PREDI},
				{"infer",		Token::TOKEN_INFER},
				{"tnum",		Token::TOKEN_TRUENUM},
				{"int",			Token::TOKEN_INT},
				{"bool",		Token::TOKEN_BOOL},
				{"func",		Token::TOKEN_FUNC},
				{"if",			Token::TOKEN_IF},
				{"else",		Token::TOKEN_ELSE},
				{"while",		Token::TOKEN_WHILE},
				{"for",			Token::TOKEN_FOR},
			};

		private:
			Token new_token(Token::Type type, const string& literal);
			void read_char();
			char peek_char();
			void unread_char();
			bool is_digit(char ch);
			bool is_letter(char ch);
			bool is_unknownchar(char ch);

			string read_identifier();
			string read_number();
            string read_string();

			void skip_white_space();

			string m_file;    //�����ļ�·��
			string m_input;   //��ȡ�����ַ�������
			int    m_pos;     //��ǰλ��
			int    m_next_pos;//��һ��λ��
			char   m_ch;      //��ǰλ�õ��ַ�
			int    m_line;    //��ǰ����
			int    m_column;  //��ǰ����
		};
	}
}