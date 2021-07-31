#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

int tests_run = 0;

static char *test_ui()
{
    mu_assert("Error, 6 != 7", 7 == 7);
    return EXIT_SUCCESS;
}

static char *test_client()
{
    mu_assert("Error, 6 != 7", 6 == 7);
    return EXIT_SUCCESS;
}

static char *all_tests()
{
    mu_run_test(test_ui);
    mu_run_test(test_client);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *result = all_tests();
    if (result != NULL)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != NULL;
}