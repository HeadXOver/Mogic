#include"mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_infix(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	switch (left->type()) {
		case mgc::objj::Object::OBJ_INTEGER:
		case mgc::objj::Object::OBJ_DECIMAL:{
			if (right->type() == mgc::objj::Object::OBJ_INTEGER ||
				right->type() == mgc::objj::Object::OBJ_IDENTIFIER ||
				right->type() == mgc::objj::Object::OBJ_DECIMAL) {
				return eval_number_infix_expression(op, left, right);
			}
			break;
		}
		case mgc::objj::Object::OBJ_BOOLEAN: {
			if (right->type() == mgc::objj::Object::OBJ_BOOLEAN || right->type() == mgc::objj::Object::OBJ_IDENTIFIER) {
				return eval_boolean_infix_expression(op, left, right);
			}
			break;
		}
		case mgc::objj::Object::OBJ_STRING: {
			if (right->type() == mgc::objj::Object::OBJ_STRING) {
				return eval_string_infix_expression(op, left, right);
			}
			break;
		}
		case mgc::objj::Object::OBJ_IDENTIFIER: {
			if (op == "name" && right->type() == mgc::objj::Object::OBJ_STRING) {
				return eval_name_infix_expression(op, left, right);
			}
			if (op == "be" && right->type() == mgc::objj::Object::OBJ_IDENTIFIER) {
				return eval_know_be_infix_expression(op, left, right);
			}
			if (op == "etre" && right->type() == mgc::objj::Object::OBJ_IDENTIFIER) {
				return eval_etre_infix_expression(op, left, right);
			}
			if (op == "=") {
				return eval_assign_expression(op, left, right);
			}
			if ((op == "+" || op == "-" || op == "/" || op == "*" || op == "<" || op == "<=" || op == ">" || op == ">=") &&
				(right->type() == mgc::objj::Object::OBJ_INTEGER || right->type() == mgc::objj::Object::OBJ_IDENTIFIER)) {
				return eval_number_infix_expression(op, left, right);
			}
			if ((op == "==" || op == "!=" || op == "or" || op == "and" || op == "xor") &&
				(right->type() == mgc::objj::Object::OBJ_INTEGER)) {
				return eval_number_infix_expression(op, left, right);
			}
			if ((op == "==" || op == "!=" || op == "or" || op == "and" || op == "xor" || op == "->") &&
				(right->type() == mgc::objj::Object::OBJ_BOOLEAN)) {
				return eval_boolean_infix_expression(op, left, right);
			}
		}
		case mgc::objj::Object::OBJ_LOGICNODE: {
			if (op == ":") {
				auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(left);
				if (l != nullptr) {
					auto r = std::dynamic_pointer_cast<objj::ObjLogicNode>(right);
					if (r != nullptr) {
						if (l->m_noeud->get_propo() == "") {
							l->m_noeud->connect_to(r->m_noeud.get());
							l->m_noeud->set_propo(r->m_noeud->get_propo()+"("+ r->m_noeud->get_objstr()+")");
							return new_string("predi connected");
						}
						else {
							return new_error("error\n eval_infix.cpp\n eval_infix\n propo already named");
						}
					}
				}
				return new_error("error\n eval_infix.cpp\n eval_assign_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
			}
		}
		default:break;
	}
	return new_error("error\n eval_infix.cpp\n eval_infix\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_pre_infix(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	if (left->type() == mgc::objj::Object::OBJ_LOGICNODE && right->type() == mgc::objj::Object::OBJ_LOGICNODE) {
		auto l = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(left);
		auto r = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(right);
		if (op == "or") {
			return new_logic_noeud(new LogicNode(l->m_noeud, "or", r->m_noeud));
		}
		if (op == "and") {
			return new_logic_noeud(new LogicNode(l->m_noeud, "and", r->m_noeud));
		}
		if (op == "==") {
			return new_logic_noeud(new LogicNode(l->m_noeud, "equal", r->m_noeud));
		}
		if (op == "->") {
			return new_logic_noeud(new LogicNode(l->m_noeud, "ifthen", r->m_noeud));
		}
	}
	return new_error("error\n eval_infix.cpp\n eval_infix\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_number_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto l = std::dynamic_pointer_cast<objj::Integer>(left);
	if (l == nullptr) {
		auto l_id = std::dynamic_pointer_cast<objj::Identifier>(left);
		if(l_id != nullptr) {
			l = std::dynamic_pointer_cast<objj::Integer>(l_id->m_value);
		}
	}
	auto r = std::dynamic_pointer_cast<objj::Integer>(right);
	if (r == nullptr) {
		auto r_id = std::dynamic_pointer_cast<objj::Identifier>(right);
		if (r_id != nullptr) {
			r = std::dynamic_pointer_cast<objj::Integer>(r_id->m_value);
		}
	}
	if (l != nullptr && r != nullptr) {
		if (op == "+") {
			return new_integer(l->m_value + r->m_value);
		}
		else if (op == "-") {
			return new_integer(l->m_value - r->m_value);
		}
		else if (op == "*") {
			return new_integer(l->m_value * r->m_value);
		}
		else if (op == "/") {
			return new_integer(l->m_value / r->m_value);
		}
		else if (op == "<") {
			return new_boolean(l->m_value < r->m_value);
		}
		else if (op == ">") {
			return new_boolean(l->m_value > r->m_value);
		}
		else if (op == "<=") {
			return new_boolean(l->m_value <= r->m_value);
		}
		else if (op == ">=") {
			return new_boolean(l->m_value >= r->m_value);
		}
		else if (op == "==") {
			return new_boolean(l->m_value == r->m_value);
		}
		else if (op == "!=") {
			return new_boolean(l->m_value != r->m_value);
		}
		else if (op == "^") {
			return new_decimal(l->m_value, (int)(r->m_value));
		}
	}
	else {
		std::shared_ptr<objj::Decimal> l_de = nullptr;
		std::shared_ptr<objj::Decimal> r_de = nullptr;
		if (l != nullptr) {
			l_de = std::dynamic_pointer_cast<objj::Decimal>(new_decimal(l->m_value, 0));
		}
		else {
			l_de = std::dynamic_pointer_cast<objj::Decimal>(left);
			if (l_de == nullptr) {
				auto l_de_id = std::dynamic_pointer_cast<objj::Identifier>(left);
				l_de = std::dynamic_pointer_cast<objj::Decimal>(l_de_id->m_value);
			}
		}
		if (r != nullptr) {
			r_de = std::dynamic_pointer_cast<objj::Decimal>(new_decimal(r->m_value, 0));
		}
		else {
			r_de = std::dynamic_pointer_cast<objj::Decimal>(right);
			if (r_de == nullptr) {
				auto r_de_id = std::dynamic_pointer_cast<objj::Identifier>(right);
				r_de = std::dynamic_pointer_cast<objj::Decimal>(r_de_id->m_value);
			}
		}
		if (l_de != nullptr && r_de != nullptr) {
			if (op == "+") {
				return decimal_add(l_de, r_de);
			}
			else if (op == "-") {
				return decimal_sub(l_de, r_de);
			}
			else if (op == "*") {
				return decimal_mul(l_de, r_de);
			}
			else if (op == "/") {
				return decimal_div(l_de, r_de);
			}
			else if (op == "<") {
				return new_boolean(l->m_value < r->m_value);
			}
			else if (op == ">") {
				return new_boolean(l->m_value > r->m_value);
			}
			else if (op == "<=") {
				return new_boolean(l->m_value <= r->m_value);
			}
			else if (op == ">=") {
				return new_boolean(l->m_value >= r->m_value);
			}
			else if (op == "==") {
				return new_boolean((l_de->m_integer == r_de->m_integer) && (l_de->m_decimal == r_de->m_decimal));
			}
			else if (op == "!=") {
				return new_boolean(l->m_value != r->m_value);
			}
		}
	}
	return new_error("error\n eval_infix.cpp\n eval_integer_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_boolean_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto l = std::dynamic_pointer_cast<objj::Bool>(left);
	if (l == nullptr) {
		auto l_id = std::dynamic_pointer_cast<objj::Identifier>(left);
		l = std::dynamic_pointer_cast<objj::Bool>(l_id->m_value);
		if (l == nullptr) {
			auto l_id_ln = std::dynamic_pointer_cast<objj::ObjLogicNode>(l_id->m_value);
			if (l_id_ln != nullptr) {
				l = std::dynamic_pointer_cast<objj::Bool>(new_boolean(l_id_ln->m_noeud->get_value()));
			}
		}
	}
	auto r = std::dynamic_pointer_cast<objj::Bool>(right);
	if (r == nullptr) {
		auto r_id = std::dynamic_pointer_cast<objj::Identifier>(right);
		r = std::dynamic_pointer_cast<objj::Bool>(r_id->m_value);
		if (r == nullptr) {
			auto r_id_ln = std::dynamic_pointer_cast<objj::ObjLogicNode>(r_id->m_value);
			if (r_id_ln != nullptr) {
				r = std::dynamic_pointer_cast<objj::Bool>(new_boolean(r_id_ln->m_noeud->get_value()));
			}
		}
	}
	if (op == "or") {
		return new_boolean(l->m_value || r->m_value);
	}
	else if (op == "and") {
		return new_boolean(l->m_value && r->m_value);
	}
	else if (op == "xor") {
		return new_boolean(l->m_value ^ r->m_value);
	}
	else if (op == "->") {
		if (l->m_value && !(r->m_value)) {
			return new_boolean(false);
		}
		return new_boolean(true);
	}
	else if (op == "==") {
		return new_boolean(l->m_value == r->m_value);
	}
	else if (op == "!=") {
		return new_boolean(l->m_value != r->m_value);
	}
	cout << "error:\n eval_infix.cpp\n eval_boolean_infix_expression\n unkown operator:"+op << endl;
	return new_error("error\n eval_infix.cpp\n eval_boolean_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_string_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto l = std::dynamic_pointer_cast<objj::Mstring>(left);
	auto r = std::dynamic_pointer_cast<objj::Mstring>(right);
	if (op == "+") {
		return new_string(l->m_string + r->m_string);
	}
	
	return new_error("error\n eval_infix.cpp\n eval_string_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_name_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto it_l = std::dynamic_pointer_cast<objj::Identifier>(left);
	auto it_obj = find_id_ptr(it_l->id_name(), IdType::ID_OBJ);
	if (it_obj != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_obj);
		auto r = std::dynamic_pointer_cast<objj::Mstring>(right);
		l->m_noeud->set_propo(r->m_string);
		return new_identifier(it_l->id_name(), l);
	}

	auto it_pro = find_id_ptr(it_l->id_name(), IdType::ID_PROPO);
	if (it_pro != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_pro);
		auto r = std::dynamic_pointer_cast<objj::Mstring>(right);
		l->m_noeud->set_propo(r->m_string);
		return new_identifier(it_l->id_name(), l);
	}

	auto it_predi = find_id_ptr(it_l->id_name(), IdType::ID_OBJPREDI);
	if (it_predi != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_predi);
		auto r = std::dynamic_pointer_cast<objj::Mstring>(right);
		l->m_noeud->set_propo(r->m_string);
		return new_identifier(it_l->id_name(), l);
	}
	
	return new_error("error\n eval_infix.cpp\n eval_name_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_know_be_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto it_left = std::dynamic_pointer_cast<objj::Identifier>(left);
	auto it_right = std::dynamic_pointer_cast<objj::Identifier>(right);
	auto it_l = find_id_ptr(it_left->id_name(), IdType::ID_OBJ);
	if (it_l != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_l);
		auto it_r = find_id_ptr(it_right->id_name(), IdType::ID_OBJ);
		if (it_r != nullptr) {
			auto r = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_r);
			l->m_noeud->connect_to(r->m_noeud.get());
			return new_string("know:" +it_left->id_name() + " be " + it_right->id_name() + " : " + l->m_noeud->get_propo() + " be " + r->m_noeud->get_propo());
		}
	}
	
	return new_error("error\n eval_infix.cpp\n eval_know_be_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_etre_infix_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto it_left = std::dynamic_pointer_cast<objj::Identifier>(left);
	auto it_right = std::dynamic_pointer_cast<objj::Identifier>(right);
	auto it_l = find_id_ptr(it_left->id_name(), IdType::ID_OBJ);
	if (it_l != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_l);
		auto it_r = find_id_ptr(it_right->id_name(), IdType::ID_OBJ);
		if (it_r != nullptr) {
			auto r = std::dynamic_pointer_cast<objj::ObjLogicNode>(it_r);
			bool f_b = l->m_noeud->find_connect(r->m_noeud.get());
			return new_boolean(f_b);
		}
	}

	return new_error("error\n eval_infix.cpp\n eval_etre_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_assign_expression(const string& op, const std::shared_ptr<mgc::objj::Object>& left, const std::shared_ptr<mgc::objj::Object>& right) {
	auto it_left = std::dynamic_pointer_cast<objj::Identifier>(left);
	auto it_l = find_id_ptr(it_left->id_name(), IdType::ID_INT);
	if (it_l != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::Integer>(it_l);
		auto r = std::dynamic_pointer_cast<objj::Integer>(right);
		if (r != nullptr) {
			l->m_value = r->m_value;
			return new_integer(l->m_value);
		}
		auto r_id = std::dynamic_pointer_cast<objj::Identifier>(right);
		if (r_id != nullptr) {
			auto r_int = std::dynamic_pointer_cast<objj::Integer>(r_id->m_value);
			if (r_int != nullptr) {
				l->m_value = r_int->m_value;
				return new_integer(l->m_value);
			}
		}
	}
	it_l = find_id_ptr(it_left->id_name(), IdType::ID_BOOL);
	if (it_l != nullptr) {
		auto l = std::dynamic_pointer_cast<objj::Bool>(it_l);
		auto r = std::dynamic_pointer_cast<objj::Bool>(right);
		if (r != nullptr) {
			l->m_value = r->m_value;
			return new_boolean(l->m_value);
		}
		auto r_id = std::dynamic_pointer_cast<objj::Identifier>(right);
		if (r_id != nullptr) {
			auto r_propo = std::dynamic_pointer_cast<objj::ObjLogicNode>(r_id->m_value);
			if (r_propo != nullptr) {
				l->m_value = r_propo->m_noeud->get_value();
				return new_boolean(l->m_value);
			}
			auto r_bool = std::dynamic_pointer_cast<objj::Bool>(r_id->m_value);
			if (r_bool != nullptr) {
				l->m_value = r_bool->m_value;
				return new_boolean(l->m_value);
			}
		}
	}

	return new_error("error\n eval_infix.cpp\n eval_know_be_infix_expression\n unkown operator:%s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}