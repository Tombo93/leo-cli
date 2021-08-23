#ifndef URL_STR_UTILS_H
#define URL_STR_UTILS_H

#include <stdlib.h>
#include <stdbool.h>

bool validate_cmdline_input(int argc, char **argv);

const char *generate_search_url(const char *site, const char *search_term);

size_t append_str_to_arr(const char *str, const char **arr, size_t arr_size);

void free_str_arr(const char **);

#endif