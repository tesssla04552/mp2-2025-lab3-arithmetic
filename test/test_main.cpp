#include <gtest.h>
#include "arithmetic.h"
#include <sstream>
#include <string>
TEST(main, test_addition_operation_works_correctly) {
    TPostfix postfix("2 + 3");
    EXPECT_NO_THROW(postfix.calculate());
}
TEST(main, test_addition_returns_correct_result) {
    TPostfix postfix("2 + 3");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0);
}
TEST(main, test_subtraction_returns_correct_result) {
    TPostfix postfix("10 - 4");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 6.0);
}
TEST(main, test_multiplication_returns_correct_result) {
    TPostfix postfix("3 * 4");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 12.0);
}
TEST(main, test_division_returns_correct_result) {
    TPostfix postfix("15 / 3");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 5.0);
}
TEST(main, test_multiplication_has_higher_priority_than_addition) {
    TPostfix postfix("2 + 3 * 4");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 14.0);
}
TEST(main, test_parentheses_override_operator_priority) {
    TPostfix postfix("((2 + 3) * 4) / 2");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 10.0);
}
TEST(main, test_setVariable_stores_value_for_calculation) {
    TPostfix postfix("x * y - z");
    postfix.SetVariable("x", 4.0);
    postfix.SetVariable("y", 3.0);
    postfix.SetVariable("z", 5.0);
    EXPECT_DOUBLE_EQ(postfix.calculate(), 7.0);
}
TEST(main, test_variables_can_be_reused_in_multiple_expressions) {
    TPostfix postfix1("x + y");
    postfix1.SetVariable("x", 2.0);
    postfix1.SetVariable("y", 3.0);
    EXPECT_DOUBLE_EQ(postfix1.calculate(), 5.0);
    TPostfix postfix2("x * y");
    postfix2.SetVariable("x", 2.0);
    postfix2.SetVariable("y", 3.0);
    EXPECT_DOUBLE_EQ(postfix2.calculate(), 6.0);
}
TEST(main, test_variable_value_persist_in_same_object) {
    TPostfix postfix("x + y + z");
    postfix.SetVariable("x", 1.0);
    postfix.SetVariable("y", 2.0);
    postfix.SetVariable("z", 3.0);
    double result1 = postfix.calculate();
    double result2 = postfix.calculate();
    EXPECT_DOUBLE_EQ(result1, 6.0);
    EXPECT_DOUBLE_EQ(result2, 6.0);
}
TEST(main, test_tokenize_returns_non_empty_vector) {
    TPostfix postfix("a + 2 * b");
    auto tokens = postfix.tokenize();
    EXPECT_FALSE(tokens.empty());
}
TEST(main, test_tokenize_correctly_identifies_variables_in_expression) {
    TPostfix postfix("a + 2 * b");
    auto tokens = postfix.tokenize();
    int variableCount = 0;
    for (const auto& token : tokens) {
        if (token.type == "variable") {
            variableCount++;
        }
    }
    EXPECT_GE(variableCount, 1);
}
TEST(main, test_tokenize_preserves_all_elenments_of_expression) {
    TPostfix postfix("a + 2 * b");
    auto tokens = postfix.tokenize();
    EXPECT_GE(tokens.size(), 3);
}
TEST(main, test_tokenize_handles_expressions_without_spaces) {
    TPostfix postfix("a+2*b");
    EXPECT_NO_THROW(postfix.tokenize());
    auto tokens = postfix.tokenize();
    EXPECT_FALSE(tokens.empty());
}
TEST(main, test_getPostfix_returns_non_empty_string) {
    TPostfix postfix("a + b * c");
    std::string postfixNotation = postfix.GetPostfix();
    EXPECT_FALSE(postfixNotation.empty());
}
TEST(main, test_getPostfix_returns_different_results_for_different_expressions) {
    TPostfix postfix1("a + b * c");
    TPostfix postfix2("(a + b) * c");
    std::string result1 = postfix1.GetPostfix();
    std::string result2 = postfix2.GetPostfix();
    EXPECT_NE(result1, result2);
}
TEST(main, test_getPostfix_format_uses_spaces_as_separators) {
    TPostfix postfix("a + b");
    std::string result = postfix.GetPostfix();
    EXPECT_NE(result.find(' '), std::string::npos);
}
TEST(main, test_calculate_throws_exception_for_invalid_expression_syntax) {
    TPostfix postfix("2 + + 3");
    EXPECT_THROW(postfix.calculate(), std::exception);
}
TEST(main, test_division_by_zero_throws_exception) {
    TPostfix postfix("5 / 0");
    EXPECT_THROW(postfix.calculate(), std::exception);
}
TEST(main, test_undefined_variable_in_expression_throws_exception) {
    TPostfix postfix("x + 1");
    EXPECT_THROW(postfix.calculate(), std::exception);
}
TEST(main, test_unmatched_parenthesis_throws_exception) {
    TPostfix postfix("(2 + 3");
    EXPECT_THROW(postfix.calculate(), std::exception);
}
TEST(main, test_power_operation_works_correctly) {
    TPostfix postfix("2^3 + 4 * 5");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 28.0);
}
TEST(main, test_power_with_parentheses_works_correctly) {
    TPostfix postfix("(a + b) ^ 2");
    postfix.SetVariable("a", 2.0);
    postfix.SetVariable("b", 3.0);
    EXPECT_DOUBLE_EQ(postfix.calculate(), 25.0);
}
TEST(main, test_getInfix_returns_original_expression) {
    std::string expression = "2 + 3 * 4";
    TPostfix postfix(expression);
    EXPECT_EQ(postfix.GetInfix(), expression);
}
TEST(main, test_getInfix_preserves_spacing_from_input) {
    std::string expression = "2 + 3 * 4";
    TPostfix postfix(expression);
    EXPECT_EQ(postfix.GetInfix(), expression);
}
TEST(main, test_getInfix_returns_empty_for_default_constructed_object) {
    TPostfix postfix;
    EXPECT_TRUE(postfix.GetInfix().empty());
}
TEST(main, test_complex_expression_with_all_operations_works) {
    TPostfix postfix("(a + b) * c - d / e ^ f");
    postfix.SetVariable("a", 1.0);
    postfix.SetVariable("b", 2.0);
    postfix.SetVariable("c", 3.0);
    postfix.SetVariable("d", 4.0);
    postfix.SetVariable("e", 2.0);
    postfix.SetVariable("f", 1.0);
    EXPECT_DOUBLE_EQ(postfix.calculate(), 7.0);
}
TEST(main, test_expression_with_multiple_variables_and_constants) {
    TPostfix postfix("3 * x + 2 * y - z / 4");
    postfix.SetVariable("x", 2.0);
    postfix.SetVariable("y", 3.0);
    postfix.SetVariable("z", 8.0);
    EXPECT_DOUBLE_EQ(postfix.calculate(), 10.0);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
