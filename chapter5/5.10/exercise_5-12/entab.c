#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void entab(int m, int n, char line[]) {
    char c;
    int posCount, tabCount, spaceCount, tabStop, i, j, charCount;

    tabCount = 0;
    spaceCount = 0;
    charCount = 0;
    i = 1;
    tabStop = n;
    j = 0;
    for (posCount=1; (c=line[j++]) != '\0'; posCount++) {
        if (c == ' ') {
            if (posCount < m) {
                print_char_with_visible_blanks(c);
            }
            else {
                if ((posCount % tabStop) == 0) { // use tab whenever possible
                    tabCount++;
                    spaceCount = 0;
                }
                else { // use space only when cannot use tab
                    spaceCount++;
                }
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