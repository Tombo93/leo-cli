#ifndef CLIENT_H
#define CLIENT_H

#include <curl/curl.h>

const char *perform_curl_init(const char *url);
void perform_cleanup();

#endif