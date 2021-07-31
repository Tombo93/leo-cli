/* 
    MinUnit unit testing
    https://jera.com/techinfo/jtns/jtn002 
*/
#ifndef TESTS_H
#define TESTS_H

#define mu_assert(message, test) \
    do                           \
    {                            \
        if (!(test))             \
            return message;      \
    } while (0)

#define mu_run_test(test)       \
    do                          \
    {                           \
        char *message = test(); \
        tests_run++;            \
        if (message)            \
            return message;     \
    } while (0)

extern int tests_run;

#endif