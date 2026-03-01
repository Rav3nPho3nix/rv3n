#ifndef RV3N_H
#define RV3N_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//// INFORMATIONS DES TEST ////

#define DEFAULT_NUMBER_OF_TEST 10

////

//// COULEURS ASCII ////

#define COLOR_RESET "\x1b[0m"

#define COLOR_RED_BOLD "\e[1;31m"
#define COLOR_GREEN_BOLD "\e[1;32m"
#define COLOR_WHITE "\e[0;37m"
#define COLOR_WHITE_BOLD "\e[1;37m"
#define COLOR_GRAY_BOLD "\e[1;90m"

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

////

//// FONCTIONS EXCEPT ////

// EVALUATION

#define _EXPECT_EVAL(condition) ({         \
    bool _passed = (condition);            \
    tests_count->local_tests_total++;      \
    if (_passed)                           \
        tests_count->local_tests_passed++; \
    else                                   \
        tests_count->test_failed = true;   \
    _passed;                               \
})

// NOMBRES

// La verification sur 'tests_count == NULL' nous permet de ne rien faire 
// si on appelle EXPECT_xx en dehors d'une suite de tests
#define EXPECT_EQUAL(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) == (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x);                                                                 \
        printf(" != ");                                                                 \
        PRINT_VALUE(y);                                                                 \
        printf(" (expected x == y)%s\n", COLOR_RESET);      \
    } \
} while(0)

#define EXPECT_NOT_EQUAL(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) != (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" == "); PRINT_VALUE(y); \
        printf(" (expected x != y)%s\n", COLOR_RESET); \
    } \
} while(0)

#define EXPECT_LESS_THAN(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) < (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" >= "); PRINT_VALUE(y); \
        printf(" (expected x < y)%s\n", COLOR_RESET); \
    } \
} while(0)

#define EXPECT_GREATER_THAN(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) > (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" <= "); PRINT_VALUE(y); \
        printf(" (expected x > y)%s\n", COLOR_RESET); \
    } \
} while(0)

#define EXPECT_LESS_OR_EQUAL_THAN(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) <= (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" > "); PRINT_VALUE(y); \
        printf(" (expected x <= y)%s\n", COLOR_RESET); \
    } \
} while(0)

#define EXPECT_GREATER_OR_EQUAL_THAN(x, y) do { \
    if (tests_count && !_EXPECT_EVAL((x) >= (y))) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" < "); PRINT_VALUE(y); \
        printf(" (expected x >= y)%s\n", COLOR_RESET); \
    } \
} while(0)

// BOOLEENS

#define EXPECT_TRUE(x) do { \
    if (tests_count && !_EXPECT_EVAL((x) == true)) \
        printf("%sN°%u FAILED : x == false (expected x == true)%s\n", COLOR_RED_BOLD, tests_count->local_tests_total, COLOR_RESET); \
} while(0)

#define EXPECT_FALSE(x) do { \
    if (tests_count && !_EXPECT_EVAL((x) == false)) \
        printf("%sN°%u FAILED : x == true (expected x == false)%s\n", COLOR_RED_BOLD, tests_count->local_tests_total, COLOR_RESET); \
} while(0)

// CHAINES DE CARACTERES

#define EXPECT_EQUAL_STR(x, y) do { \
    if (tests_count && !_EXPECT_EVAL(strcmp((x), (y)) == 0)) \
        printf("%sN°%u FAILED : \"%s\" != \"%s\" (expected x == y)%s\n", COLOR_RED_BOLD, tests_count->local_tests_total, x, y, COLOR_RESET); \
} while(0)

#define EXPECT_NOT_EQUAL_STR(x, y) do { \
    if (tests_count && !_EXPECT_EVAL(strcmp((x), (y)) != 0)) \
        printf("%sN°%u FAILED : \"%s\" == \"%s\" (expected x != y)%s\n", COLOR_RED_BOLD, tests_count->local_tests_total, x, y, COLOR_RESET); \
} while(0)

// POINTEURS

