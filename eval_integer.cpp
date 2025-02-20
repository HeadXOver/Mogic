#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_integer(const std::shared_ptr<ast::Integer> & node) {
	return new_integer(node->m_value);
}