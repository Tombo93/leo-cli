#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>

#include "client.h"

client *curl_setup_connection(const char *adress)
{
    client *client = malloc(sizeof *client);
    CURL *curl;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, adress);

        client->curl = curl;
        return client;
    }
    return NULL;
}

CURLcode perform_get_request(client *client)
{
    client->res = curl_easy_perform(client->curl);
    if (client->res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(client->res));
    }
    return client->res;
}

void perform_cleanup(client *client)
{
    curl_easy_cleanup(client->curl);
    curl_global_cleanup();
    free(client);
}