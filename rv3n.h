#ifndef RV3N_H
#define RV3N_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

//// INFORMATIONS DES TEST ////

#define DEFAULT_NUMBER_OF_TEST 10

////

//// COULEURS ASCII ////

#define COLOR_RESET "\x1b[0m"

#define COLOR_RED_BOLD "\e[1;31m"
#define COLOR_GREEN_BOLD "\e[1;32m"
#define COLOR_WHITE "\e[0;37m"
#define COLOR_WHITE_BOLD "\e[1;37m"

#define COLOR_WHITE_BOLD_BG_GREEN "\e[1;97;42m"
#define COLOR_WHITE_BOLD_BG_RED   "\e[1;97;41m"
#define COLOR_WHITE_BOLD_BG_GRAY  "\e[1;97;100m"

////

//// FONCTIONS AFFICHAGE ////

static inline void print_value_int(int x) { printf("%d", x); }
static inline void print_value_uint(unsigned int x) { printf("%u", x); }
static inline void print_value_long(long x) { printf("%ld", x); }
static inline void print_value_ulong(unsigned long x) { printf("%lu", x); }
static inline void print_value_float(double x) { printf("%f", x); }
static inline void print_value_double(double x) { printf("%lf", x); }
static inline void print_value_str(char *x) { printf("%s", x); }
static inline void print_value_ptr(void *x) { printf("%p", x); }

#define PRINT_VALUE(x) _Generic((x),  \
    int: print_value_int,             \
    unsigned int: print_value_uint,   \
    long: print_value_long,           \
    unsigned long: print_value_ulong, \
    float: print_value_float,         \
    double: print_value_double,       \
    char *: print_value_str,          \
    void *: print_value_ptr,          \
    default: print_value_ptr)((x))

//// FONCTIONS ASSERT ////

// NOMBRES

#define ASSERT_EQUAL(x, y) {                                                      \
    assertions->assertions_total++;                                               \
    if (x != y) {                                                                 \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" != ");                                                           \
        PRINT_VALUE(y);                                                           \
        printf(" (expected x == y)%s\n", COLOR_RESET);                            \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_NOT_EQUAL(x, y) {                                                  \
    assertions->assertions_total++;                                               \
    if (x == y) {                                                                 \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" == ");                                                           \
        PRINT_VALUE(y);                                                           \
        printf(" (expected x != y)%s\n", COLOR_RESET);                            \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_LESS_THAN(x, y) {                                                  \
    assertions->assertions_total++;                                               \
    if (x >= y) {                                                                 \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" >= ");                                                           \
        PRINT_VALUE(y);                                                           \
        printf(" (expected x < y)%s\n", COLOR_RESET);                             \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_GREATER_THAN(x, y) {                                               \
    assertions->assertions_total++;                                               \
    if (x <= y) {                                                                 \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" <= ");                                                           \
        PRINT_VALUE(y);                                                           \
        printf("(expected x > y)%s\n", COLOR_RESET);                              \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_LESS_OR_EQUAL_THAN(x, y) {                                         \
    assertions->assertions_total++;                                               \
    if (x > y) {                                                                  \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" > ");                                                            \
        PRINT_VALUE(y);                                                           \
        printf("(expected x <= y)%s\n", COLOR_RESET);                             \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_GREATER_OR_EQUAL_THAN(x, y) {                                      \
    assertions->assertions_total++;                                               \
    if (x < y) {                                                                  \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" < ");                                                            \
        PRINT_VALUE(y);                                                           \
        printf("(expected x >= y)%s\n", COLOR_RESET);                             \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

// BOOLEENS

#define ASSERT_TRUE(x) {                                                                                                          \
    assertions->assertions_total++;                                                                                               \
    if (x == false) {                                                                                                             \
        printf("%sN°%u FAILED : x == false (expected x == true)%s\n", COLOR_RED_BOLD, assertions->assertions_total, COLOR_RESET); \
        assertions->test_failed = true;                                                                                           \
    }                                                                                                                             \
    else {                                                                                                                        \
        assertions->assertions_passed++;                                                                                          \
    }                                                                                                                             \
}

#define ASSERT_FALSE(x) {                                                                                                         \
    assertions->assertions_total++;                                                                                               \
    if (x == true) {                                                                                                              \
        printf("%sN°%u FAILED : x == true (expected x == false)%s\n", COLOR_RED_BOLD, assertions->assertions_total, COLOR_RESET); \
        assertions->test_failed = true;                                                                                           \
    }                                                                                                                             \
    else {                                                                                                                        \
        assertions->assertions_passed++;                                                                                          \
    }                                                                                                                             \
}

// CHAINES DE CARACTERES

#define ASSERT_EQUAL_STR(x, y) {                                                                                                               \
    assertions->assertions_total++;                                                                                                            \
    bool isEqual = true;                                                                                                                       \
    size_t i = 0;                                                                                                                              \
    while (isEqual && x[i] != '\0') {                                                                                                          \
        if (x[i] != y[i] || x[i] == '\0') {                                                                                                    \
            printf("%sN°%u FAILED : \"%s\" != \"%s\" (expected x == y)%s\n", COLOR_RED_BOLD, assertions->assertions_total, x, y, COLOR_RESET); \
            isEqual = false;                                                                                                                   \
            assertions->test_failed = true;                                                                                                    \
        }                                                                                                                                      \
        i++;                                                                                                                                   \
    }                                                                                                                                          \
    if (isEqual) {                                                                                                                             \
        assertions->assertions_passed++;                                                                                                       \
    }                                                                                                                                          \
}

#define ASSERT_NOT_EQUAL_STR(x, y) {                                                                                                       \
    assertions->assertions_total++;                                                                                                        \
    size_t i = 0;                                                                                                                          \
    while (x[i] != '\0' && y[i] != '\0' && x[i] == y[i]) {                                                                                 \
        i++;                                                                                                                               \
    }                                                                                                                                      \
    if (x[i] == y[i]) {                                                                                                                    \
        printf("%sN°%u FAILED : \"%s\" == \"%s\" (expected x != y)%s\n", COLOR_RED_BOLD, assertions->assertions_total, x, y, COLOR_RESET); \
        assertions->test_failed = true;                                                                                                    \
    }                                                                                                                                      \
    else {                                                                                                                                 \
        assertions->assertions_passed++;                                                                                                   \
    }                                                                                                                                      \
}

// AUTRES

#define ASSERT_NULL(x) {                                                          \
    assertions->assertions_total++;                                               \
    if (x != NULL) {                                                              \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" != NULL (expected x == NULL)%s\n", COLOR_RESET);                 \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
}

