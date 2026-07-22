#include "rv3n.h"

void fn()
{
    EXPECT_EQUAL(1, 1);
    EXPECT_NOT_EQUAL(1, 2);
    EXPECT_LESS_THAN(1, 2);
    EXPECT_LESS_OR_EQUAL_THAN(2, 2);
    EXPECT_GREATER_THAN(3, 2);
    EXPECT_GREATER_OR_EQUAL_THAN(3, 3);
}

void fn2()
{
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

void fn3()
{
    EXPECT_EQUAL_STR("toto", "toto");
    EXPECT_NOT_EQUAL_STR("toto", "titi");
    EXPECT_NOT_EQUAL_STR("toto", "totot");
    EXPECT_NOT_EQUAL_STR("tot", "toto");
    EXPECT_NOT_EQUAL_STR("tot", "toto");
}

void fn4()
{
    EXPECT_EQUAL(1., 1.);
    EXPECT_NOT_EQUAL(1.2, 2);
    EXPECT_NOT_EQUAL(1.2, 1.2);
    EXPECT_LESS_THAN(1.99, 2);
    EXPECT_LESS_OR_EQUAL_THAN(2, 2.);
    EXPECT_GREATER_THAN(3.14, 2);
    EXPECT_GREATER_OR_EQUAL_THAN(3.1, 3);
}

void fn5()
{
    int tmp = 2;
    EXPECT_NULL(NULL);
    EXPECT_NOT_NULL(&tmp);
    EXPECT_NOT_NULL(NULL);
}

int main()
{
    add_suite(fn, "Entiers");
    add_suite(fn4, "Flottants et Entiers");
    add_suite(fn2, "Booléens");
    add_suite(fn3, "Chaines de caractères");
    add_suite(fn5, "Pointeurs");

    // Pas execute
    EXPECT_EQUAL(1, 1);
    EXPECT_EQUAL(1, 2);

    // Stoppe le programme
    ASSERT_EQUAL(2, 3);
    
    run_tests();
}