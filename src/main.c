#include <stdlib.h>
#include <stdio.h>

#include "client.h"
#include "url_utils.h"
#include "ui.h"
#include "html_parser.h"

#define LEO_ITA_DEU_ADRESS "https://dict.leo.org/italienisch-deutsch/"

int main(int argc, char **argv)
{

    /* User input validation */
    if (!validate_cmdline_input(argc, argv))
    {
        fprintf(stderr, "Input argument(s) not valid\n");
        return EXIT_FAILURE;
    }

    /* URL handling */
    const char *url = generate_search_url(LEO_ITA_DEU_ADRESS, argv[1]);

    /* Init curl */
    const char *response = perform_curl_init(url);

    /* Do something with the response */
    html_tidy(response);

    /* Clean up curl */
    perform_cleanup();

    return EXIT_SUCCESS;
}