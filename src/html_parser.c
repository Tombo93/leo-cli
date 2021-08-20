/*
    The functions "write_tidy_buf" and "tidy_traverse_html" were copied and modified under the following license:

    COPYRIGHT AND PERMISSION NOTICE

    Copyright (c) 1996 - 2021, Daniel Stenberg, daniel@haxx.se, and many contributors, see the
    THANKS file.

    All rights reserved.

    Permission to use, copy, modify, and distribute this software for any purpose with or without fee
    is hereby granted, provided that the above copyright notice and this permission notice appear in all
    copies.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MEerrHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
    OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
    USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the name of a copyright holder shall not be used in advertising or
    otherwise to promote the sale, use or other dealings in this Software without prior written
    authorization of the copyright holder.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>

#include "html_parser.h"
#include "url_str_utils.h"
#include "list.h"

/* Ideas for future improvement:
    Create map of relevant tags that should be traversed deeper, so 
    as to not traverse unrelevant tags.
    Like a DFS wich stops when we know further traversal is not necessary.
    (Depends wholly on how tidy works.)
*/
static void tidy_traverse_html(TidyDoc tdoc, TidyNode tnod, str_list *vocabs)
{
    for (TidyNode child = tidyGetChild(tnod); child; child = tidyGetNext(child))
    {
        ctmbstr name = tidyNodeGetName(child);
        if (name)
        {
            if (strcmp(name, "translation") == 0)
            {
                for (TidyAttr attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr))
                {
                    if (strcmp(tidyAttrName(attr), "translation") == 0)
                    {
                        TidyBuffer buf;
                        tidyBufInit(&buf);
                        if (tidyNodeGetText(tdoc, child, &buf))
                        {
                            str_list_add(vocabs, (const char *)buf.bp);
                        }
                        tidyBufFree(&buf);
                    }
                }
            }

            tidy_traverse_html(tdoc, child, vocabs);
        }
    }
}

void html_tidy_search(const char *html_str, str_list *vocabs)
{
    TidyDoc tdoc = tidyCreate();
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int err = -1;

    Bool ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes); // Convert to XHTML
    if (ok)
    {
        err = tidySetErrorBuffer(tdoc, &errbuf); // Capture diagnostics
        if (err >= 0)
        {
            err = tidyParseString(tdoc, (ctmbstr)html_str); // Parse the input
            if (err >= 0)
            {
                err = tidyCleanAndRepair(tdoc); // Tidy it up!
                if (err >= 0)
                {
                    err = tidyRunDiagnostics(tdoc); // Kvetch
                    if (err > 1)                    // If error, force output.
                    {
                        err = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? err : -1);
                        if (err >= 0)
                        {
                            err = tidySaveBuffer(tdoc, &output); // Pretty Print
                        }
                    }
                }
            }
        }
    }

    if (err >= 0)
    {
        if (err > 0)
            printf("\nDiagnostics:\n\n%s", errbuf.bp);
        printf("\nEverything fine with Tidy.\nReady for processing...\n\n");
        tidy_traverse_html(tdoc, tidyGetRoot(tdoc), vocabs);
    }
    else
        printf("A severe error (%d) occurred.\n", err);

    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
}