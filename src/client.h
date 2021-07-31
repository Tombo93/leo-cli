#ifndef CLIENT_H
#define CLIENT_H

#include <curl/curl.h>

typedef struct client
{
    CURL *curl;
    CURLcode res;
} client;

client *curl_setup_connection(const char *);
CURLcode perform_get_request(client *);
void perform_cleanup(client *);

#endif