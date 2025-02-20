#include"mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::find_id_ptr(string name, Evaluator::IdType type) {
	auto it_name = m_id_name.begin();
	auto it_type = m_id_type.begin();
	auto it_ptr = m_id_value.begin();
	for (; it_name != m_id_name.end(); it_name++, it_type++, it_ptr++) {
		if (*it_name == name && *it_type == type) {
			return *it_ptr;
		}
	}
	return nullptr;
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::find_id_ptr(string name) {
	auto it_name = m_id_name.begin();
	auto it_ptr = m_id_value.begin();
	for (; it_name != m_id_name.end(); it_name++,it_ptr++) {
		if (*it_name == name) {
			return *it_ptr;
		}
	}
	return nullptr;
}

mgc::eval::Evaluator::IdType mgc::eval::Evaluator::find_id_type(string name) {
	auto it_name = m_id_name.begin();
	auto it_type = m_id_type.begin();
	for (; it_name != m_id_name.end(); it_name++, it_type++) {
		if (*it_name == name) {
			return *it_type;
		}
	}
	return IdType::ID_NDEFINED;
}

bool mgc::eval::Evaluator::is_error(const std::shared_ptr<mgc::objj::Object> & obj) {
	return obj->type() == mgc::objj::Object::OBJ_ERROR;
}
std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_error(const char* format, ...) {
	char buf[1024] = { 0 };
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf_s(buf, format, arg_ptr);
	va_end(arg_ptr);

	std::shared_ptr<Error> obj(new Error());
	obj->m_message = buf;
	return obj;
}
std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_integer(int64_t value) {
	return mgc::objj::Object::new_integer(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_decimal(int64_t integer, int decimal) {
	return mgc::objj::Object::new_decimal(integer, decimal);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_boolean(bool value) {
	return mgc::objj::Object::new_boolean(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_predicate(LogicNode* value) {
	return mgc::objj::Object::new_predicate(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_string(string value) {
	return mgc::objj::Object::new_string(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_identifier(string name) {
	return mgc::objj::Object::new_identifier(name);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_identifier(string name,std::shared_ptr<mgc::objj::Object> value) {
	return mgc::objj::Object::new_identifier(name,value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_func(string name, std::list<std::shared_ptr<ast::Identifier>> ids, std::shared_ptr <ast::Block> block) {
	std::vector<std::shared_ptr<mgc::objj::Object>> obj_ids;
	for (auto it = ids.begin(); it != ids.end(); it++) {
		obj_ids.push_back(new_identifier((*it)->m_name));
	}
	return mgc::objj::Object::new_func(name, obj_ids, block);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_declaration(string value) {
	return mgc::objj::Object::new_declaration(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_result_list(std::list<std::shared_ptr<mgc::objj::Object>> value) {
	return mgc::objj::Object::new_result_list(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_noeud(LogicNode* value) {
	return mgc::objj::Object::new_noeud(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::new_logic_noeud(LogicNode* value) {
	return mgc::objj::Object::new_logic_node(value);
}

std::shared_ptr<mgc::objj::Object> mgc::eval::Evaluator::eval(const std::shared_ptr<Node> & node) {
	switch (node->type()) {
		case Node::NODE_PROGRAM: {
			auto s = std::dynamic_pointer_cast<ast::Program>(node);
			return eval_program(s->m_statements);
		}
		case Node::NODE_BLOCK: {
			auto s = std::dynamic_pointer_cast<ast::Block>(node);
			Evaluator eval_block;
			auto id_name = this->m_id_name.begin();
			auto id_type = this->m_id_type.begin();
			auto id_ptr = this->m_id_value.begin();
			for (; id_name != this->m_id_name.end(); id_name++, id_type++, id_ptr++) {
				eval_block.m_id_name.push_back(*id_name);
				eval_block.m_id_type.push_back(*id_type);
				eval_block.m_id_value.push_back(*id_ptr);
			}
			auto r = eval_block.eval_program(s->m_statements);
			id_ptr = this->m_id_value.begin();
			auto e_b_ptr = eval_block.m_id_value.begin();
			for (; id_ptr != this->m_id_value.end(); e_b_ptr++, id_ptr++) {
				*id_ptr = *e_b_ptr;
			}
			return r;
		}
		case Node::NODE_EXPRESSION_STATEMENT: {
			auto s = std::dynamic_pointer_cast<ast::ExpressionStatement>(node);
			return eval(s->m_expression);
		}
		case Node::NODE_INTEGER: {
			auto e = std::dynamic_pointer_cast<ast::Integer>(node);
			return eval_integer(e);
		}
		case Node::NODE_STRING: {
			auto e = std::dynamic_pointer_cast<ast::Mstring>(node);
			return eval_string(e);
		}
		case Node::NODE_BOOL: {
			auto e = std::dynamic_pointer_cast<ast::Bool>(node);
			return eval_boolean(e);
		}
		case Node::NODE_IDENTIFIER: {
			auto e = std::dynamic_pointer_cast<ast::Identifier>(node);
			return eval_identifier(e);
		}
		case Node::NODE_PREIDENTIFIER: {
			auto e = std::dynamic_pointer_cast<ast::PreIdentifier>(node);
			return eval_pre_identifier(e);
		}
		case Node::NODE_DECLARATION: {
			auto e = std::dynamic_pointer_cast<ast::Declaration>(node);
			return eval_declaration(e);
		}
		case Node::NODE_FUNCEXPRESSION: {
			auto e = std::dynamic_pointer_cast<ast::FuncExpression>(node);
			auto efe = eval_func_expression(e);
			return efe;
		}
		case Node::NODE_PREFIX: {
			auto e = std::dynamic_pointer_cast<ast::Prefix>(node);

			auto body = eval(e->m_body);

			if (is_error(body)) return body;

			return eval_prefix(e->m_operator, body);
		}
		case Node::NODE_PREPREFIX : {
			auto e = std::dynamic_pointer_cast<ast::PrePrefix>(node);

			auto body = eval(e->m_body);

			if (is_error(body)) return body;

			auto n = std::dynamic_pointer_cast<objj::ObjLogicNode>(eval_pre_prefix(e->m_operator, body));
			m_logic_node.push_back(n);
			return n;
		}
		case Node::NODE_INFIX: {
			auto e = std::dynamic_pointer_cast<ast::Infix>(node);

			auto left = eval(e->m_left);

			if (is_error(left)) {
				return left;
			}
			auto right = eval(e->m_right);

			if (is_error(right)) {
				return right;
			}
			return eval_infix(e->m_operator, left, right);
		}
		case Node::NODE_PREINFIX: {
			auto e = std::dynamic_pointer_cast<ast::PreInfix>(node);

			auto left = eval(e->m_left);

			if (is_error(left)) {
				return left;
			}
			auto right = eval(e->m_right);

			if (is_error(right)) {
				return right;
			}

			auto n = std::dynamic_pointer_cast<objj::ObjLogicNode>(eval_pre_infix(e->m_operator, left, right));
			m_logic_node.push_back(n);
			return n;
		}
		case Node::NODE_KNOW: {
			auto s = std::dynamic_pointer_cast<ast::Know>(node);
			auto k = (eval(s->m_precondition));
			if (!(k->set_value(1))) {
				cout << "出现矛盾" << endl;
				return new_boolean(false);
			}
			auto it_type = m_id_type.begin();
			auto it_ptr = m_id_value.begin();
			for (; it_type != m_id_type.end(); it_type++, it_ptr++) {
				if (*it_type == IdType::ID_PROPO) {
					auto it_propo = dynamic_pointer_cast<objj::ObjLogicNode>(*it_ptr);
					if (it_propo != nullptr) {
						if (it_propo->m_noeud->get_value() == -1) {
							if (!(it_propo->m_noeud->imagine_set_value(1))) {
								it_propo->m_noeud->imagine_unset_value();
								if (!(it_propo->m_noeud->set_value(0))) {
									cout << "出现矛盾" << endl;
									return new_boolean(false);
								}
								return new_boolean(true);
							}
							it_propo->m_noeud->imagine_unset_value();

							if (!(it_propo->m_noeud->imagine_set_value(0))) {
								it_propo->m_noeud->imagine_unset_value();
								if (!(it_propo->m_noeud->set_value(1))) {
									cout << "出现矛盾" << endl;
									return new_boolean(false);
								}
								return new_boolean(true);
							}
							it_propo->m_noeud->imagine_unset_value();
						}
					}
				}
			}
			return new_boolean(true);
		}
		case Node::NODE_INFER: {
			auto s = std::dynamic_pointer_cast<ast::Infer>(node);
			eval_infer(s->m_members,s->m_tnum);
			return new_boolean(true);
		}
		case Node::NODE_OUTPUT: {
			auto s = std::dynamic_pointer_cast<ast::OutPut>(node);
			if (s->m_statement->type() == ast::Node::Type::NODE_IDENTIFIER) {
				auto id = std::dynamic_pointer_cast<ast::Identifier>(s->m_statement);
				auto it = find_id_ptr(id->m_name);
				if (it != nullptr) {
					if (it->type() == mgc::objj::Object::OBJ_LOGICNODE) {
						auto ln = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(it);
						cout << ln->m_noeud->get_propo() << "=" << ln->m_noeud->get_value() << endl;
						auto e = eval(s->m_statement);
						return e;
					}
				}
				else {
					return new_string("unknown identifier:"+id->m_name);
				}
			}
			auto e = eval(s->m_statement);
			cout << e->str() << endl;
			return e;
		}
		case Node::NODE_IF: {
			auto s = std::dynamic_pointer_cast<ast::If>(node);
			auto e = eval(s->m_condition);
			auto id = dynamic_pointer_cast<mgc::objj::Identifier>(e);
			if (id != nullptr) {
				e = id->m_value;
			}
			std::shared_ptr<mgc::objj::Bool> bo;
			if (e->type() == mgc::objj::Object::OBJ_BOOLEAN) {
				bo = std::dynamic_pointer_cast<mgc::objj::Bool>(e);
			}
			else if(e->type() == mgc::objj::Object::OBJ_INTEGER) {
				auto in = std::dynamic_pointer_cast<mgc::objj::Integer>(e);
				bo = std::dynamic_pointer_cast<mgc::objj::Bool>(new_boolean(in->m_value != 0));
			}
			else if (e->type() == mgc::objj::Object::OBJ_LOGICNODE) {
				auto ln = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(e);
				bo = std::dynamic_pointer_cast<mgc::objj::Bool>(new_boolean(ln->m_noeud->get_value() != 0));
			}
			if (bo != nullptr) {
				if (bo->m_value) {
					return eval(s->m_block);
				}
				else {
					return eval(s->m_else);
				}
			}
		}
		case Node::NODE_WHILE: {
			auto s = std::dynamic_pointer_cast<ast::While>(node);
			std::shared_ptr<mgc::objj::Object> e;
			while (true) {
				e = eval(s->m_condition);
				auto id = dynamic_pointer_cast<mgc::objj::Identifier>(e);
				if (id != nullptr) {
					e = id->m_value;
				}
				std::shared_ptr<mgc::objj::Bool> bo;
				if (e->type() == mgc::objj::Object::OBJ_BOOLEAN) {
					bo = std::dynamic_pointer_cast<mgc::objj::Bool>(e);
				}
				else if (e->type() == mgc::objj::Object::OBJ_INTEGER) {
					auto in = std::dynamic_pointer_cast<mgc::objj::Integer>(e);
					bo = std::dynamic_pointer_cast<mgc::objj::Bool>(new_boolean(in->m_value != 0));
				}
				else if (e->type() == mgc::objj::Object::OBJ_LOGICNODE) {
					auto ln = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(e);
					bo = std::dynamic_pointer_cast<mgc::objj::Bool>(new_boolean(ln->m_noeud->get_value() != 0));
				}
				if (bo != nullptr) {
					if (bo->m_value) {
						eval(s->m_block);
					}
					else {
						return new_boolean(false);
					}
				}
			}
		}
		case Node::NODE_FOR: {
			auto s = std::dynamic_pointer_cast<ast::For>(node);
			auto e = eval(s->m_time);
			auto id = dynamic_pointer_cast<mgc::objj::Identifier>(e);
			if (id != nullptr) {
				e = id->m_value;
			}
			std::shared_ptr<mgc::objj::Integer> in;
			if (e->type() == mgc::objj::Object::OBJ_BOOLEAN) {
				auto bo = std::dynamic_pointer_cast<mgc::objj::Bool>(e);
				in = std::dynamic_pointer_cast<mgc::objj::Integer>(new_integer(bo->m_value));
			}
			else if (e->type() == mgc::objj::Object::OBJ_INTEGER) {
				in = std::dynamic_pointer_cast<mgc::objj::Integer>(e);
			}
			else if (e->type() == mgc::objj::Object::OBJ_LOGICNODE) {
				auto ln = std::dynamic_pointer_cast<mgc::objj::ObjLogicNode>(e);
				in = std::dynamic_pointer_cast<mgc::objj::Integer>(new_integer(ln->m_noeud->get_value()));
			}
			if (in != nullptr) {
				int n = (int)(in->m_value);
				for (int i = 0; i < n; i++) {
					eval(s->m_block);
				}
				return new_boolean(true);
			}
		}
		case Node::NODE_FUNC: {
			auto s = std::dynamic_pointer_cast<ast::Func>(node);
			this->m_id_name.push_back(s->m_func_name);
			this->m_id_type.push_back(IdType::ID_FUNC);
			auto f = new_func(s->m_func_name, s->m_ids, s->m_block);
			this->m_id_value.push_back(f);
			return f;
		}
		default: {
			//error
			printf("error\n Evaluator.cpp\n eval\n cannot eval this node");
			return new_error("error\n Evaluator.cpp\n eval\n cannot eval this node");
		}
	}
}

int Evaluator::get_bit(int64_t n) {
	int bit = 0;
	while (n != 0) {
		n /= 10;
		bit++;
	}
	return bit;
}