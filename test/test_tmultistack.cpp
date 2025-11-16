#include <gtest.h>
#include "tmultistack.h"

TEST(TMultiStack, can_create_multistack)
{
    ASSERT_NO_THROW(TMultiStack<int> ms);
}

TEST(TMultiStack, can_create_multistack_with_positive_size_and_count)
{
    ASSERT_NO_THROW(TMultiStack<int> ms(20, 3));
}

TEST(TMultiStack, cant_create_too_large_multistack)
{
    ASSERT_ANY_THROW(TMultiStack<int> ms(MAX_MULTISTACK_SIZE + 1, 3));
}

TEST(TMultiStack, throws_when_create_multistack_with_negative_size)
{
    ASSERT_ANY_THROW(TMultiStack<int> ms(-5, 3));
}

TEST(TMultiStack, throws_when_create_multistack_with_negative_stack_count)
{
    ASSERT_ANY_THROW(TMultiStack<int> ms(10, -2));
}

TEST(TMultiStack, can_create_copied_multistack)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_NO_THROW(TMultiStack<int> ms1(ms));
}

TEST(TMultiStack, copied_multistack_has_same_size)
{
    TMultiStack<int> ms(10, 2);
    TMultiStack<int> ms2(ms);
    ASSERT_EQ(ms.GetSize(), ms2.GetSize());
}

TEST(TMultiStack, can_push_element_to_specific_stack)
{
    TMultiStack<int> ms(10, 3);
    ASSERT_NO_THROW(ms.Push(42, 1));
}

TEST(TMultiStack, can_pop_element_from_specific_stack)
{
    TMultiStack<int> ms(10, 3);
    ms.Push(42, 1);
    ASSERT_NO_THROW(ms.Pop(1));
}

TEST(TMultiStack, pop_returns_correct_element)
{
    TMultiStack<int> ms(10, 2);
    ms.Push(100, 0);
    ms.Push(200, 1);
    int elem1 = ms.Pop(0);
    int elem2 = ms.Pop(1);
    ASSERT_EQ(elem1, 100);
    ASSERT_EQ(elem2, 200);
}

TEST(TMultiStack, throws_when_push_to_invalid_stack_index)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_ANY_THROW(ms.Push(42, 5));
}

TEST(TMultiStack, throws_when_pop_from_invalid_stack_index)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_ANY_THROW(ms.Pop(5));
}

TEST(TMultiStack, throws_when_pop_from_empty_stack)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_ANY_THROW(ms.Pop(0));
}

TEST(TMultiStack, can_check_empty_specific_stack)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_TRUE(ms.IsEmpty(0));
}

TEST(TMultiStack, can_check_full_specific_stack)
{
    TMultiStack<int> ms(2, 2);
    ms.Push(1, 0);
    ms.Push(2, 0);
    ASSERT_TRUE(ms.IsFull(0));
}

TEST(TMultiStack, empty_stack_is_not_full)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_FALSE(ms.IsFull(0));
}

TEST(TMultiStack, full_stack_is_not_empty)
{
    TMultiStack<int> ms(1, 2);
    ms.Push(42, 0);
    ASSERT_FALSE(ms.IsEmpty(0));
}

TEST(TMultiStack, can_get_size)
{
    TMultiStack<int> ms(15, 3);
    ASSERT_EQ(ms.GetSize(), 15);
}

TEST(TMultiStack, can_access_stack_via_operator)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_NO_THROW(ms[0]);
    ASSERT_NO_THROW(ms[1]);
}



TEST(TMultiStack, throws_when_access_invalid_stack_via_operator)
{
    TMultiStack<int> ms(10, 2);
    ASSERT_ANY_THROW(ms[5]);
}

TEST(TMultiStack, can_create_moved_multistack)
{
    TMultiStack<int> ms1(10, 2);
    ms1.Push(1, 0);
    ASSERT_NO_THROW(TMultiStack<int> ms2(std::move(ms1)));
}

TEST(TMultiStack, moved_multistack_has_correct_state)
{
    TMultiStack<int> ms1(10, 2);
    ms1.Push(42, 0);
    ms1.Push(24, 1);
    TMultiStack<int> ms2(std::move(ms1));

    int elem1 = ms2.Pop(0);
    int elem2 = ms2.Pop(1);
    ASSERT_EQ(elem1, 42);
    ASSERT_EQ(elem2, 24);
}

