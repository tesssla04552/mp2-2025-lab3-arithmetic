// реализация функций и классов для вычисления арифметических выражений
#include "stack.h"
#include "arithmetic.h"
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <stdexcept>
Token::Token(const std::string& val, const std::string& typ) : value(val), type(typ) {}
void TPostfix::initializePriority() {
	priority['+'] = 1;
	priority['-'] = 1;
	priority['*'] = 2;
	priority['/'] = 2;
	priority['^'] = 3;
	priority['('] = 0;
	priority[')'] = 0;
}
bool TPostfix::isOperator(char c) const {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool TPostfix::isBracket(char c) const {
	return c == '(' || c == ')';
}
bool TPostfix::isVariableChar(char c) const {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool TPostfix::isNumber(const std::string& str) const {
	if (str.empty()) return false;
	size_t start = 0;
	if (str[0] == '-' && str.length() > 1) {
		start = 1;
	}
	bool hasDecimal = false;
	bool hasDigit = false;
	for (size_t i = start; i < str.length(); i++) {
		if (str[i] == '.') {
			if (hasDecimal) return false;
			hasDecimal = true;
		}
		else if (std::isdigit(str[i])) {
			hasDigit = true;
		}
		else {
			return false;
		}
	}
	return hasDigit;
}
TPostfix::TPostfix(const std::string& infixExpr) : infix(infixExpr) {
	initializePriority();
}
void TPostfix::setInfix(const std::string& infixExpr) {
	infix = infixExpr;
	postfix = "";
	tokens.clear();
}
std::string TPostfix::GetInfix() const {
	std::string result = infix;
	return result;
}
std::string TPostfix::GetPostfix() {
	std::string result = postfix;
	if (result.empty()) {
		result = toPostfix();
	}
	return result;
}
void TPostfix::SetVariable(const std::string& name, double value) {
	variables[name] = value;
}
double TPostfix::GetVariable(const std::string& name) const {
	auto it = variables.find(name);
	if (it != variables.end()) {
		return it->second;
	}
	throw std::invalid_argument("Variable '" + name + "' not found");
}
std::vector<Token> TPostfix::tokenize() {
	tokens.clear();
	std::string currentToken = "";
	for (size_t i = 0; i < infix.length(); i++) {
		char c = infix[i];
		if (std::isspace(c)) {
			if (!currentToken.empty()) {
				std::string type = isNumber(currentToken) ? "number" : "variable";
				tokens.push_back(Token(currentToken, type));
				currentToken = "";
			}
			continue;
		}
		if (c == '-' && (tokens.empty() || tokens.back().value == "(" || tokens.back().type == "operator")) {
			currentToken += c;
			continue;
		}
		if (isOperator(c) || isBracket(c)) {
			if (!currentToken.empty()) {
				std::string type = isNumber(currentToken) ? "number" : "variable";
				tokens.push_back(Token(currentToken, type));
				currentToken = "";
			}
			std::string type = isBracket(c) ? "bracket" : "operator";
			tokens.push_back(Token(std::string(1, c), type));
		}
		else {
			currentToken += c;
		}
	}
	if (!currentToken.empty()) {
		std::string type = isNumber(currentToken) ? "number" : "variable";
		tokens.push_back(Token(currentToken, type));
	}
	return tokens;
}
bool TPostfix::validate() {
	if (infix.empty()) {
		throw std::invalid_argument("Expression is empty");
	}		
	tokenize();
	if (tokens.empty()) {
		throw std::invalid_argument("No tokens found in expression");
	}
	TStack<int> bracketStack(tokens.size());
	const Token* lastToken = nullptr;
	for (size_t i = 0; i < tokens.size(); i++) {
		const Token& token = tokens[i];
		if (token.type == "variable") {
			for (char c : token.value) {
				if (!isVariableChar(c)) {
					throw std::invalid_argument("Invalid character in variable name: " + token.value);
				}
			}
		}
		if (token.value == "(") {
			bracketStack.push(i);
		}
		else if (token.value == ")") {
			if (bracketStack.isEmpty()) {
				throw std::invalid_argument("Unmatched closing bracket at position " + std::to_string(i));
			}
			bracketStack.pop();
		}
		if (lastToken != nullptr) {
			if (lastToken->type == "operator" && token.type == "operator") {
				if (token.value != "-") {
					throw std::invalid_argument("Two operators in a row " + lastToken->value + " " + token.value);
				}
			}
			if ((lastToken->type == "number" || lastToken->type == "variable") && (token.type == "number" || token.type == "variable")) {
				throw std::invalid_argument("Missing operator between: " + lastToken->value + " and " + token.value);
			}
			if ((lastToken->type == "number" || lastToken->type == "variable") && token.value == "(") {
				throw std::invalid_argument("Missing operator before opening bracket after: " + lastToken->value);
			}
			if (lastToken->type == "operator" && token.value == ")") {
				throw std::invalid_argument("Missing operand before closing bracket after operator: " + lastToken->value);
			}
		}
		else {
			if (token.type == "operator" && token.value != "-") {
				throw std::invalid_argument("Expression cannot start with operator: " + token.value);
			}
		}
		lastToken = &token;
	}
	if (!bracketStack.isEmpty()) {
		throw std::invalid_argument("Unmatched opening bracket");
	}
	if (!tokens.empty() && tokens.back().type == "operator") {
		throw std::invalid_argument("Expression cannot end with operator: " + tokens.back().value);
	}	
	return true;
}
std::string TPostfix::toPostfix() {
	validate();
	TStack<std::string> stack(tokens.size());
	postfix = "";
	for (const Token& token : tokens) {
		if (token.type == "number" || token.type == "variable") {
			postfix += token.value + " ";
		}
		else if (token.value == "(") {
			stack.push(token.value);
		}
		else if (token.value == ")") {
			while (!stack.isEmpty() && stack.peek() != "(") {
				postfix += stack.pop() + " ";
			}
			if (!stack.isEmpty() && stack.peek() == "(") {
				stack.pop();
			}
		}
		else if (token.type == "operator") {
			while (!stack.isEmpty() && stack.peek() != "(" && priority[stack.peek()[0]] >= priority[token.value[0]]) {
				postfix += stack.pop() + " ";
			}
			stack.push(token.value);
		}
	}
	while (!stack.isEmpty()) {
		postfix += stack.pop() + " ";
	}
	if (!postfix.empty() && postfix.back() == ' ') {
		postfix.pop_back();
	}
	return postfix;
}
double TPostfix::calculate() {
	if (postfix.empty()) {
		toPostfix();
	}
	TStack<double> stack(tokens.size());
	std::stringstream ss(postfix);
	std::string token;
	while (ss >> token) {
		if (isNumber(token)) {
			stack.push(std::stod(token));
		}
		else if (isVariableChar(token[0])) {
			auto it = variables.find(token);
			if (it == variables.end()) {
				throw std::invalid_argument("Underfined variable: " + token);
			}
			stack.push(it->second);
		}
		else if (isOperator(token[0])) {
			if (stack.GetSize() < 2) {
				throw std::invalid_argument("Not enough operands for operator: " + token);
			}
			double b = stack.pop();
			double a = stack.pop();
			double result = 0.0;
			switch (token[0]) {
			case '+':
				result = a + b; break;
			case '-':
				result = a - b; break;
			case '*':
				result = a * b; break;
			case '/':
				if (b == 0) throw std::runtime_error("Division by zero");
				result = a / b;
				break;
			case '^':
				result = std::pow(a, b);
				break;
			default:
				throw std::invalid_argument("Unknown operator: " + token);
			}
			stack.push(result);
		}
	}
	if (stack.GetSize() != 1) {
		throw std::invalid_argument("Invalid expression");
	}
	return stack.pop();
}
std::vector<Token> TPostfix::GetTokens() const {
	return tokens;
}

