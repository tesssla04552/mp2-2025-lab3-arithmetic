#include <gtest.h>
#include "arithmetic.h"
#include <sstream>
#include <string>
TEST(main, test_basic_arithmetic_operations) {
    TPostfix postfix1("2 + 3");
    EXPECT_NO_THROW(postfix1.calculate());
    EXPECT_DOUBLE_EQ(postfix1.calculate(), 5.0);
    TPostfix postfix2("10 - 4");
    EXPECT_DOUBLE_EQ(postfix2.calculate(), 6.0);
    TPostfix postfix3("3 * 4");
    EXPECT_DOUBLE_EQ(postfix3.calculate(), 12.0);
    TPostfix postfix4("15 / 3");
    EXPECT_DOUBLE_EQ(postfix4.calculate(), 5.0);
}
TEST(main, test_operator_precedence) {
    TPostfix postfix("2 + 3 * 4");
    EXPECT_DOUBLE_EQ(postfix.calculate(), 14.0);
    TPostfix postfix2("(2 + 3) * 4");
    EXPECT_DOUBLE_EQ(postfix2.calculate(), 20.0);
}
TEST(main, test_variable_handling) {
    TPostfix postfix("x * y - z");
    postfix.SetVariable("x", 4.0);
    postfix.SetVariable("y", 3.0);
    postfix.SetVariable("z", 5.0);
    EXPECT_DOUBLE_EQ(postfix.calculate(), 7.0);
}
TEST(main, test_tokenization) {
    TPostfix postfix("a + 2 * b");
    auto tokens = postfix.tokenize();
    EXPECT_FALSE(tokens.empty());
    bool hasVariable = false;
    for (const auto& token : tokens) {
        if (token.type == "variable") {
            hasVariable = true;
            break;
        }
    }
    EXPECT_TRUE(hasVariable);
}
TEST(main, test_get_postfix_notation) {
    TPostfix postfix("a + b * c");
    std::string postfixNotation = postfix.GetPostfix();
    EXPECT_FALSE(postfixNotation.empty());
}
TEST(main, test_error_handling) {
    TPostfix postfix("2 + + 3");
    EXPECT_THROW(postfix.calculate(), std::exception);
    TPostfix postfix2("5 / 0");
    EXPECT_THROW(postfix.calculate(), std::exception);
}
TEST(main, test_with_power_and_complex_operations) {
    TPostfix postfix1("2^3 + 4 * 5");
    EXPECT_DOUBLE_EQ(postfix1.calculate(), 28.0);
    TPostfix postfix2("(a + b) ^ 2");
    postfix2.SetVariable("a", 2.0);
    postfix2.SetVariable("b", 3.0);
    EXPECT_DOUBLE_EQ(postfix2.calculate(), 25.0);
}
TEST(main, test_get_infix_works) {
    std::string expression = "2 + 3 * 4";
    TPostfix postfix(expression);
    EXPECT_EQ(postfix.GetInfix(), expression);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