TEST(TMultiStack, can_push_after_pop)
{
    TMultiStack<int> ms(5, 2);
    ms.Push(1, 0);
    ms.Push(2, 0);
    ms.Pop(0);
    ASSERT_NO_THROW(ms.Push(3, 0));
}

TEST(TMultiStack, multiple_push_pop_operations_on_different_stacks)
{
    TMultiStack<int> ms(10, 3);

    for (int stack = 0; stack < 3; stack++) {
        for (int i = 1; i <= 3; i++) {
            ms.Push(stack * 10 + i, stack);
        }
    }

    for (int stack = 2; stack >= 0; stack--) {
        for (int i = 3; i >= 1; i--) {
            int elem = ms.Pop(stack);
            ASSERT_EQ(elem, stack * 10 + i);
        }
    }
}

TEST(TMultiStack, can_handle_multiple_stacks_independently)
{
    TMultiStack<int> ms(12, 4);

    ms.Push(1, 0);
    ms.Push(2, 0);

    ms.Push(10, 1);
    ms.Push(20, 1);
    ms.Push(30, 1);

    ms.Push(100, 2);

    ASSERT_EQ(ms.Pop(0), 2);
    ASSERT_EQ(ms.Pop(1), 30);
    ASSERT_EQ(ms.Pop(2), 100);
    ASSERT_EQ(ms.Pop(0), 1);
    ASSERT_EQ(ms.Pop(1), 20);
    ASSERT_EQ(ms.Pop(1), 10);
}

TEST(TMultiStack, is_full_returns_false_when_other_stacks_have_space)
{
    TMultiStack<int> ms(6, 3);

    ms.Push(1, 0);
    ms.Push(2, 0);

    ASSERT_TRUE(ms.IsFull(0));
    ASSERT_FALSE(ms.IsFull(1));
    ASSERT_FALSE(ms.IsFull(2));
}

TEST(TMultiStack, can_create_large_multistack)
{
    ASSERT_NO_THROW(TMultiStack<int> ms(1000, 10));
}

TEST(TMultiStack, stack_count_is_correct)
{
    TMultiStack<int> ms(20, 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_NO_THROW(ms.Push(i * 10, i));
    }

    ASSERT_ANY_THROW(ms.Push(100, 5));
}

TEST(TMultiStack, memory_is_properly_distributed)
{
    TMultiStack<int> ms(9, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ASSERT_NO_THROW(ms.Push(i * 10 + j, i));
        }
    }

    for (int i = 0; i < 3; i++) {
        ASSERT_TRUE(ms.IsFull(i));
    }
}

TEST(TMultiStack, can_handle_consecutive_operations)
{
    TMultiStack<int> ms(10, 2);

    for (int i = 0; i < 5; i++) {
        ms.Push(i, 0);
        ms.Push(i * 10, 1);
    }

    for (int i = 4; i >= 0; i--) {
        ASSERT_EQ(ms.Pop(0), i);
        ASSERT_EQ(ms.Pop(1), i * 10);
    }

    ASSERT_TRUE(ms.IsEmpty(0));
    ASSERT_TRUE(ms.IsEmpty(1));
}

TEST(TMultiStack, can_use_different_data_types)
{
    ASSERT_NO_THROW(TMultiStack<double> ms(10, 2));
}

TEST(TMultiStack, repack_works_when_stack_is_full)
{
    TMultiStack<int> ms(6, 3);

    ms.Push(1, 0);
    ms.Push(2, 0);

    ASSERT_NO_THROW(ms.Push(3, 0));
}

TEST(TMultiStack, elements_preserved_after_repack)
{
    TMultiStack<int> ms(6, 2);

    ms.Push(10, 0);
    ms.Push(20, 0);
    ms.Push(30, 1);

    ms.Push(40, 0);

    ASSERT_EQ(ms.Pop(0), 40);
    ASSERT_EQ(ms.Pop(0), 20);
    ASSERT_EQ(ms.Pop(0), 10);
    ASSERT_EQ(ms.Pop(1), 30);
}

TEST(TMultiStack, can_get_stack_count_through_operations)
{
    TMultiStack<int> ms(12, 4);

    ASSERT_NO_THROW(ms[0]);
    ASSERT_NO_THROW(ms[1]);
    ASSERT_NO_THROW(ms[2]);
    ASSERT_NO_THROW(ms[3]);
    ASSERT_ANY_THROW(ms[4]);
}