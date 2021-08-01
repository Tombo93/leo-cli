#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "client.h"
#include "url_utils.h"
#include "ui.h"

#define LEO_ITA_DEU_ADRESS "https://dict.leo.org/italienisch-deutsch/"

int main(int argc, char **argv)
{
    if (!validate_cmdline_input(argc, argv))
    {
        fprintf(stderr, "Input argument was not valid\n");
        return EXIT_FAILURE;
    }
    const char *url = generate_search_url(LEO_ITA_DEU_ADRESS, argv[1]);

    CURLcode response = perform_search(url);

    printf("\n\nResponse statuscode: %d\n", response);

    return EXIT_SUCCESS;
}