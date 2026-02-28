// #include <stdio.h>
// #include <stdlib.h>

// #define NAME_LENGTH 100
// #define DEFAULT_NUMBER_OF_TEST 10

// //// TYPES STRUCTURES ////

// // Pointeur sur une fonction de test
// typedef void (*TestFunction)();

// // Type structuré "Test" qui exécute une fonction de test
// typedef struct {
//     TestFunction function;
//     char name[NAME_LENGTH];
// } Test;

// // Type structure "TestRunner" qui exécute tout les "Test"
// typedef struct {
//     Test *tests;
//     size_t size;
//     size_t capacity;
// } TestsRunner;

// ////

// //// INSTANCE DE TESTS_RUNNER /////

// static TestsRunner tr = {.tests = NULL, .size = 0, .capacity = DEFAULT_NUMBER_OF_TEST};

// ////

// //// FONCTIONS DE TESTS_RUNNER /////

// // void tests_runner_initialize(TestsRunner *tr, size_t n) {
// //     tr->capacity = n;
// //     tr->size = 0;
// //     tr->tests = malloc(sizeof(Test) * n);
// // }

// // void tests_runner_add(TestsRunner *tr, Test test) {
// //     if (tr->size == tr->capacity) {
// //         tr->tests = realloc(tr->tests, tr->capacity + DEFAULT_NUMBER_OF_TEST);
// //         if (tr->tests == NULL) {
// //             printf("Error : Reallocation failed (in tests_runner_add)\n");
// //             exit(EXIT_FAILURE);
// //         }
// //         tr->capacity += DEFAULT_NUMBER_OF_TEST;
// //     }

// //     tr->tests[tr->size++] = test;
// // }

// void tests_runner_add(Test test) {
//     if (tr.size == tr.capacity) {
//         tr.tests = realloc(tr.tests, sizeof(Test) * (tr.capacity + DEFAULT_NUMBER_OF_TEST));
//         if (tr.tests == NULL) {
//             printf("Error : Reallocation failed (in tests_runner_add)\n");
//             exit(EXIT_FAILURE);
//         }
//         tr.capacity += DEFAULT_NUMBER_OF_TEST;
//     }

//     tr.tests[tr.size++] = test;
// }

// // void tests_runner_delete(TestsRunner *tr) {
// //     free(tr->tests);
// // }

// // void run_tests(TestsRunner tr) {
// //     for (size_t i=0; i<tr.size; i++) {
// //         printf("TEST %lu : %s\n", i, tr.tests[i].name);
// //     }
// // }

// void run_tests() {
//     for (size_t i=0; i<tr.size; i++) {
//         printf("TEST %lu : %s\n", i, tr.tests[i].name);
//     }
//     free(tr.tests);
// }

// ////

// //// FONCTIONS DE TEST ////

// void fn1() {
//     // ...
// }

// void fn2() {
//     // ...
// }

// ////

// int main() {
//     printf("Programme.\n");

//     // TestsRunner t;
//     // tests_runner_initialize(&t, DEFAULT_NUMBER_OF_TEST);

//     Test t1 = {.name = "toto", .function = fn1};
//     Test t2 = {.name = "titi", .function = fn2};

//     // tests_runner_add(&t, t1);
//     // tests_runner_add(&t, t2);

//     // run_tests(t);
//     // tests_runner_delete(&t);

//     tests_runner_add(t1);
//     tests_runner_add(t2);
//     run_tests();

// }

#include "unit-test.h"

void fn() {
    EQUAL(1, 1);
    NOT_EQUAL(1, 2);
    LESS_THAN(1, 2);
    LESS_OR_EQUAL_THAN(2,2);
    BIGGER_THAN(3,2);
    BIGGER_OR_EQUAL_THAN(3,3);
}

void fn2() {
    TRUE(true);
    TRUE(false);
    FALSE(true);
    FALSE(false);
}

void fn3() {
    EQUAL_STR("toto", "titi");
    EQUAL_STR("toto", "toto");
}

void fn4() {
    EQUAL(1., 1.);
    NOT_EQUAL(1.2, 2);
    LESS_THAN(1.99, 2);
    LESS_OR_EQUAL_THAN(2, 2.);
    BIGGER_THAN(3.14, 2);
    BIGGER_OR_EQUAL_THAN(3.1, 3);
}

void fn5() {
    int tmp = 2;
    IS_NULL(&tmp);
    IS_NULL(NULL);
}

int main() {
    add_test(fn, "Entiers");
    add_test(fn4, "Flottants et Entiers");
    add_test(fn2, "Booléens");
    add_test(fn3, "Chaines de caractères");
    add_test(fn5, "Pointeurs");

    run_tests();
}