#define EXPECT_NULL(x) do { \
    if (tests_count && !_EXPECT_EVAL((x) == NULL)) { \
        printf("%sN°%u FAILED : ", COLOR_RED_BOLD, tests_count->local_tests_total); \
        PRINT_VALUE(x); printf(" != NULL (expected x == NULL)%s\n", COLOR_RESET); \
    } \
} while(0)

#define EXPECT_NOT_NULL(x) do { \
    if (tests_count && !_EXPECT_EVAL((x) != NULL)) \
        printf("%sN°%u FAILED : x == NULL (expected x != NULL)%s\n", COLOR_RED_BOLD, tests_count->local_tests_total, COLOR_RESET); \
} while(0)

////

//// TYPES STRUCTURES ////

typedef void (*SuiteFonction)();

typedef struct {
    SuiteFonction function;
    char *name;
} Test;

typedef struct {
    unsigned local_tests_passed;
    unsigned local_tests_total;
    unsigned global_tests_passed;
    unsigned global_tests_total;
    bool test_failed;
} TestsCount;

////

//// VARIABLES ////

size_t size = 0;
size_t capacity = 0;
unsigned suites_passed = 0;
unsigned suites_failed = 0;
Test *tests = NULL;
TestsCount *tests_count = NULL;

////

void add_suite(SuiteFonction function, char *name) {
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

    tests_count = mmap(NULL, sizeof(TestsCount), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    tests_count->global_tests_passed = 0;
    tests_count->global_tests_total  = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t i=0; i<size; i++) {
        printf("\n%s--- SUITE %lu : %s ---%s\n", COLOR_WHITE, i+1, tests[i].name, COLOR_RESET);
        
        tests_count->test_failed = false;
        tests_count->local_tests_passed = 0;
        tests_count->local_tests_total  = 0;

        pid_t p;
        // Nous sommes dans le processus fils
        if ((p = fork()) == 0) {
            tests[i].function();

            free(tests);

            tests_count->global_tests_total += tests_count->local_tests_total;
            tests_count->global_tests_passed += tests_count->local_tests_passed;
            if (tests_count->test_failed) {
                printf("%s > FAILED %d/%d %s\n", COLOR_WHITE_BOLD_BG_RED, tests_count->local_tests_passed, tests_count->local_tests_total, COLOR_RESET);
                exit(EXIT_FAILURE);
            }
            else {
                printf("%s > PASSED %d/%d %s\n", COLOR_WHITE_BOLD_BG_GREEN, tests_count->local_tests_passed, tests_count->local_tests_total, COLOR_RESET);
                exit(EXIT_SUCCESS);
            }
        }
        // Nous sommes dans le processus pere
        else {
            int res;
            wait(&res);

            // Verifie la valeur de sortie
            if (res == 0) {
                suites_passed++;
            }
            else {
                suites_failed++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    const double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\n%s --- SUMMARY --- %s\n", COLOR_WHITE_BOLD_BG_GRAY, COLOR_RESET);

    const unsigned max_total = (suites_passed + suites_failed > tests_count->global_tests_total) ? suites_passed + suites_failed : tests_count->global_tests_total;
    const int width = snprintf(NULL, 0, "%u", max_total);

    printf("%s[SUITES]   TOTAL %*u | %s%*u PASSED %s| %s%*u FAILED%s\n", COLOR_WHITE_BOLD, width, suites_passed + suites_failed, COLOR_GREEN_BOLD, width, suites_passed, COLOR_WHITE_BOLD, COLOR_RED_BOLD, width, suites_failed, COLOR_RESET);
    printf("%s[TESTS]    TOTAL %*u | %s%*u PASSED %s| %s%*u FAILED%s\n", COLOR_WHITE_BOLD, width, tests_count->global_tests_total, COLOR_GREEN_BOLD, width, tests_count->global_tests_passed, COLOR_WHITE_BOLD, COLOR_RED_BOLD, width, tests_count->global_tests_total - tests_count->global_tests_passed, COLOR_RESET);
    printf("%s[ELAPSED] %*.9lf s%s\n", COLOR_GRAY_BOLD, width + 10, elapsed, COLOR_RESET);
    free(tests);
    tests = NULL;
    tests_count = NULL;
}

#endif