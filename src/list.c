#include <stdlib.h>
#include <stdio.h>

#include "list.h"

str_list *str_list_init()
{
    str_list *L = malloc(sizeof *L);
    L->vocabs = malloc(sizeof *L->vocabs);
    L->len = 0;
    return L;
}

void str_list_add(str_list *list, const char *str)
{
    printf("%ld, %s\n", list->len, str);
}

void str_list_delete(str_list *list)
{
    free(list->vocabs);
    free(list);
}