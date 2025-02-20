#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_func_expression(const std::shared_ptr<ast::FuncExpression>& node) {
	auto it = std::dynamic_pointer_cast<objj::ObjLogicNode>(find_id_ptr(node->m_func_name, IdType::ID_OBJPREDI));
	if (it != nullptr) {
		std::list<LogicNode*> obj_list;
		for (auto& e : node->m_expressions) {
			auto it_name = std::dynamic_pointer_cast<ast::Identifier>(e);
			auto obj = std::dynamic_pointer_cast<objj::ObjLogicNode>(find_id_ptr(it_name->m_name, IdType::ID_OBJ));
			if (obj != nullptr) {
				obj_list.push_back(obj->m_noeud.get());
			}
			else {
				return new_error("can't find the predicate object:%s", it_name->m_name.c_str());
			}
		}
		LogicNode* predi(new mgc::LogicNode(it->m_noeud, obj_list));
		auto nl = std::dynamic_pointer_cast<objj::ObjLogicNode>(new_logic_noeud(predi));
		m_predi_node.push_back(nl);
		return nl;
	}
	auto it_func = find_id_ptr(node->m_func_name, IdType::ID_FUNC);
	if (it_func != nullptr) {
		auto it = std::dynamic_pointer_cast<objj::Func>(it_func);
		auto e = node->m_expressions.begin();
		Evaluator evalfunc;
		for (auto& arg : it->m_ids) {
			arg->m_value = eval(*e);
			evalfunc.m_id_name.push_back(arg->m_name);
			switch (arg->m_value->type()) {
			case mgc::objj::Object::Type::OBJ_INTEGER: {
				evalfunc.m_id_type.push_back(IdType::ID_INT);
				break;
			}
			case mgc::objj::Object::Type::OBJ_BOOLEAN: {
				evalfunc.m_id_type.push_back(IdType::ID_BOOL);
				break;
			}
			case mgc::objj::Object::Type::OBJ_LOGICNODE: {
				evalfunc.m_id_type.push_back(IdType::ID_PROPO);
				break;
			}
			}
			evalfunc.m_id_value.push_back(arg->m_value);
			++e;
		}
		return evalfunc.eval(it->m_block);
	}
	return new_boolean(false);
}