#include"mgcEvaluator.hpp"

#include<iostream>

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_prefix(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	if (op == "!" || op == "not") {
		return eval_boolean_prefix_expression(op,body);
	}
	else if (op == "-" || op == "+") {
		if (body->type() == mgc::objj::Object::OBJ_INTEGER) {
			return eval_integer_prefix_expression(op, body);
		}
		if (body->type() == mgc::objj::Object::OBJ_DECIMAL) {
			return eval_decimal_prefix_expression(op, body);
		}
		if (body->type() == mgc::objj::Object::OBJ_IDENTIFIER) {
			auto id = std::dynamic_pointer_cast<objj::Identifier>(body);
			auto it = find_id_ptr(id->id_name());
			if (it->type() == mgc::objj::Object::OBJ_INTEGER) {
				return eval_integer_prefix_expression(op, it);
			}
			if (it->type() == mgc::objj::Object::OBJ_DECIMAL) {
				return eval_decimal_prefix_expression(op, it);
			}
		}
	}
	else if (op == "obj") {
		return eval_obj_declaration(op, body);
	}
	else if (op == "propo") {
		return eval_propo_declaration(op, body);
	}
	else if (op == "predi") {
		return eval_predi_declaration(op, body);
	}
	else if (op == "int") {
		return eval_int_declaration(op, body);
	}
	else if (op == "bool") {
		return eval_bool_declaration(op, body);
	}

	return new_error("error:\n eval_prefix.cpp\n eval_prefix\n unkown operator:%s %s ", op.c_str(), body->name().c_str());
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_pre_prefix(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	if (op == "!" || op == "not") {
		if (body->type() == mgc::objj::Object::OBJ_LOGICNODE) {
			auto b = std::dynamic_pointer_cast<objj::ObjLogicNode>(body);
			return new_logic_noeud(new LogicNode("not", b->m_noeud));
		}
	}

	return new_error("error:\n eval_prefix.cpp\n eval_prefix\n unkown operator:%s %s ", op.c_str(), body->name().c_str());
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_integer_prefix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Integer>(body);
	if (b != nullptr) {
		if (op == "+") {
			return new_integer(b->m_value);
		}
		else if (op == "-") {
			return new_integer(0 - b->m_value);
		}
	}
	auto b2 = std::dynamic_pointer_cast<objj::Identifier>(body);
	if (b2 != nullptr) {
		auto b2_integer = std::dynamic_pointer_cast<objj::Integer>(b2->m_value);
		if (op == "+") {
			return new_integer(b2_integer->m_value);
		}
		else if (op == "-") {
			return new_integer(0 - b2_integer->m_value);
		}
	}
	return new_error("error:\n eval_prefix.cpp\n eval_integer_prefix_expression\n unkown operator:%s %s", op.c_str(), body->name().c_str());
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_decimal_prefix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Decimal>(body);
	if (b != nullptr) {
		if (op == "+") {
			return body;
		}
		else if (op == "-") {
			return new_decimal(-(b->m_integer),b->m_decimal);
		}
	}
	auto b2 = std::dynamic_pointer_cast<objj::Identifier>(body);
	if (b2 != nullptr) {
		auto b2_integer = std::dynamic_pointer_cast<objj::Integer>(b2->m_value);
		if (op == "+") {
			return new_integer(b2_integer->m_value);
		}
		else if (op == "-") {
			return new_integer(0 - b2_integer->m_value);
		}
	}
	return new_error("error:\n eval_prefix.cpp\n eval_integer_prefix_expression\n unkown operator:%s %s", op.c_str(), body->name().c_str());
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_boolean_prefix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Bool>(body);
	if (b != nullptr) {
		return new_boolean(!(b->m_value));
	}
	auto b2 = std::dynamic_pointer_cast<objj::Identifier>(body);
	if (b2 != nullptr) {
		auto b2_bool = std::dynamic_pointer_cast<objj::Bool>(b2->m_value);
		if (b2_bool != nullptr) {
			return new_boolean(!(b2_bool->m_value));
		}
		auto b_propo = std::dynamic_pointer_cast<objj::ObjLogicNode>(b2->m_value);
		if (b_propo != nullptr) {
			if (b_propo->m_noeud->get_value() == -1) {
				return new_integer(-1);
			}
			return new_boolean(!(b_propo->m_noeud->get_value()));
		}
	}
	return new_error("error:\n eval_prefix.cpp\n eval_boolean_prefix_expression\n unkown operator:%s %s", op.c_str(), body->name().c_str());
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_obj_declaration(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Identifier>(body);
	
	auto it_b = find_id_ptr(b->m_name);
	if (it_b != nullptr) {
		cout << "重复声明id: " << b->m_name << endl;
		return new_error("重复声明id: %s", b->m_name.c_str());
	}
	
	m_id_name.push_back(b->m_name);
	m_id_type.push_back(IdType::ID_OBJ);
	std::shared_ptr<mgc::objj::Object> new_n = new_noeud(new LogicNode(LogicNode::NodeType::OBJ, ""));
	m_id_value.push_back(new_n);
	//std::cout << "声明obj: " << b->m_name << std::endl;
	return new_identifier(b->m_name, new_n);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_propo_declaration(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Identifier>(body);

	auto it_b = find_id_ptr(b->m_name);
	if (it_b != nullptr) {
		cout << "重复声明id: " << b->m_name << endl;
		return new_error("重复声明id: %s", b->m_name.c_str());
	}

	m_id_name.push_back(b->m_name);
	m_id_type.push_back(IdType::ID_PROPO);
	std::shared_ptr<mgc::objj::Object> new_n = new_logic_noeud(new LogicNode(""));
	m_id_value.push_back(new_n);
	//std::cout << "声明propo: " << b->m_name << std::endl;
	return new_identifier(b->m_name, new_n);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_int_declaration(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Identifier>(body);

	auto it_b = find_id_ptr(b->m_name);
	if (it_b != nullptr) {
		cout << "重复声明id: " << b->m_name << endl;
		return new_error("重复声明id: %s", b->m_name.c_str());
	}

	m_id_name.push_back(b->m_name);
	m_id_type.push_back(IdType::ID_INT);
	std::shared_ptr<mgc::objj::Object> new_int = new_integer(0);
	m_id_value.push_back(new_int);
	//std::cout << "声明propo: " << b->m_name << std::endl;
	return new_identifier(b->m_name, new_int);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_bool_declaration(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Identifier>(body);

	auto it_b = find_id_ptr(b->m_name);
	if (it_b != nullptr) {
		cout << "重复声明id: " << b->m_name << endl;
		return new_error("重复声明id: %s", b->m_name.c_str());
	}

	m_id_name.push_back(b->m_name);
	m_id_type.push_back(IdType::ID_BOOL);
	std::shared_ptr<mgc::objj::Object> new_bool = new_boolean(false);
	m_id_value.push_back(new_bool);
	//std::cout << "声明propo: " << b->m_name << std::endl;
	return new_identifier(b->m_name, new_bool);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval_predi_declaration(const string& op, const std::shared_ptr<mgc::objj::Object>& body) {
	auto b = std::dynamic_pointer_cast<objj::Identifier>(body);

	auto it_b = find_id_ptr(b->m_name);
	if (it_b != nullptr) {
		cout << "重复声明id: " << b->m_name << endl;
		return new_error("重复声明id: %s", b->m_name.c_str());
	}

	m_id_name.push_back(b->m_name);
	m_id_type.push_back(IdType::ID_OBJPREDI);
	std::shared_ptr<mgc::objj::Object> new_predi = new_predicate(new LogicNode(LogicNode::NodeType::OBJPREDI, ""));
	m_id_value.push_back(new_predi);
	//std::cout << "声明propo: " << b->m_name << std::endl;
	return new_identifier(b->m_name, new_predi);
}