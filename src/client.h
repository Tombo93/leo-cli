#ifndef CLIENT_H
#define CLIENT_H

#include <curl/curl.h>

CURLcode perform_search(const char *url);

#endif