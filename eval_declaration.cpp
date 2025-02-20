#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_declaration(const std::shared_ptr<ast::Declaration>& node) {
	return new_declaration(node->m_name);
}