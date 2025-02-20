#include "mgcEvaluator.hpp"

using namespace mgc::eval;

std::shared_ptr<mgc::objj::Object> Evaluator::eval_program(const std::list<std::shared_ptr<Statement>>& stmts) {
	std::shared_ptr<mgc::objj::Object> result;
	std::list<std::shared_ptr<mgc::objj::Object>> results;
	for (auto & stat : stmts) {
		result = eval(stat);
		if (is_error(result)) {
			break;
		}
		results.push_back(result);
	}
	return new_result_list(results);
}