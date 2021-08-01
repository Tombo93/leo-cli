#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>

#include "client.h"

typedef struct client
{
    CURL *curl;
    CURLcode res;
} client;

/* __________________ private functions __________________ */

static client *curl_setup_connection(const char *url)
{
    client *client = malloc(sizeof *client);
    CURL *curl;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        client->curl = curl;
        return client;
    }
    return NULL;
}

static CURLcode perform_get_request(client *client)
{
    client->res = curl_easy_perform(client->curl);
    if (client->res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(client->res));
    }
    return client->res;
}

static void perform_cleanup(client *client)
{
    curl_easy_cleanup(client->curl);
    curl_global_cleanup();
    free(client);
}

/* _______________________________________________________ */

CURLcode perform_search(const char *url)
{
    client *C = curl_setup_connection(url);
    CURLcode status = perform_get_request(C);
    perform_cleanup(C);
    return status;
}