#define ASSERT_NOT_NULL(x) {                                                      \
    assertions->assertions_total++;                                               \
    if (x == NULL) {                                                              \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, assertions->assertions_total); \
        PRINT_VALUE(x);                                                           \
        printf(" == NULL (expected x != NULL)%s\n", COLOR_RESET);                 \
        assertions->test_failed = true;                                           \
    }                                                                             \
    else {                                                                        \
        assertions->assertions_passed++;                                          \
    }                                                                             \
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
    printf("%srv3n%s, a minimal unit test utility to rapidly test your app !%s\n", COLOR_WHITE_BOLD, COLOR_WHITE, COLOR_RESET);

    assertions = mmap(NULL, sizeof(AssertionsCount), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

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
                printf("%s > FAILED %d/%d %s\n", COLOR_WHITE_BOLD_BG_RED, assertions->assertions_passed, assertions->assertions_total, COLOR_RESET);
                exit(EXIT_FAILURE);
            }
            else {
                printf("%s > PASSED %d/%d %s\n", COLOR_WHITE_BOLD_BG_GREEN, assertions->assertions_passed, assertions->assertions_total, COLOR_RESET);
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

    printf("\n%s--- SUMMARY ---%s\n", COLOR_WHITE_BOLD_BG_GRAY, COLOR_RESET);
    printf("%sTOTAL  : %u%s\n", COLOR_WHITE_BOLD, passed + failed, COLOR_RESET);
    printf("%sPASSED : %u%s\n", COLOR_GREEN_BOLD, passed, COLOR_RESET);
    printf("%sFAILED : %u%s\n", COLOR_RED_BOLD, failed, COLOR_RESET);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                    (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("%sELAPSED TIME : %.9f s%s\n", COLOR_WHITE_BOLD, elapsed, COLOR_RESET);
    free(tests);
}

#endif