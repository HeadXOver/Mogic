#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_boolean(const std::shared_ptr<ast::Bool>& node){
	return new_boolean(node->m_bool);
}