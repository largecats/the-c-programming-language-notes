/*
Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
*/

#include <stdio.h>
#define TAB_STOP 8

void print_char_with_visible_blanks(char c);

main() {
    char c;
    int posCount, tabCount, spaceCount;

    tabCount = 0;
    spaceCount = 0;
    for (posCount=1; (c=getchar()) != EOF; posCount++) {
        if (c == ' ') {
            if((posCount % TAB_STOP) == 0) { // use tab whenever possible
                tabCount++;
                spaceCount = 0;
            }
            else { // use space only when cannot use tab
                spaceCount++;
            }
        }
        else {
            // printf("spaceCount=%d, tabCount=%d\n", spaceCount, tabCount);
            for (;tabCount>0; tabCount--) {
                print_char_with_visible_blanks('\t');
            }
            for (;spaceCount>0; spaceCount--) {
                print_char_with_visible_blanks(' ');
            }
            if (c == '\n') {
                posCount = 0;
            }
            putchar(c);
        }
    }
}

void print_char_with_visible_blanks(char c) {
    if (c == '\t') {
        printf("\\t");
    }
    else if (c == ' ') {
        printf("\\s");
    }
    else if (c == '\n') {
        printf("\\n");
    }
    else {
        putchar(c);
    }
    // putchar(c);
}

/*
hello     Neo
hello\t\s\sNeo
knock     knock
knock\t\s\sknock
follow the    white      rabbit
follow\sthe\s\s\s\swhite\t\srabbit
*/