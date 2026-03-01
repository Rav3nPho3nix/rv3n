#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stddef.h>

//// INFORMATIONS DES TEST ////

#define DEFAULT_NUMBER_OF_TEST 10

////

//// COULEURS ASCII ////

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED_BOLD "\e[1;31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_GREEN_BOLD "\e[1;32m"
#define COLOR_WHITE "\e[0;37m"
#define COLOR_WHITE_BOLD "\e[1;37m"

////

//// FONCTIONS ASSERT ////

// NOMBRES

#define ASSERT_EQUAL(a, b) { \
    assertions->assertions_total++; \
    if (a != b) { \
        printf("%sFAILED : %d != %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_NOT_EQUAL(a, b) { \
    assertions->assertions_total++; \
    if (a == b) { \
        printf("%sFAILED : %d == %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_LESS_THAN(a, b) { \
    assertions->assertions_total++; \
    if (a >= b) { \
        printf("%sFAILED : %d >= %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_GREATER_THAN(a, b) { \
    assertions->assertions_total++; \
    if (a <= b) { \
        printf("%sFAILED : %d <= %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_LESS_OR_EQUAL_THAN(a, b) { \
    assertions->assertions_total++; \
    if (a > b) { \
        printf("%sFAILED : %d > %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_GREATER_OR_EQUAL_THAN(a, b) { \
    assertions->assertions_total++; \
    if (a < b) { \
        printf("%sFAILED : %d < %d%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

// BOOLEENS

#define ASSERT_TRUE(a) { \
    assertions->assertions_total++; \
    if (a == false) { \
        printf("%sFAILED : false%s\n", COLOR_RED_BOLD, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_FALSE(a) { \
    assertions->assertions_total++; \
    if (a == true) { \
        printf("%sFAILED : true%s\n", COLOR_RED_BOLD, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

// CHAINES DE CARACTERES

#define ASSERT_EQUAL_STR(a, b) { \
    assertions->assertions_total++; \
    bool isEqual = true; \
    size_t i = 0; \
    while (isEqual && a[i] != '\0') { \
        if (a[i] != b[i] || b[i] == '\0') { \
            printf("%sFAILED : \"%s\" != \"%s\"%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
            isEqual = false; \
            assertions->test_failed = true; \
        } \
        i++; \
    } \
    if (isEqual) { \
        assertions->assertions_passed++; \
    } \
}

#define ASSERT_NOT_EQUAL_STR(a, b) { \
    assertions->assertions_total++; \
    size_t i = 0; \
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) { \
        i++; \
    } \
    if (a[i] == b[i]) { \
        printf("%sFAILED : \"%s\" == \"%s\"%s\n", COLOR_RED_BOLD, a, b, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

// AUTRES

#define ASSERT_NULL(a) { \
    assertions->assertions_total++; \
    if (a != NULL) { \
        printf("%sFAILED : %p != NULL%s\n", COLOR_RED_BOLD, a, COLOR_RESET); \
        assertions->test_failed = true; \
    } \
    else { \
        assertions->assertions_passed++; \
    } \
}

////

//// TYPES STRUCTURES ////

typedef void (*TestFunction)();

typedef struct {
    TestFunction function;
    char *name;
} Test;

typedef struct {
    unsigned assertions_passed;
    unsigned assertions_total;
    bool test_failed;
} AssertionsCount;

////

//// VARIABLES ////

size_t size = 0;
size_t capacity = 0;
unsigned passed = 0;
unsigned failed = 0;
Test *tests = NULL;
AssertionsCount *assertions = NULL;

////

void add_test(TestFunction function, char *name) {
    if (size == capacity) {
        tests = realloc(tests, sizeof(Test) * (capacity + DEFAULT_NUMBER_OF_TEST));
        if (tests == NULL) {
            printf("%sSomething went wront with the reallocation.%s\n", COLOR_RED_BOLD, COLOR_RESET);
            exit(EXIT_FAILURE);
        }
        capacity += DEFAULT_NUMBER_OF_TEST;
    }

    tests[size].name = name;
    tests[size].function = function;
    size++;
}

void run_tests() {
    printf("%s[NOM]%s, a minimal unit test utility to rapidly test your app !%s\n", COLOR_WHITE_BOLD, COLOR_WHITE, COLOR_RESET);

    assertions = mmap(NULL, sizeof(AssertionsCount), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (size_t i=0; i<size; i++) {
        printf("\n%s--- TEST %lu : %s ---%s\n", COLOR_WHITE, i+1, tests[i].name, COLOR_RESET);
        
        assertions->test_failed = false;
        assertions->assertions_passed = 0;
        assertions->assertions_total = 0;

        pid_t p;
        // Nous sommes dans le processus fils
        if ((p = fork()) == 0) {
            tests[i].function();

            free(tests);

            if (assertions->test_failed) {
                printf("%s> FAILED %d/%d%s\n", COLOR_RED_BOLD, assertions->assertions_passed, assertions->assertions_total, COLOR_RESET);
                exit(EXIT_FAILURE);
            }
            else {
                printf("%s> PASSED %d/%d%s\n", COLOR_GREEN_BOLD, assertions->assertions_passed, assertions->assertions_total, COLOR_RESET);
                exit(EXIT_SUCCESS);
            }
        }
        // Nous sommes dans le processus pere
        else {
            int res;
            wait(&res);

            // Verifie la valeur de sortie
            if (res == 0) {
                passed++;
            }
            else {
                failed++;
            }
        }
    }

    printf("\n%s--- SUMMARY ---%s\n", COLOR_WHITE_BOLD, COLOR_RESET);
    printf("%sTOTAL  : %u%s\n", COLOR_WHITE_BOLD, passed + failed, COLOR_RESET);
    printf("%sPASSED : %u%s\n", COLOR_GREEN_BOLD, passed, COLOR_RESET);
    printf("%sFAILED : %u%s\n", COLOR_RED_BOLD, failed, COLOR_RESET);

    free(tests);
}

#endif