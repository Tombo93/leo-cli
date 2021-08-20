#include <stdlib.h>
#include <stdio.h>

#include "client.h"
#include "url_str_utils.h"
#include "list.h"
#include "ui.h"
#include "html_parser.h"

#define LEO_ITA_DEU_ADRESS "https://dict.leo.org/italienisch-deutsch/"

int main(int argc, char **argv)
{
    if (!validate_cmdline_input(argc, argv))
    {
        fprintf(stderr, "Input argument(s) not valid\n");
        return EXIT_FAILURE;
    }
    const char *url = generate_search_url(LEO_ITA_DEU_ADRESS, argv[1]);
    const char *response = perform_curl_init(url);
    str_list *vocab_list = str_list_init();

    /* Do something with the response */
    html_tidy_search(response, vocab_list);

    init_ui();
    print_vocab_list(vocab_list->vocabs, vocab_list->len, 3, 5);

    /* Clean up */
    exit_ui();
    perform_curl_cleanup();
    str_list_delete(vocab_list);

    return EXIT_SUCCESS;
}