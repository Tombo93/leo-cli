#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#include "client.h"

typedef struct myhtml
{
    char *data;
    size_t size;
} myhtml;

static CURL *curl;

static size_t write_html(char *buffer, size_t size, size_t nmemb, void *dataptr)
{
    size_t realsize = size * nmemb;
    myhtml *html_p = (myhtml *)dataptr;

    char *ptr = realloc(html_p->data, html_p->size + realsize + 1);
    if (ptr == NULL)
        return 0; /* out of memory! */
    html_p->data = ptr;

    memcpy(&(html_p->data[html_p->size]), buffer, realsize);
    html_p->size += realsize;
    html_p->data[html_p->size] = 0;

    return realsize;
}

const char *perform_curl_init(const char *url)
{
    myhtml *response = malloc(sizeof *response);
    CURLcode res_code;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_html);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res_code = curl_easy_perform(curl);
        if (res_code != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res_code));
        }

        const char *data = (const char *)response->data;
        free(response);
        return data;
    }

    free(response);
    return NULL;
}

void perform_curl_cleanup()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
