#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "extern.h"

/* entab: replace blanks with tabs */
void entab(int argc, char *argv[], char line[]) {
    char c;
    int posCount, tabCount, spaceCount, tabStop, i, j, charCount;

    tabCount = 0;
    spaceCount = 0;
    charCount = 0;
    i = 1;
    tabStop = atoi(argv[i]);
    j = 0;
    for (posCount=1; (c=line[j++]) != '\0'; posCount++) {
        if (c == ' ') {
            if (i >= argc || tabStop == 0) {
                tabStop = TAB_STOP;
            }
            // print_variable(i);
            // print_variable(tabStop);
            if((posCount % tabStop) == 0) { // use tab whenever possible
                tabCount++;
                spaceCount = 0;
                tabStop = atoi(argv[i++]) - tabStop; /* increment to the next tabStop after using a tab */
            }
            else { // use space only when cannot use tab
                spaceCount++;
            }
        }
        else {
            // printf("spaceCount=%d, tabCount=%d\n", spaceCount, tabCount);
            for (;tabCount>0; tabCount--) {
                print_char_with_visible_blanks('\t');
                // putchar('\t');
            }
            for (;spaceCount>0; spaceCount--) {
                print_char_with_visible_blanks(' ');
                // putchar(' ');
            }
            if (c == '\n') {
                posCount = 0;
            }
            print_char_with_visible_blanks(c);
            // putchar(c);
        }
    }
}