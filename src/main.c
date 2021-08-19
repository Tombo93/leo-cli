#include <stdlib.h>
#include <stdio.h>

#include "client.h"
#include "url_str_utils.h"
#include "ui.h"
#include "html_parser.h"

#define LEO_ITA_DEU_ADRESS "https://dict.leo.org/italienisch-deutsch/"

// const char *example_vocab[] = {"testa", "abitare", "sforzare"};

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

    /*
        Init curl + request
        TODO:
            separate initiation and request
    */
    const char *response = perform_curl_init(url);

    /* Do something with the response */
    const char **vocabs = malloc(sizeof *vocabs);
    html_tidy_search(response, vocabs, 0);

    /* Clean up curl */
    perform_cleanup();

    init_ui();
    print_vocab_list(vocabs, 3, 3, 5);
    exit_ui();

    free_str_arr(vocabs);

    return EXIT_SUCCESS;
}