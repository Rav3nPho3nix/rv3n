#include "unit-test.h"

void fn()
{
    ASSERT_EQUAL(1, 1);
    ASSERT_NOT_EQUAL(1, 2);
    ASSERT_LESS_THAN(1, 2);
    ASSERT_LESS_OR_EQUAL_THAN(2, 2);
    ASSERT_GREATER_THAN(3, 2);
    ASSERT_GREATER_OR_EQUAL_THAN(3, 3);
}

void fn2()
{
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

void fn3()
{
    ASSERT_EQUAL_STR("toto", "toto");
    ASSERT_NOT_EQUAL_STR("toto", "titi");
    ASSERT_NOT_EQUAL_STR("toto", "totot");
    ASSERT_NOT_EQUAL_STR("tot", "toto");
    ASSERT_NOT_EQUAL_STR("tot", "toto");
}

void fn4()
{
    ASSERT_EQUAL(1., 1.);
    ASSERT_NOT_EQUAL(1.2, 2);
    ASSERT_NOT_EQUAL(1.2, 1.2);
    ASSERT_LESS_THAN(1.99, 2);
    ASSERT_LESS_OR_EQUAL_THAN(2, 2.);
    ASSERT_GREATER_THAN(3.14, 2);
    ASSERT_GREATER_OR_EQUAL_THAN(3.1, 3);
}

void fn5()
{
    int tmp = 2;
    ASSERT_NULL(NULL);
    ASSERT_NOT_NULL(&tmp);
    ASSERT_NOT_NULL(NULL);
}

int main()
{
    add_test(fn, "Entiers");
    add_test(fn4, "Flottants et Entiers");
    add_test(fn2, "Booléens");
    add_test(fn3, "Chaines de caractères");
    add_test(fn5, "Pointeurs");

    run_tests();
}