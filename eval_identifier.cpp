#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_identifier(const std::shared_ptr<ast::Identifier>& node) {
	auto it = find_id_ptr(node->m_name);
	if (it != nullptr) {
		return new_identifier(node->m_name, it);
	}
	return new_identifier(node->m_name);
}

std::shared_ptr<mgc::objj::Object> Evaluator::eval_pre_identifier(const std::shared_ptr<ast::PreIdentifier>& node) {
	auto it = find_id_ptr(node->m_name, IdType::ID_PROPO);
	if (it != nullptr) return it;
	
	cout << "cannot find identifier " << node->m_name << endl;
	return new_error("cannot find identifier %s", node->m_name.c_str());
}