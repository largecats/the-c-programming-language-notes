/*
Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as
arguments. Use the default tab settings if there are no arguments.
*/

/*
https://linux.die.net/man/1/tabs
The input is a list of integers representing tab stops. E.g., the default tab setting of every 8 columns starting at position 0
would have the list representation [0, 8, 16, 24, 32, 40]
*/

#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"

#define TAB_STOP 8

void detab(int argc, char *argv[], char line[]);
void entab(int argc, char *argv[], char line[]);

int main(int argc, char *argv[]) {
    char line[MAXLINE]; /* read original input into line */

    getline_pointer_version(line, MAXLINE);

    detab(argc, argv, line);
    entab(argc, argv, line);

    putchar('\n');
}

/*
$ ./result.out 8 16 32
follow the    white      rabbit
follow\sthe\s\s\s\swhite\s\s\s\s\s\srabbit
follow\sthe\s\s\s\swhite\t\srabbit

$ ./result.out 5 10
white      rabbit
white\s\s\s\s\s\srabbit
white\t\srabbit\n
$ ./result.out 8 16
white      rabbit
white\s\s\s\s\s\srabbit
white\t\s\s\srabbit\n

$ ./result.out 2 4 6 8 10
white   rabbit
white\s\s\srabbit
white\t\trabbit\n

$ ./result.out 3 6 9 12 
hello   Neo follow the    white      rabbit
hello\sNeo\sfollow\sthe\s\s\s\swhite\s\s\s\s\s\srabbit
hello\tNeo\sfollow\sthe\t\twhite\t\t\s\srabbit\n
*/

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