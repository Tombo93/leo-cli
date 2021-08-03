/*
    Example from https://www.html-tidy.org/developer/
*/
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>
#include <stdio.h>
#include <errno.h>

#include "html_parser.h"

int html_tidy(const char *input)
{
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int rc = -1;
    Bool ok;

    TidyDoc tdoc = tidyCreate(); // Initialize "document"
    printf("Tidying input...\n");

    ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes); // Convert to XHTML
    if (ok)
        rc = tidySetErrorBuffer(tdoc, &errbuf); // Capture diagnostics
    if (rc >= 0)
        rc = tidyParseString(tdoc, input); // Parse the input
    if (rc >= 0)
        rc = tidyCleanAndRepair(tdoc); // Tidy it up!
    if (rc >= 0)
        rc = tidyRunDiagnostics(tdoc); // Kvetch
    if (rc > 1)                        // If error, force output.
        rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
    if (rc >= 0)
        rc = tidySaveBuffer(tdoc, &output); // Pretty Print

    if (rc >= 0)
    {
        if (rc > 0)
            printf("\nDiagnostics:\n\n%s", errbuf.bp);
        printf("\nEverything fine with Tidy.\nReady for processing...\n\n");
    }
    else
        printf("A severe error (%d) occurred.\n", rc);

    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    return rc;
}