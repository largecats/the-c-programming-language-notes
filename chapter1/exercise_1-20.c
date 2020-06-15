/*
Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>
#define TAB_STOP 8

void print_char_with_visible_blanks(char c);

main() {
    char c;
    int posCount; // number of positions traversed

    posCount = 0;
    while ((c=getchar()) != EOF) {
        if (c == '\t') {
            int spaceCount = (TAB_STOP - (posCount % TAB_STOP));
            posCount = posCount + spaceCount;
            for (;spaceCount>0; spaceCount--) {
                print_char_with_visible_blanks(' ');
            }
        }
        else if (c == '\n') {
            putchar(c);
            posCount = 0;
        }
        else {
            print_char_with_visible_blanks(c);
            posCount++;
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
}

/*
hello Neo
hello\sNeo
hello   Neo
hello\s\s\sNeo
knock   knock
knock\s\s\sknock
follow  the     white   rabbit
follow\s\sthe\s\s\s\s\swhite\s\s\srabbit
*/