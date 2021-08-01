#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

bool validate_cmdline_input(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error\nUsage: %s <search word>\n\n", argv[0]);
        return false;
    }
    return true;
}