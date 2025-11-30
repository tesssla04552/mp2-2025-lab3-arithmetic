// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include <vector>
#include <map>
struct Token {
	std::string value;
	std::string type;
	Token(const std::string& val = "", const std::string& typ = "");
};
class TPostfix {
private:
	std::string infix;
	std::string postfix;
	std::vector<Token> tokens;
	std::map<char, int> priority;
	std::map<std::string, double> variables;
	void initializePriority();
	bool isOperator(char c) const;
	bool isBracket(char c) const;
	bool isVariableChar(char c) const;
	bool isNumber(const std::string& str) const;
public:
	TPostfix(const std::string& infixExpr = "");
	void setInfix(const std::string& infixExpr);
	std::string GetInfix() const;
	std::string GetPostfix();
	void SetVariable(const std::string& name, double value);
	double GetVariable(const std::string& name) const;
	std::vector<Token> tokenize();
	bool validate();
	std::string toPostfix();
	double calculate();
	std::vector<Token> GetTokens() const;
};
