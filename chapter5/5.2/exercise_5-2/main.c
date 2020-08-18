/*
Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?
*/

#include <stdio.h>
#include <ctype.h>
#include "../../../helper_functions.h"

int getfloat(double *pn);

int main() {
    int i;
    double arr[MAXLINE];

    for (i = 0; i < MAXLINE && getfloat(&arr[i]) != EOF; i++) {
        ;
    }
    print_variable(i);

    print_float_array(arr);
}

/*
$ gcc chapter5/5.2/exercise_5-2/main.c helper_functions.c -o chapter5/5.2/exercise_5-2/result.out

$ chapter5/5.2/exercise_5-2/result.out
0.123
2.35
1
i = 3
[0.123, 2.350, 1.000, ]
*/

/* getfloat: read float into double *pn */
int getfloat(double *pn) {
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
    for (*pn = 0.0; isdigit(c); c=getch()) {
        *pn = 10.0 * *pn + (c-'0');
    }
    if (c == '.') {
        c = getch();
        int power = 1;
        for (; isdigit(c); c=getch()) {
            // print_char(c);
            *pn = 10.0 * *pn + (c-'0');
            power *= 10;
        }
        *pn /= power;
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return c; /* possibly EOF */
}