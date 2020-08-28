#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#include "../../../helper_functions.h"

int getop(char *s) {
    int result;
    static char space = '\0';
    static char newline = '\0';

    while ((result = scanf("%s%c", s, &space)) == 2) {
        // print_string(s);
        // print_char_with_visible_blanks(space);
        if (isdigit(*s)) {
            return NUMBER;
        }
        else {
            if (space == '\n') {
                newline = space;
            }
            return s[0];
        }
    }
    if (newline == '\n') {
        newline = '\0';
        return '\n';
    }
    return EOF;
}