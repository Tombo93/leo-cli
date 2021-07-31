#include <stdlib.h>
#include <stdio.h>

#include "client.h"
#include "ui.h"

int main(int argc, char **argv)
{
    validate_cmdline_input(argc, argv);
    client *C = curl_setup_connection("https://dict.leo.org/italienisch-deutsch/");
    CURLcode status = perform_get_request(C);
    perform_cleanup(C);
    printf("Response statuscode: %d", status);

    return EXIT_SUCCESS;
}