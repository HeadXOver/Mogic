#include"obj_header.hpp"

using namespace mgc::objj;

map<mgc::objj::Object::Type, string> mgc::objj::Object::m_names = {
	{OBJ_ERROR,			"Error"},
	{OBJ_INTEGER,		"Integer" },
	{OBJ_DECIMAL,		"Decimal" },
	{OBJ_RESULTLIST,	"ResultList" },
	{OBJ_BOOLEAN,		"Boolean" },
	{OBJ_IDENTIFIER,	"Identifier" },
    {OBJ_STRING,		"String" },
    {OBJ_DECLARATION,	"Declaration" },
	{OBJ_FUNC,			"Func" },
	{OBJ_VOID,			"Void" },
	{OBJ_NOEUD,			"Noeud" },
	{OBJ_LOGICNODE,		"LogicNode" },
};

string mgc::objj::Object::name() const {
	auto it = m_names.find(type());
	if (it != m_names.end()) {
		return it->second;
    }
    return "Unknown obj name";
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_error(const char* format, ...) {
	char buf[1024] = { 0 };
	va_list arg_ptr;
	va_start(arg_ptr,format);
	vsprintf_s(buf, format, arg_ptr);
	va_end(arg_ptr);
    std::shared_ptr<Error> obj(new Error(buf));
	obj->m_message = buf;
	return obj;
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_integer(int64_t value) {
	return (std::shared_ptr<objj::Object>)(new Integer(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_decimal(int64_t integer, int decimal) {
	return (std::shared_ptr<objj::Object>)(new Decimal(integer, decimal));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_string(string value) {
	return (std::shared_ptr<objj::Object>)(new Mstring(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_boolean(bool value) {
	return (std::shared_ptr<objj::Object>)(new Bool(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_declaration(string value) {
	return (std::shared_ptr<objj::Object>)(new Declaration(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_result_list(std::list<std::shared_ptr<mgc::objj::Object>> value) {
	return (std::shared_ptr<objj::Object>)(new ResultList(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_identifier(string value) {
	return (std::shared_ptr<objj::Object>)(new Identifier(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_identifier(string value, std::shared_ptr< mgc::objj::Object> value2) {
	return (std::shared_ptr<objj::Object>)(new Identifier(value, value2));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_func(string name, std::vector<std::shared_ptr<mgc::objj::Object>> ids, std::shared_ptr<ast::Block> block) {
	std::vector<std::shared_ptr<mgc::objj::Identifier>> obj_ids;
	for (auto& id : ids) {
		obj_ids.push_back(std::dynamic_pointer_cast<mgc::objj::Identifier>(id));
	}
	return (std::shared_ptr<objj::Object>)(new Func(name, obj_ids, block));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_noeud(LogicNode* value) {
	return (std::shared_ptr<objj::Object>)(new ObjLogicNode(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_logic_node(LogicNode* value) {
	return (std::shared_ptr<objj::Object>)(new ObjLogicNode(value));
}

std::shared_ptr<mgc::objj::Object> mgc::objj::Object::new_predicate(LogicNode* value) {
	return (std::shared_ptr<objj::Object>)(new ObjLogicNode(value));
}