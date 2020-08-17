#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "extern.h"

/* detab: replace tabs with blanks */
void detab(int argc, char *argv[], char line[]) {
    char c;

    int i, j, tabStop, posCount, charCount;
    i = 0; /* counter for argv */
    j = 0; /* counter for line */
    tabStop = 0;
    posCount = 0;  // number of positions traversed (one character, e.g., \t, may occupy multiple positions)
    charCount = 0; // number of characters traversed, counter for to

    while ((c=line[j++]) != '\0') {
        if (c == '\t') {
            if (++i >= argc) { /* increment to the next tabStop after encountering a tab */
                tabStop = TAB_STOP;
            }
            else {
                tabStop = atoi((argv[i])) - tabStop;
            }
            int spaceCount = (tabStop - (posCount % tabStop));
            posCount = posCount + spaceCount;
            for (;spaceCount>0; spaceCount--) {
                print_char_with_visible_blanks(' ');
                // putchar(' ');
            }
        }
        else if (c == '\n') {
            putchar(c);
            posCount = 0;
        }
        else {
            print_char_with_visible_blanks(c);
            // putchar(c);
            posCount++;
        }
    }
}