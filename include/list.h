#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct str_list
{
    const char **vocabs;
    size_t len;
} str_list;

str_list *str_list_init();
void str_list_add(str_list *, const char *);
void str_list_delete(str_list *);

#endif