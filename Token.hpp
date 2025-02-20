#pragma once

#include <string>
#include<map>

using namespace std;

namespace mgc {
    namespace token {
        class Token {
        public:
            const enum Type {
                TOKEN_OBJ = 0,       //obj
                TOKEN_EOF,           //end
                TOKEN_NAT,           //nat
                TOKEN_KNOW,          //know
                TOKEN_BE,            //be
                TOKEN_QUESTION,      //?
                TOKEN_NAME,          //name
                TOKEN_QUOT,          //'
                TOKEN_LPAREN,        //(
                TOKEN_RPAREN,        //)
                TOKEN_SEMICOLON,     //;
                TOKEN_COLON,         //:
                TOKEN_NUMBER,        //number
                TOKEN_NOT,           //not
                TOKEN_ILLEGAL,       //illegal
                TOKEN_IDENTIFIER,    //identifier
                TOKEN_OR,            //or
                TOKEN_AND,           //and
                TOKEN_TRUE,          //True
                TOKEN_FALSE,         //False
                TOKEN_PLUS,          //+
                TOKEN_MINUS,         //-
                TOKEN_MULTIPLY,      //*
                TOKEN_DIVIDE,        ///
                TOKEN_UNKNOWN,       //unkown
                TOKEN_EXCLAMATION,   //!
                TOKEN_EQUAL,         //==
                TOKEN_SOIT,          //=
                TOKEN_NOT_EQUAL,     //!=
                TOKEN_LESS,          //<
                TOKEN_LESS_EQUAL,    //<=
                TOKEN_GREATER,       //>
                TOKEN_GREATER_EQUAL, //>=
                TOKEN_COMMA,         //,
                TOKEN_DOT,           //.
                TOKEN_STRING,        //string
                TOKEN_LBRACKET,      //{
                TOKEN_RBRACKET,      //}
                TOKEN_ETRE,          //be?
                TOKEN_XOR,           //xor
                TOKEN_IFTHEN,        //if then
                TOKEN_PROPO,         //propo
                TOKEN_PREDI,         //predi
                TOKEN_OUTPUT,        //>>
                TOKEN_INFER,         //infer,
                TOKEN_TRUENUM,       //true number
                TOKEN_INT,           //int
                TOKEN_BOOL,          //bool
                TOKEN_FUNC,          //func
                TOKEN_IF,            //if
                TOKEN_ELSE,          //else
                TOKEN_WHILE,         //while
                TOKEN_FOR,           //for
                TOKEN_EXP,           //^
            };

            Token();
            Token(Type type, const string& literal, int line, int column);
            ~Token();

            void show() const;

            Type type() const;
            string name() const;
            string literal() const;
            int line() const;
            int column() const;

        private:
            Type m_type;
            string m_literal;
            int m_line;
            int m_column;
            map<Type, string> m_typeName = {
                {TOKEN_OBJ,          "TOKEN_OBJ"},
                {TOKEN_EOF,          "TOKEN_EOF"},
                {TOKEN_NAT,          "TOKEN_NAT"},
                {TOKEN_KNOW,         "TOKEN_KNOW"},
                {TOKEN_BE,           "TOKEN_BE"},
                {TOKEN_QUESTION,     "TOKEN_QUESTION"},
                {TOKEN_NAME,         "TOKEN_NAME"},
                {TOKEN_QUOT,         "TOKEN_QUOT"},
                {TOKEN_LPAREN,       "TOKEN_LPAREN"},
                {TOKEN_RPAREN,       "TOKEN_RPAREN"},
                {TOKEN_SEMICOLON,    "TOKEN_SEMICOLON"},
                {TOKEN_COLON,        "TOKEN_COLON"},
                {TOKEN_NUMBER,       "TOKEN_NUMBER"},
                {TOKEN_EXCLAMATION,  "TOKEN_EXCLAMATION"},
                {TOKEN_EQUAL,        "TOKEN_EQUAL"},
                {TOKEN_NOT_EQUAL,    "TOKEN_NOT_EQUAL"},
                {TOKEN_LESS,         "TOKEN_LESS"},
                {TOKEN_LESS_EQUAL,   "TOKEN_LESS_EQUAL"},
                {TOKEN_GREATER,      "TOKEN_GREATER"},
                {TOKEN_GREATER_EQUAL,"TOKEN_GREATER_EQUAL"},
                {TOKEN_COMMA,        "TOKEN_COMMA"},
                {TOKEN_DOT,          "TOKEN_DOT"},
                {TOKEN_NOT,          "TOKEN_NOT"},
                {TOKEN_ILLEGAL,      "TOKEN_ILLEGAL"},
                {TOKEN_IDENTIFIER,   "TOKEN_IDENTIFIER"},
                {TOKEN_OR,           "TOKEN_OR"},
                {TOKEN_AND,          "TOKEN_AND"},
                {TOKEN_TRUE,         "TOKEN_TRUE"},
                {TOKEN_FALSE,        "TOKEN_FALSE"},
                {TOKEN_PLUS,         "TOKEN_PLUS"},
                {TOKEN_MINUS,        "TOKEN_MINUS"},
                {TOKEN_MULTIPLY,     "TOKEN_MULTIPLY"},
                {TOKEN_DIVIDE,       "TOKEN_DIVIDE"},
                {TOKEN_UNKNOWN,      "TOKEN_UNKNOWN"},
                {TOKEN_SOIT,         "TOKEN_SOIT"},
                {TOKEN_STRING,       "TOKEN_STRING"},
                {TOKEN_LBRACKET,     "TOKEN_LBRACKET"},
                {TOKEN_RBRACKET,     "TOKEN_RBRACKET"},
                {TOKEN_ETRE,         "TOKEN_ETRE"},
                {TOKEN_XOR,          "TOKEN_XOR"},
                {TOKEN_IFTHEN,       "TOKEN_IFTHEN"},
                {TOKEN_PROPO,        "TOKEN_PROPO"},
                {TOKEN_PREDI,        "TOKEN_PREDI"},
                {TOKEN_OUTPUT,       "TOKEN_OUTPUT"},
                {TOKEN_INFER,        "TOKEN_INFER"},
                {TOKEN_TRUENUM,      "TOKEN_TRUENUM"},
                {TOKEN_INT,          "TOKEN_INT"},
                {TOKEN_BOOL,         "TOKEN_BOOL"},
                {TOKEN_FUNC,         "TOKEN_FUNC"},
                {TOKEN_IF,           "TOKEN_IF"},
                {TOKEN_ELSE,         "TOKEN_ELSE"},
                {TOKEN_WHILE,        "TOKEN_WHILE"},
                {TOKEN_FOR,          "TOKEN_FOR"},
                {TOKEN_EXP,          "TOEKN_EXP"},
            };
        };
    }
}