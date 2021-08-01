#include <stdlib.h>
#include <string.h>

const char *generate_search_url(const char *site, const char *search_term)
{
    size_t len_site = strlen(site);
    size_t len_search = strlen(search_term);
    char *url = malloc(len_site + len_search + 1);

    memcpy(url, site, len_site);
    memcpy(url + len_site, search_term, len_search);

    return (const char *)url;
}