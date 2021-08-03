#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

#include "ui.h"

bool validate_cmdline_input(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error\nUsage: %s <search word>\n\n", argv[0]);
        return false;
    }
    return true;
}

void init_ui()
{
    initscr();
    cbreak();
    noecho();
    clear();
}

void exit_ui()
{
    mvaddstr(LINES - 1, 0, "Press any key to quit");
    refresh();
    getch();
    endwin();
}

void print_vocab_list(const char **vocab_list, size_t n_vocab, int y_offset, int x_offset)
{
    for (size_t i = 0; i < n_vocab; i++, y_offset++)
    {
        mvaddstr(y_offset, x_offset, vocab_list[i]);
    }
    refresh();
}