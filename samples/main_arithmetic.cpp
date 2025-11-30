// реализация пользовательского приложения
#include "arithmetic.h"
#include <iostream>
int main()
{
	std::cout << "===== SIMPLE EXPRESSION CALCULATOR =====" << std::endl;
	std::cout << "Operations are supported: +, -, *, /, ^" << std::endl;
	std::cout << "The use of variables and brackets is supported" << std::endl;
	std::cout << "Examples: 2+3*4, (a+b)*c, x^2+y^2" << std::endl << std::endl;
	while (true) {
		std::string expression;
		std::cout << "Enter a expression (or 'exit' for exit):" << std::endl;
		std::getline(std::cin, expression);
		if (expression == "exit") {
			break;
		}
		if (expression.empty()) {
			continue;
		}
		try {
			TPostfix postfix(expression);
			postfix.tokenize();
			auto tokens = postfix.GetTokens();
			for (const auto& token : tokens) {
				if (token.type == "variable") {
					double value;
					std::cout << "Enter a value for " << token.value << ": ";
					std::cin >> value;
					postfix.SetVariable(token.value, value);
					std::cin.ignore();
				}
			}
			double result = postfix.calculate();
			std::cout << "RESULT: " << result << std::endl;
			std::cout << "POSTFIX ENTRY: " << postfix.GetPostfix() << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "ERROR: " << e.what() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "PROGRAM COMPLETED." << std::endl;
  return 0;
}
