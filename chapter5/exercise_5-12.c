/*
Exercise 5-12. Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"

#define TAB_STOP 8

void parse_arg(int argc, char *argv[], int m, int n);
void detab(int m, int n, char line[]);
void entab(int m, int n, char line[]);

int main(int argc, char *argv[]) {
    char line[MAXLINE]; /* read original input into line */
    int m, n;

    parse_arg(argc, argv, m, n);
    getline_pointer_version(line, MAXLINE);

    detab(m, n, line);
    entab(m, n, line);

    putchar('\n');
}

void parse_arg(int argc, char *argv[], int m, int n) {
    int i = 0;

    while (++i < argc) {
        char *arg = argv[i];
        if (*arg == '-') {
            m = atoi(*(++arg));
        }
        else if (*arg == '+') {
            n = atoi(*(++arg));
        }
    }
}
