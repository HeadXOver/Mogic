#pragma once

#include"ast_header.hpp"
#include"obj_header.hpp"
#include<vector>
#include<cmath>
#include<bitset>

using namespace mgc::ast;
using namespace mgc::objj;

namespace mgc {
	namespace eval {
		class Evaluator {
		public:
			Evaluator() {}
			~Evaluator() {}

			enum IdType {
				ID_NDEFINED,
				ID_OBJ,
				ID_PROPO,
				ID_INT,
				ID_BOOL,
				ID_STR,
				ID_FUNC,
				ID_PREDI,
				ID_OBJPREDI,
			};

			std::list<string> m_id_name;
			std::list<IdType> m_id_type;
			std::list<std::shared_ptr<objj::Object>> m_id_value;

			std::list<std::shared_ptr<objj::ObjLogicNode>> m_logic_node;
			std::list<std::shared_ptr<objj::ObjLogicNode>> m_predi_node;

			std::shared_ptr<objj::Object> find_id_ptr(string name, Evaluator::IdType type);
			std::shared_ptr<objj::Object> find_id_ptr(string name);
			IdType find_id_type(string name);

			bool is_error(const std::shared_ptr<objj::Object>& obj);

			int get_bit(int64_t value);

			std::shared_ptr<objj::Object> decimal_add(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right);
			std::shared_ptr<objj::Object> decimal_sub(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right);
			std::shared_ptr<objj::Object> decimal_mul(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right);
			std::shared_ptr<objj::Object> decimal_div(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right);

			std::shared_ptr<objj::Object> new_error(const char* format, ...);
			std::shared_ptr<objj::Object> new_integer(int64_t value);
			std::shared_ptr<objj::Object> new_decimal(int64_t integer, int decimal);
			std::shared_ptr<objj::Object> new_identifier(string name);
			std::shared_ptr<objj::Object> new_identifier(string name, std::shared_ptr<objj::Object> value);
			std::shared_ptr<objj::Object> new_boolean(bool value);
			std::shared_ptr<objj::Object> new_predicate(LogicNode* value);
			std::shared_ptr<objj::Object> new_string(string value);
			std::shared_ptr<objj::Object> new_declaration(string value);
			std::shared_ptr<objj::Object> new_result_list(std::list<std::shared_ptr<objj::Object>>);
			std::shared_ptr<objj::Object> new_noeud(LogicNode* value);
			std::shared_ptr<objj::Object> new_logic_noeud(LogicNode* value);
			std::shared_ptr<objj::Object> new_func(string name, std::list<std::shared_ptr<ast::Identifier>> ids,std::shared_ptr <ast::Block> block);

			std::shared_ptr<objj::Object> eval(const std::shared_ptr<ast::Node>& node);
			std::shared_ptr<objj::Object> eval_program(const std::list<std::shared_ptr<ast::Statement>>& stmts);
			std::shared_ptr<objj::Object> eval_integer(const std::shared_ptr<ast::Integer> & node);
			std::shared_ptr<objj::Object> eval_boolean(const std::shared_ptr<ast::Bool> & node);
			std::shared_ptr<objj::Object> eval_string(const std::shared_ptr<ast::Mstring>& node);
			std::shared_ptr<objj::Object> eval_identifier(const std::shared_ptr<ast::Identifier>& node);
			std::shared_ptr<objj::Object> eval_pre_identifier(const std::shared_ptr<ast::PreIdentifier>& node);
			std::shared_ptr<objj::Object> eval_declaration(const std::shared_ptr<ast::Declaration>& node);
			std::shared_ptr<objj::Object> eval_func_expression(const std::shared_ptr<ast::FuncExpression>& node);

			//infix
			std::shared_ptr<objj::Object> eval_infix(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_pre_infix(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_number_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_boolean_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_string_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_name_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_know_be_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_etre_infix_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);
			std::shared_ptr<objj::Object> eval_assign_expression(const string& op, const std::shared_ptr<objj::Object>& left, const std::shared_ptr<objj::Object>& right);

			//prefix
			std::shared_ptr<objj::Object> eval_prefix(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_pre_prefix(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_integer_prefix_expression(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_decimal_prefix_expression(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_boolean_prefix_expression(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_obj_declaration(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_propo_declaration(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_int_declaration(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_bool_declaration(const string& op, const std::shared_ptr<objj::Object>& body);
			std::shared_ptr<objj::Object> eval_predi_declaration(const string& op, const std::shared_ptr<objj::Object>& body);

		private:
			void eval_infer(std::list<std::shared_ptr<ast::Identifier>> members,int tnum);
			void unset_imagine(std::list<std::shared_ptr<ast::Identifier>> members);
			bool check_infer(std::list<std::shared_ptr<ast::Identifier>> members, unsigned int n);
		};
	}
}