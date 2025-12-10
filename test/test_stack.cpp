// тесты для стека
#include "stack.h"
#include <gtest.h>
TEST(TStack, test_of_constructor_with_positive_capacity_creates_empty_stack) {
	TStack<int> stack(5);
	EXPECT_TRUE(stack.isEmpty());
}
TEST(TStack, test_new_stack_has_correct_capacity) {
	TStack<int> stack(10);
	EXPECT_EQ(stack.GetCapacity(), 10);
}
TEST(TStack, test_new_stack_has_zero_size) {
	TStack<int> stack(7);
	EXPECT_EQ(stack.GetSize(), 0);
}
TEST(TStack, test_new_stack_is_not_full) {
	TStack<int> stack(3);
	EXPECT_FALSE(stack.isFull());
}
TEST(TStack, test_push_increases_stack_size) {
	TStack<int> stack(3);
	stack.push(10);
	EXPECT_EQ(stack.GetSize(), 1);
}
TEST(TStack, test_push_changes_empty_state) {
	TStack<int> stack(3);
	stack.push(10);
	EXPECT_FALSE(stack.isEmpty());
}
TEST(TStack, test_multiple_pushes_fill_stack) {
	TStack<int> stack(3);
	stack.push(10);
	stack.push(20);
	stack.push(30);
	EXPECT_TRUE(stack.isFull());
}
TEST(TStack, test_pop_returns_last_pushed_element) {
	TStack<int> stack(3);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.pop(), 20);
}
TEST(TStack, test_pop_decreases_stack_size) {
	TStack<int> stack(3);
	stack.push(10);
	stack.push(20);
	stack.push(30);
	stack.pop();
	stack.pop();
	stack.pop();
	EXPECT_TRUE(stack.isEmpty());
}
TEST(TStack, test_pop_preserves_order_lifo) {
	TStack<int> stack(3);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	EXPECT_EQ(stack.pop(), 3);
	EXPECT_EQ(stack.pop(), 2);
	EXPECT_EQ(stack.pop(), 1);
}
TEST(TStack, test_peek_returns_top_element_without_removal) {
	TStack<std::string> stack(3);
	stack.push("first");
	stack.push("second");
	EXPECT_EQ(stack.peek(), "second");
}
TEST(TStack, test_peek_does_not_change_stack_size) {
	TStack<int> stack(3);
	stack.push(100);
	stack.peek();
	EXPECT_EQ(stack.GetSize(), 1);
}
TEST(TStack, test_push_triggers_resize_when_full) {
	TStack<int> stack(2);
	stack.push(1);
	stack.push(2);
	EXPECT_TRUE(stack.isFull());
	stack.push(3);
	EXPECT_FALSE(stack.isFull());
}
TEST(TStack, test_capacity_increases_after_resize) {
	TStack<int> stack(2);
	stack.push(1);
	stack.push(2);
	int oldCapacity = stack.GetCapacity();
	stack.push(3);
	EXPECT_GT(stack.GetCapacity(), oldCapacity);
}
TEST(TStack, test_all_elements_preserved_after_resize) {
	TStack<int> stack(2);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	EXPECT_EQ(stack.pop(), 3);
	EXPECT_EQ(stack.pop(), 2);
	EXPECT_EQ(stack.pop(), 1);
}
TEST(TStack, test_clear_resets_stack_size_to_zero) {
	TStack<int> stack(5);
	stack.push(100);
	stack.push(200);
	stack.clear();
	EXPECT_EQ(stack.GetSize(), 0);
}
TEST(TStack, test_clear_makes_stack_empty) {
	TStack<int> stack(5);
	stack.push(100);
	stack.clear();
	EXPECT_TRUE(stack.isEmpty());
}
TEST(TStack, test_stack_can_be_reused_after_clear) {
	TStack<int> stack(5);
	stack.push(100);
	stack.clear();
	stack.push(400);
	EXPECT_EQ(stack.pop(), 400);
}
TEST(TStack, test_pop_on_empty_stack_throws_underflow_error) {
	TStack<int> stack(2);
	EXPECT_THROW(stack.pop(), std::underflow_error);
}
TEST(TStack, test_peek_on_empty_stack_throws_underflow_error) {
	TStack<int> stack(2);
	EXPECT_THROW(stack.peek(), std::underflow_error);
}
TEST(TStack, test_constructor_with_negative_capacity_throws_invalid_argument) {
	EXPECT_THROW(TStack<int>(-1), std::invalid_argument);
}
TEST(TStack, test_constructor_with_zero_capacity_throws_invalid_argument) {
	EXPECT_THROW(TStack<int>(0), std::invalid_argument);
}
TEST(TStack, test_works_with_double_type) {
	TStack<double> doubleStack(3);
	doubleStack.push(3.14);
	EXPECT_DOUBLE_EQ(doubleStack.pop(), 3.14);
}
TEST(TStack, test_works_with_string_type) {
	TStack<std::string> stringStack(2);
	stringStack.push("hello");
	EXPECT_EQ(stringStack.pop(), "hello");
}
TEST(TStack, test_string_stack_maintains_lifo_order) {
	TStack<std::string> stringStack(2);
	stringStack.push("first");
	stringStack.push("second");
	EXPECT_EQ(stringStack.pop(), "second");
	EXPECT_EQ(stringStack.pop(), "first");
}
TEST(TStack, test_copy_constructor_creates_independent_stack) {
	TStack<int> original(3);
	original.push(1);
	original.push(2);
	original.push(3);
	TStack<int> copy(original);
	EXPECT_EQ(copy.GetSize(), original.GetSize());
}
TEST(TStack, test_copied_stack_contains_same_elements) {
	TStack<int> original(3);
	original.push(1);
	original.push(2);
	original.push(3);
	TStack<int> copy(original);
	EXPECT_EQ(copy.pop(), 3);
	EXPECT_EQ(copy.pop(), 2);
	EXPECT_EQ(copy.pop(), 1);
}
TEST(TStack, test_original_unchanged_after_copy_operations) {
	TStack<int> original(3);
	original.push(1);
	original.push(2);
	original.push(3);
	TStack<int> copy(original);
	copy.pop();
	copy.pop();
	EXPECT_EQ(original.GetSize(), 3);
}
TEST(TStack, test_copied_stack_has_same_capacity) {
	TStack<int> original(5);
	TStack<int> copy(original);
	EXPECT_EQ(copy.GetCapacity(), original.GetCapacity());
}
TEST(TStack, test_assignment_operator_copies_stack_correctly) {
	TStack<int> original(3);
	original.push(1);
	original.push(2);
	original.push(3);
	TStack<int> assigned(1);
	assigned = original;
	EXPECT_EQ(assigned.GetSize(), original.GetSize());
}
TEST(TStack, test_assigned_stack_contains_correct_elements) {
	TStack<int> original(3);
	original.push(1);
	original.push(2);
	original.push(3);
	TStack<int> assigned(1);
	assigned = original;
	EXPECT_EQ(assigned.pop(), 3);
	EXPECT_EQ(assigned.pop(), 2);
	EXPECT_EQ(assigned.pop(), 1);
}


