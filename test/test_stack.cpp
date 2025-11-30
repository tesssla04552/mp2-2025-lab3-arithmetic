// тесты для стека
#include "stack.h"
#include <gtest.h>
TEST(TStack, test_of_constructor_and_basic_properties) {
	TStack<int> stack(5);
	EXPECT_TRUE(stack.isEmpty());
	EXPECT_FALSE(stack.isFull());
	EXPECT_EQ(stack.GetSize(), 0);
	EXPECT_EQ(stack.GetCapacity(), 5);
}
TEST(TStack, test_element_addition) {
	TStack<int> stack(3);
	stack.push(10);
	EXPECT_FALSE(stack.isEmpty());
	EXPECT_EQ(stack.GetSize(), 1);
	stack.push(20);
	stack.push(30);
	EXPECT_EQ(stack.GetSize(), 3);
	EXPECT_TRUE(stack.isFull());
}
TEST(TStack, test_element_extraction) {
	TStack<int> stack(3);
	stack.push(10);
	stack.push(20);
	stack.push(30);
	EXPECT_EQ(stack.pop(), 30);
	EXPECT_EQ(stack.pop(), 20);
	EXPECT_EQ(stack.pop(), 10);
	EXPECT_TRUE(stack.isEmpty());
}
TEST(TStack, test_top_elem_viewing) {
	TStack<std::string> stack(3);
	stack.push("first");
	EXPECT_EQ(stack.peek(), "first");
}
TEST(TStack, test_autosize_increase) {
	TStack<int> stack(2);
	stack.push(1);
	stack.push(2);
	EXPECT_TRUE(stack.isFull());
	stack.push(3);
	EXPECT_FALSE(stack.isFull());
	EXPECT_GT(stack.GetCapacity(), 2);
	EXPECT_EQ(stack.GetSize(), 3);
}
TEST(TStack, test_stack_cleanup) {
	TStack<int> stack(5);
	stack.push(100);
	stack.push(200);
	stack.push(300);
	EXPECT_EQ(stack.GetSize(), 3);
	stack.clear();
	EXPECT_TRUE(stack.isEmpty());
	EXPECT_EQ(stack.GetSize(), 0);
	stack.push(400);
	EXPECT_EQ(stack.GetSize(), 1);
	EXPECT_EQ(stack.pop(), 400);
}
TEST(TStack, test_error_handling) {
	TStack<int> stack(2);
	EXPECT_THROW(stack.pop(), std::underflow_error);
	EXPECT_THROW(stack.peek(), std::underflow_error);
	EXPECT_THROW(TStack<int> invalidStack(-1), std::invalid_argument);
	EXPECT_THROW(TStack<int> zeroStack(0), std::invalid_argument);
}
TEST(TStack, test_with_different_data_types) {
	TStack<double> doubleStack(3);
	doubleStack.push(3.14);
	doubleStack.push(2.71);
	EXPECT_DOUBLE_EQ(doubleStack.pop(), 2.71);
	EXPECT_DOUBLE_EQ(doubleStack.pop(), 3.14);
	TStack<std::string> stringStack(2);
	stringStack.push("hello");
	stringStack.push("world");
	EXPECT_EQ(stringStack.pop(), "world");
	EXPECT_EQ(stringStack.pop(), "hello");
}
TEST(TStack, test_copy) {
	TStack<int>	originalStack(3);
	originalStack.push(1);
	originalStack.push(2);
	originalStack.push(3);
	TStack<int> copyStack(originalStack);
	EXPECT_EQ(copyStack.GetSize(), originalStack.GetSize());
	EXPECT_EQ(copyStack.pop(), 3);
	EXPECT_EQ(copyStack.pop(), 2);
	EXPECT_EQ(copyStack.pop(), 1);
	EXPECT_EQ(originalStack.GetSize(), 3);
}
TEST(TStack, test_assignment) {
	TStack<int>	originalStack(3);
	originalStack.push(1);
	originalStack.push(2);
	originalStack.push(3);
	TStack<int> assigned(1);
	assigned = originalStack;
	EXPECT_EQ(assigned.GetSize(), originalStack.GetSize());
	EXPECT_EQ(assigned.pop(), 3);
	EXPECT_EQ(assigned.pop(), 2);
	EXPECT_EQ(assigned.pop(), 1);
}


