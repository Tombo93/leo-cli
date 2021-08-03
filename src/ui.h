#ifndef UI_H
#define UI_H

#include <curses.h>
#include <stdbool.h>

bool validate_cmdline_input(int argc, char **argv);

void init_ui();
void exit_ui();
void print_vocab_list(const char **vocab_list, size_t n_vocab, int y_offset, int x_offset);

#endif