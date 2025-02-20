#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_string(const std::shared_ptr<ast::Mstring>& node) {
	return new_string(node->m_string);
}