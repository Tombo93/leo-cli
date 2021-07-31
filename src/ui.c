#include <curses.h>
#include <stdbool.h>

bool validate_cmdline_input(int argc, char **argv)
{
    printf("%s: %d", argv[0], argc);
    return false;
}