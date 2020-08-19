/*
Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>
#include "../../../helper_functions.h"

#define TAB_STOP 8

int main() {
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

/*
$ gcc chapter1/1.10/exercise_1-20/main.c helper_functions.c -o chapter1/1.10/exercise_1-20/result.out

$ chapter1/1.10/exercise_1-20/result.out
hello Neo
hello\sNeo
hello   Neo
hello\s\s\sNeo
knock   knock
knock\s\s\sknock
follow  the     white   rabbit
follow\s\sthe\s\s\s\s\swhite\s\s\srabbit
*/