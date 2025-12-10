// тесты для вычисления арифметических выражений
#include <gtest.h>
#include <arithmetic.h>
TEST(TPostfix, test_getInfix_returns_exact_input_expression) {
	std::string expression = "2 + 3 * 4";
	TPostfix postfix(expression);
	EXPECT_EQ(postfix.GetInfix(), expression);
}
TEST(TPostfix, test_getInfix_returns_empty_string_for_default_constructor) {
	TPostfix postfix;
	EXPECT_TRUE(postfix.GetInfix().empty());
}
TEST(TPostfix, test_setInfix_replaces_existing_expression) {
	TPostfix postfix("2 + 3");
	postfix.setInfix("5 * 4");
	EXPECT_EQ(postfix.GetInfix(), "5 * 4");
}
TEST(TPostfix, test_setInfix_clears_postfix_cache) {
	TPostfix postfix("2 + 3");
	std::string postfix1 = postfix.GetPostfix();
	postfix.setInfix("5 * 4");
	std::string postfix2 = postfix.GetPostfix();
	EXPECT_NE(postfix1, postfix2);
}
TEST(TPostfix, test_setVariable_stores_value_correctly) {
	TPostfix postfix;
	postfix.SetVariable("x", 5.5);
	EXPECT_DOUBLE_EQ(postfix.GetVariable("x"), 5.5);
}
TEST(TPostfix, test_setVariable_overwrites_existing_value) {
	TPostfix postfix;
	postfix.SetVariable("x", 5.5);
	postfix.SetVariable("x", 10.2);
	EXPECT_DOUBLE_EQ(postfix.GetVariable("x"), 10.2);
}
TEST(TPostfix, test_setVariable_supports_miltiple_variables) {
	TPostfix postfix;
	postfix.SetVariable("x", 5.5);
	postfix.SetVariable("y", 3.2);
	postfix.SetVariable("z", 7.8);
	EXPECT_DOUBLE_EQ(postfix.GetVariable("x"), 5.5);
	EXPECT_DOUBLE_EQ(postfix.GetVariable("y"), 3.2);
	EXPECT_DOUBLE_EQ(postfix.GetVariable("z"), 7.8);
}
TEST(TPostfix, test_getVariable_throws_for_underfined_variable) {
	TPostfix postfix;
	EXPECT_THROW(postfix.GetVariable("nonexistent"), std::invalid_argument);
}
TEST(TPostfix, test_getVariable_throws_with_correct_error_message) {
	TPostfix postfix;
	try {
		postfix.GetVariable("undefined_var");
		FAIL() << "Expected std::invalid_argument";
	}
	catch (const std::invalid_argument& e) {
		EXPECT_NE(std::string(e.what()).find("undefined_var"), std::string::npos);
	}
}
TEST(TPostfix, test_calculate_addition_returns_correct_result) {
	TPostfix postfix("2 + 3");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0);
}
TEST(TPostfix, test_calculate_subtraction_returns_correct_result) {
	TPostfix postfix("10 - 4");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 6.0);
}
TEST(TPostfix, test_calculate_multiplication_returns_correct_result) {
	TPostfix postfix("3 * 4");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 12.0);
}
TEST(TPostfix, test_calculate_division_returns_correct_result) {
	TPostfix postfix("15 / 3");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0);
}
TEST(TPostfix, test_calculate_power_returns_correct_result) {
	TPostfix postfix("2 ^ 3");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 8.0);
}
TEST(TPostfix, test_calculate_expression_with_parentheses_correctly) {
	TPostfix postfix("(10 + 2) * 3");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 36.0);
}
TEST(TPostfix, test_calculate_mixed_operations_with_parentheses) {
	TPostfix postfix("(10 + 2) * 3 - 4 / 2");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 34.0);
}
TEST(TPostfix, test_calculate_power_with_multiplication) {
	TPostfix postfix("2 ^ 3 + 4 * 5");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 28.0);
}
TEST(TPostfix, test_multiplication_has_higher_priority_than_addition) {
	TPostfix postfix("2 + 3 * 4");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 14.0);
}
TEST(TPostfix, test_addition_and_subtraction_have_same_priority_left_associative) {
	TPostfix postfix("10 - 5 + 3");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 8.0);
}
TEST(TPostfix, test_multiplication_and_division_have_same_priority_left_associative) {
	TPostfix postfix("12 / 3 * 2");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 8.0);
}
TEST(TPostfix, test_power_has_higher_priority_than_multiplication) {
	TPostfix postfix("2 * 3 ^ 2");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 18.0);
}
TEST(TPostfix, test_calculate_with_single_variable) {
	TPostfix postfix("x + 3");
	postfix.SetVariable("x", 5);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 8.0);
}
TEST(TPostfix, test_calculate_with_multiple_variables) {
	TPostfix postfix("a * b + c / d");
	postfix.SetVariable("a", 5);
	postfix.SetVariable("b", 3);
	postfix.SetVariable("c", 10);
	postfix.SetVariable("d", 2);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 20.0);
}
TEST(TPostfix, test_calculate_throws_for_undefined_variable_in_expression) {
	TPostfix postfix("x + 1");
	EXPECT_THROW(postfix.calculate(), std::invalid_argument);
}
TEST(TPostfix, test_calculate_throws_on_division_by_zero) {
	TPostfix postfix("5 / 0");
	EXPECT_THROW(postfix.calculate(), std::runtime_error);
}
TEST(TPostfix, test_division_by_zero_error_has_correct_message) {
	TPostfix postfix("5 / 0");
	try {
		postfix.calculate();
		FAIL() << "Expected std::runtime_error";
	}
	catch (const std::runtime_error& e) {
		EXPECT_NE(std::string(e.what()).find("Division by zero"), std::string::npos);
	}
}
TEST(TPostfix, test_getPostfix_returns_non_empty_string_for_valid_expression) {
	TPostfix postfix("a + b * c");
	EXPECT_FALSE(postfix.GetPostfix().empty());
}
TEST(TPostfix, test_getPostfix_returns_correct_postfix_for_simple_expression) {
	TPostfix postfix("a + b");
	std::string result = postfix.GetPostfix();
	EXPECT_EQ(result, "a b +");
}
TEST(TPostfix, test_getPostfix_returns_correct_postfix_with_parentheses) {
	TPostfix postfix("(a + b) * c");
	std::string result = postfix.GetPostfix();
	EXPECT_EQ(result, "a b + c *");
}
TEST(TPostfix, test_getPostfix_is_cached_and_returns_same_result) {
	TPostfix postfix("2 + 3 * 4");
	std::string result1 = postfix.GetPostfix();
	std::string result2 = postfix.GetPostfix();
	EXPECT_EQ(result1, result2);
}
TEST(TPostfix, test_getPostfix_updates_after_setInfix) {
	TPostfix postfix("2 + 3");
	std::string postfix1 = postfix.GetPostfix();
	postfix.setInfix("5 * 4");
	std::string postfix2 = postfix.GetPostfix();
	EXPECT_NE(postfix1, postfix2);
}
TEST(TPostfix, test_tokenize_returns_non_empty_vector_for_valid_expression) {
	TPostfix postfix("(a + 25.5) * b - 3^2");
	auto tokens = postfix.tokenize();
	EXPECT_FALSE(tokens.empty());
}
TEST(TPostfix, test_tokenize_correctly_identifies_numbers) {
	TPostfix postfix("25.5 + 3.14");
	auto tokens = postfix.tokenize();
	bool hasNumber = false;
	for (const auto& token : tokens) {
		if (token.type == "number") {
			hasNumber = true;
			break;
		}
	}
	EXPECT_TRUE(hasNumber);
}
TEST(TPostfix, test_tokenize_correctly_identifies_variables) {
	TPostfix postfix("x + y");
	auto tokens = postfix.tokenize();
	bool hasVariable = false;
	for (const auto& token : tokens) {
		if (token.type == "variable") {
			hasVariable = true;
			break;
		}
	}
	EXPECT_TRUE(hasVariable);
}
TEST(TPostfix, test_tokenize_correctly_identifies_operators) {
	TPostfix postfix("a + b * c");
	auto tokens = postfix.tokenize();
	bool hasOperator = false;
	for (const auto& token : tokens) {
		if (token.type == "operator") {
			hasOperator = true;
			break;
		}
	}
	EXPECT_TRUE(hasOperator);
}
TEST(TPostfix, test_tokenize_handles_spaces_correctly) {
	TPostfix postfix(" a + b ");
	EXPECT_NO_THROW(postfix.tokenize());
	auto tokens = postfix.tokenize();
	EXPECT_GE(tokens.size(), 3);
}
TEST(TPostfix, test_validate_accepts_correct_simple_expression) {
	TPostfix postfix("2 + 3");
	EXPECT_NO_THROW(postfix.validate());
	EXPECT_TRUE(postfix.validate());
}
TEST(TPostfix, test_validate_accepts_expression_with_variables) {
	TPostfix postfix("(a + b) * c");
	EXPECT_NO_THROW(postfix.validate());
}
TEST(TPostfix, test_validate_accepts_expression_with_power) {
	TPostfix postfix("x^2 + y^2");
	EXPECT_NO_THROW(postfix.validate());
}
TEST(TPostfix, test_validate_accepts_expression_with_decimal_numbers) {
	TPostfix postfix("2 + + 3");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_two_consecutive_operators) {
	TPostfix postfix("2 + + 3");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_unmatched_opening_parenthesis) {
	TPostfix postfix("(a + b");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_unmatched_closing_parenthesis) {
	TPostfix postfix("a + b)");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_missing_operator_between_operands) {
	TPostfix postfix("2 3 +");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_expression_starting_with_binary_operator) {
	TPostfix postfix("* 2 + 3");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_expression_ending_with_operator) {
	TPostfix postfix("2 + 3 *");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_validate_throws_for_empty_expression) {
	TPostfix postfix("");
	EXPECT_THROW(postfix.validate(), std::invalid_argument);
}
TEST(TPostfix, test_calculate_handles_negative_result) {
	TPostfix postfix("5 - 10");
	EXPECT_DOUBLE_EQ(postfix.calculate(), -5.0);
}
TEST(TPostfix, test_calculate_handles_unary_minus_at_start) {
	TPostfix postfix("-3 + 7");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 4.0);
}
TEST(TPostfix, test_calculate_handles_unary_minus_after_parenthesis) {
	TPostfix postfix("(-3 + 5) * 2");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 4.0);
}
TEST(TPostfix, test_calculate_handles_negative_variable_values) {
	TPostfix postfix("x + 5");
	postfix.SetVariable("x", -3);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 2.0);
}
TEST(TPostfix, test_calculate_handles_decimal_division) {
	TPostfix postfix("10.0 / 4.0");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 2.5);
}
TEST(TPostfix, test_calculate_handles_small_decimal_numbers) {
	TPostfix postfix("0.1 + 0.2");
	EXPECT_DOUBLE_EQ(postfix.calculate(), 0.3);
}
TEST(TPostfix, test_full_workflow_with_variables_and_parentheses) {
	std::string expression = "(x + y) * z - w^2";
	TPostfix postfix(expression);
	EXPECT_NO_THROW(postfix.validate());
	std::string postfixExpr = postfix.GetPostfix();
	EXPECT_FALSE(postfixExpr.empty());
	postfix.SetVariable("x", 3);
	postfix.SetVariable("y", 5);
	postfix.SetVariable("z", 2);
	postfix.SetVariable("w", 4);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 0.0);
}
TEST(TPostfix, test_multiple_expressions_with_same_object) {
	TPostfix postfix;
	postfix.setInfix("a + b");
	postfix.SetVariable("a", 2);
	postfix.SetVariable("b", 3);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0);
	postfix.setInfix("a * b - c");
	postfix.SetVariable("c", 1);
	EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0); 
}