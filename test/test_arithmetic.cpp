// тесты для вычисления арифметических выражений
#include <gtest.h>
#include <arithmetic.h>
TEST(TPostfix, test_get_infix_returns_correct_expression) {
	std::string expression = "2 + 3 * 4";
	TPostfix postfix(expression);
	std::string result = postfix.GetInfix();
	EXPECT_EQ(result, expression);
}
TEST(TPostfix, test_set_infix_changes_expression) {
	TPostfix postfix("2 + 3");
	EXPECT_EQ(postfix.GetInfix(), "2 + 3");
	postfix.setInfix("5 * 4");
	EXPECT_EQ(postfix.GetInfix(), "5 * 4");
}
TEST(TPostfix, test_set_and_get_variable_values) {
	TPostfix postfix;
	postfix.SetVariable("x", 5.5);
	postfix.SetVariable("y", 3.2);
	double x = postfix.GetVariable("x");
	double y = postfix.GetVariable("y");
	EXPECT_DOUBLE_EQ(x, 5.5);
	EXPECT_DOUBLE_EQ(y, 3.2);
}
TEST(TPostfix, test_throws_exception_for_undefined_variable) {
	TPostfix postfix;
	EXPECT_THROW(postfix.GetVariable("nonexistent"), std::invalid_argument);
}
TEST(TPostfix, test_calculate_simple_expressions) {
	TPostfix postfix1("2 + 3");
	double result1 = postfix1.calculate();
	EXPECT_DOUBLE_EQ(result1, 5.0);
	TPostfix postfix2("10 - 4");
	double result2 = postfix2.calculate();
	EXPECT_DOUBLE_EQ(result2, 6.0);
	TPostfix postfix3("3 * 4");
	double result3 = postfix3.calculate();
	EXPECT_DOUBLE_EQ(result3, 12.0);
	TPostfix postfix4("15 / 3");
	double result4 = postfix4.calculate();
	EXPECT_DOUBLE_EQ(result4, 5.0);
}
TEST(TPostfix, test_calculate_complex_expressions) {
	TPostfix postfix1("(10 + 2) * 3 - 4 / 2");
	double result1 = postfix1.calculate();
	EXPECT_DOUBLE_EQ(result1, 34.0);
	TPostfix postfix2("2 ^ 3 + 4 * 5");
	double result2 = postfix2.calculate();
	EXPECT_DOUBLE_EQ(result2, 28.0);
}
TEST(TPostfix, test_calculate_with_variables) {
	TPostfix postfix("a * b + c / d");
	postfix.SetVariable("a", 5); postfix.SetVariable("b", 3);
	postfix.SetVariable("c", 10); postfix.SetVariable("d", 2);
	double result = postfix.calculate();
	EXPECT_DOUBLE_EQ(result, 20.0);
}
TEST(TPostfix, test_respects_operator_precedence) {
	TPostfix postfix1("2 + 3 * 4");
	double result1 = postfix1.calculate();
	EXPECT_DOUBLE_EQ(result1, 14.0);
	TPostfix postfix2("2 * 3 + 4");
	double result2 = postfix2.calculate();
	EXPECT_DOUBLE_EQ(result2, 10.0);
}
TEST(TPostfix, test_throws_exception_on_division_by_zero) {
	TPostfix postfix("5 / 0");
	EXPECT_THROW(postfix.calculate(), std::runtime_error);
}
TEST(TPostfix, test_throws_exception_on_undefined_variable_in_calculation) {
	TPostfix postfix("x + 1");
	EXPECT_THROW(postfix.calculate(), std::invalid_argument);
}
TEST(TPostfix, test_get_postfix_returns_correct_notation) {
	TPostfix postfix1("a + b * c");
	std::string result1 = postfix1.GetPostfix();
	EXPECT_FALSE(result1.empty());
	TPostfix postfix2("(a + b) * c");
	std::string result2 = postfix2.GetPostfix();
	EXPECT_FALSE(result2.empty());
}
TEST(TPostfix, test_multiple_get_postfix_calls_return_same_result) {
	TPostfix postfix("2 + 3 * 4");
	std::string result1 = postfix.GetPostfix();
	std::string result2 = postfix.GetPostfix();
	EXPECT_EQ(result1, result2);
}
TEST(TPostfix, test_tokenize_complete_without_errors) {
	TPostfix postfix("(a + 25.5) * b - 3^2");
	EXPECT_NO_THROW(postfix.tokenize());
	std::vector<Token> tokens = postfix.GetTokens();
	EXPECT_FALSE(tokens.empty());
}
TEST(TPostfix, test_validate_correct_expressions) {
	EXPECT_NO_THROW(TPostfix("2 + 3").validate());
	EXPECT_NO_THROW(TPostfix("(a + b) * c").validate());
	EXPECT_NO_THROW(TPostfix("x^2 + y^2").validate());
	EXPECT_NO_THROW(TPostfix("3.14 * radius").validate());
}
TEST(TPostfix, test_validate_throws_exception_for_invalid_expressions) {
	EXPECT_THROW(TPostfix("2 + + 3").validate(), std::invalid_argument);
	EXPECT_THROW(TPostfix("(a + b").validate(), std::invalid_argument);
	EXPECT_THROW(TPostfix("a + b)").validate(), std::invalid_argument);
}
TEST(TPostfix, test_handles_negative_numbers) {
	TPostfix postfix1("5 - 10");
	double result1 = postfix1.calculate();
	EXPECT_DOUBLE_EQ(result1, -5.0);
	TPostfix postfix2("-3 + 7");
	double result2 = postfix2.calculate();
	EXPECT_DOUBLE_EQ(result2, 4.0);
}
TEST(TPostfix, test_full_integration) {
	std::string expression = "(x + y) * z - w^2";
	TPostfix postfix(expression);
	EXPECT_NO_THROW(postfix.validate());
	std::string postfixExpr = postfix.GetPostfix();
	EXPECT_FALSE(postfixExpr.empty());
	postfix.SetVariable("x", 3);
	postfix.SetVariable("y", 5);
	postfix.SetVariable("z", 2);
	postfix.SetVariable("w", 4);
	double result = postfix.calculate();
	EXPECT_DOUBLE_EQ(result, 0.0);
}
TEST(TPostfix, test_handles_floating_point_numbers) {
	TPostfix postfix("5.5 * 2 + 3.14");
	double result = postfix.calculate();
	EXPECT_DOUBLE_EQ(result, 14.14);
}
