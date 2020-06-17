/*
Exercise 5-12. Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"

#define TAB_STOP 8

void parse_arg(int argc, char *argv[], int *mp, int *np);
void detab(int m, int n, char line[]);
void entab(int m, int n, char line[]);

int main(int argc, char *argv[]) {
    char line[MAXLINE]; /* read original input into line */
    int m, n;

    parse_arg(argc, argv, &m, &n);
    getline_pointer_version(line, MAXLINE);

    detab(m, n, line);
    entab(m, n, line);

    putchar('\n');
}

/*
$ ./result.out -10 +8
hello   Neo follow  the    white        rabbit
hello\tNeo\sfollow\s\sthe\s\s\s\swhite\s\s\s\s\s\s\s\srabbit
hello\tNeo\sfollow\s\sthe\t\swhite\trabbit\n

$ ./result.out -10 +8
hello   Neo follow  the    white        rabbit
hello\s\s\sNeo\sfollow\s\sthe\s\s\s\swhite\s\s\s\s\s\s\s\srabbit
hello\s\s\sNeo\sfollow\s\sthe\t\s\s\swhite\trabbit\n
*/

void parse_arg(int argc, char *argv[], int *mp, int *np) {
    int i = 1;

    while (i < argc) {
        switch (*argv[i]) {
            case '-':
                *mp = atoi(++(argv[i]));
            case '+':
                *np = atoi(++(argv[i]));
                break;
            default:
                break;
        }
        i++;
    }
}

void detab(int m, int n, char line[]) {
    char c;

    int i, j, tabStop, posCount, charCount;
    i = 0; /* counter for argv */
    j = 0; /* counter for line */
    tabStop = n;
    posCount = 0;  // number of positions traversed (one character, e.g., \t, may occupy multiple positions)
    charCount = 0; // number of characters traversed, counter for to

    while ((c=line[j++]) != '\0') {
        if (c == '\t') {
            int spaceCount = (tabStop - (posCount % tabStop));
            posCount = posCount + spaceCount;
            if (posCount < m) {
                print_char_with_visible_blanks(c);
            }
            else {
                for (;spaceCount>0; spaceCount--) {
                    print_char_with_visible_blanks(' ');
                    // putchar(' ');
                }
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