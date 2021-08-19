#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <tidy/tidy.h>

void html_tidy_search(const char *html_str, const char **vocab_list, size_t size);

#endif