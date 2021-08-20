#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <tidy/tidy.h>
#include "list.h"

void html_tidy_search(const char *html_str, str_list *vocabs);

#endif