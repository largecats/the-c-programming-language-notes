/*
Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.
*/

#include <stdio.h>
#include <ctype.h>
#include "../../../helper_functions.h"

int getint(int *pn);

int main() {
    int i;
    int arr[MAXLINE];

    for (i = 0; i < MAXLINE && getint(&arr[i]) != EOF; i++) {
        ;
    }
    print_variable(i);

    print_array(arr);
}

/*
$ gcc chapter5/5.2/exercise_5-1/main.c helper_functions.c -o chapter5/5.2/exercise_5-1/result.out

$ chapter5/5.2/exercise_5-1/result.out
123
234
345
i = 3
[123, 234, 345, ]
*/

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())) {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* not a number */
        return 0;
    }
    sign = (c == '-')? -1: 1;
    if (c == '+' || c == '-') { /* proceed to read number */
        c = getch();
    }
    if (!isdigit(c) && c != EOF) { /* if + or - is not followed by digit, push it back on input */
        // ungetch(c); /* ignore the illegitimate input */
        return 0;
    }
    for (*pn = 0; isdigit(c); c=getch()) {
        *pn = 10 * *pn + (c-'0');
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return c; /* possibly EOF */
}