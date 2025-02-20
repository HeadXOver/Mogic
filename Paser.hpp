#pragma once

#include"Lexer.hpp"
#include"ast_header.hpp"

using namespace mgc::lexer;
using namespace mgc::ast;

namespace mgc {
	namespace paser {
		class Paser {
		public:
			enum Precedence {
				LOWEST = 0,
				SOIT,			//=
				BE,				//be
				NAME,			//name
				EQUAL,			//==,xor
				COMPARISON,		//<,>
				IFTHEN,			//if then
				ORAND,			//||,&&
				NOT,			//!,not
				ETRE,			//be?
				SUM,			//+,-
				PRODUCT,		//*,/
				STRUCT,			//construct
			};

			Paser();
			Paser(const std::shared_ptr<Lexer>& lexer);
			~Paser();

			//前缀表达式构建函数原型的定义
			typedef std::shared_ptr<Expression>(Paser::* prefix_parse_fn)(void);

			//中缀表达式构建函数原型的定义
			typedef std::shared_ptr<Expression>(Paser::* infix_parse_fn)(const std::shared_ptr<Expression>&);

			//前缀前提式构建函数原型的定义
			typedef std::shared_ptr<Precondition>(Paser::* precondition_prefix_parse_fn)(void);

			//中缀前提式构建函数原型的定义
			typedef std::shared_ptr<Precondition>(Paser::* precondition_infix_parse_fn)(const std::shared_ptr<Precondition>&);

			void next_token();
			bool curr_token_is(Token::Type type);
			bool peek_token_is(Token::Type type);
			bool expect_peek_token(Token::Type type);

			void peek_error(Token::Type type);
			std::list<string>& errors();

			int curr_token_precedence();
			int peek_token_precedence();

			void no_prefix_parse_fn_error(Token::Type type);
			void no_precondition_prefix_parse_fn_error(Token::Type type);

			std::shared_ptr<Expression> parse_expression(int precedence);
			std::shared_ptr<Program> parse_program();
			std::shared_ptr<Block> parse_block();
			std::shared_ptr<Statement> parse_statement();
			std::shared_ptr<ExpressionStatement> parse_expression_statement();
			std::shared_ptr<Precondition> parse_precondition(int precedence);

			//prefix
			std::shared_ptr<Expression> parse_integer();
			std::shared_ptr<Expression> parse_boolean();
			std::shared_ptr<Expression> parse_string();
			std::shared_ptr<Expression> parse_identifier();
			std::shared_ptr<Expression> parse_group();
			std::shared_ptr<Expression> parse_prefix();

			//infix
			std::shared_ptr<Expression> parse_infix(const std::shared_ptr<Expression>& left);

			//precondition prefix
			std::shared_ptr<Precondition> parse_precondition_boolean();
			std::shared_ptr<Precondition> parse_precondition_group();
			std::shared_ptr<Precondition> parse_precondition_prefix();
			std::shared_ptr<Precondition> parse_precondition_identifier();

			//precondition infix
			std::shared_ptr<Precondition> parse_precondition_infix(const std::shared_ptr<Precondition>& left);

		private:
			std::shared_ptr<Lexer> m_lexer;

			Token m_curr;
			Token m_peek;

			std::list<string> m_errors;

			static std::map<Token::Type, int> m_precedences;
			static std::map<Token::Type, prefix_parse_fn> m_prefix_parse_fns;
			static std::map<Token::Type, infix_parse_fn> m_infix_parse_fns;
			static std::map<Token::Type, precondition_prefix_parse_fn> m_precondition_prefix_parse_fns;
			static std::map<Token::Type, precondition_infix_parse_fn> m_precondition_infix_parse_fns;
		};
	}
}