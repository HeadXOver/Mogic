#include <iostream>

#include "Lexer.hpp"
#include "Paser.hpp"
#include "mgcEvaluator.hpp"
#include "LogicNode.hpp"

using namespace mgc;
using namespace mgc::lexer;
using namespace mgc::paser;
using namespace mgc::eval;

int main() {

	/*auto lexer_first = new Lexer("text.mgc");
	
	while (true) {
		auto token = lexer_first->next_token();
		token.show();
		if (token.type() == Token::TOKEN_EOF) {
			break;
		}
	}*/


	std::shared_ptr<Lexer> haifirst_lexer(new Lexer("text.mgc"));
	std::shared_ptr<Paser> halfirst_paser(new Paser(haifirst_lexer));
	auto program = halfirst_paser->parse_program();
	//program->show();
	auto errors = halfirst_paser->errors();
	if (!errors.empty()) {
		for (auto& error : errors) {
			std::cout << error << std::endl;
		}
		return -1;
	}
	printf("------------Mogic---------------\n\n");

	std::shared_ptr<Evaluator> halfirst_evaluator(new Evaluator());

	auto evaluated = halfirst_evaluator->eval(program);

	return 0;
}