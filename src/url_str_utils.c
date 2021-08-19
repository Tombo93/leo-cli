#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool validate_cmdline_input(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error\nUsage: %s <search word>\n\n", argv[0]);
        return false;
    }
    return true;
}

const char *generate_search_url(const char *site, const char *search_term)
{
    size_t len_site = strlen(site);
    size_t len_search = strlen(search_term);
    char *url = malloc(len_site + len_search + 1);

    memcpy(url, site, len_site);
    memcpy(url + len_site, search_term, len_search);

    return (const char *)url;
}

size_t append_str_to_arr(const char *str, const char **arr, size_t arr_size)
{
    arr = realloc(arr, arr_size + 1);
    if (arr != NULL)
    {
        // memcpy(arr[arr_size], str, strlen(str) + 1);
        arr[arr_size] = str;
        return arr_size + 1;
    }
    return 0;
}

void free_str_arr(const char **str_arr)
{
    int i = 0;
    const char *str;
    while ((str = str_arr[i]) != NULL)
    {
        free((void *)str);
        i++;
    }
    free(str_arr);
}