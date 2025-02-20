#pragma once

#include<map>
#include<string>
#include<memory>
#include<stdarg.h>
#include<list>
#include "LogicNode.hpp"
#include "block.hpp"
#include<vector>
#include"obj_header.hpp"

using namespace std;

namespace mgc {
	namespace objj {
		class Object {
		public:
			enum Type {
				OBJ_ERROR = 0,
				OBJ_INTEGER,
				OBJ_DECIMAL,
                OBJ_STRING,
				OBJ_BOOLEAN,
				OBJ_RESULTLIST,
				OBJ_IDENTIFIER,
				OBJ_DECLARATION,
				OBJ_VOID,
				OBJ_NOEUD,
				OBJ_LOGICNODE,
				OBJ_FUNC,
			};

			Object() :m_type(OBJ_VOID) {}
			Object(Type type) : m_type(type) {}
			virtual ~Object() {}

			Type type() const { return m_type; }
			string name() const;
			virtual string str() const = 0;
			virtual bool set_value(short value) = 0;

			static std::shared_ptr<Object> new_error(const char* format, ...);
			static std::shared_ptr<Object> new_integer(int64_t value);
			static std::shared_ptr<Object> new_decimal(int64_t integer, int decimal);
			static std::shared_ptr<Object> new_result_list(std::list<std::shared_ptr<Object>>);
			static std::shared_ptr<Object> new_boolean(bool value);
			static std::shared_ptr<Object> new_predicate(LogicNode* value);
			static std::shared_ptr<Object> new_string(string value);
			static std::shared_ptr<Object> new_declaration(string value);
			static std::shared_ptr<Object> new_identifier(string value);
			static std::shared_ptr<Object> new_identifier(string value,std::shared_ptr<Object> value2);
			static std::shared_ptr<Object> new_noeud(LogicNode* value);
			static std::shared_ptr<Object> new_logic_node(LogicNode* value);
			static std::shared_ptr<Object> new_func(string name, std::vector<std::shared_ptr<mgc::objj::Object>> ids, std::shared_ptr <ast::Block> block);

		protected:
			Type m_type;
			static map<Type, string> m_names;
		};
	}
}