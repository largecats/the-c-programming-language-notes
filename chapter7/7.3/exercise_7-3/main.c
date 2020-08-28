/*
Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "../../../helper_functions.h"

#define MAXLEN 100

void minprintf(char *fmt, ...);

int main() {
    minprintf("hello\n");
    int i = 5;
    minprintf("i = %6d\n", i);
    double j = 5.0;
    minprintf("j = %.3f\n", j);
    char *s = "hello";
    minprintf("s = %10.3s\n", s);
}

/*
$ gcc chapter7/7.3/exercise_7-3/main.c -o chapter7/7.3/exercise_7-3/result.out

$ chapter7/7.3/exercise_7-3/result.out
hello
i =      5
j = 5.000
s =        hel
*/

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
    va_list ap; /* declare ap of type va_list to point to each unnamed arg in turn */
    char *p, *sval, c, temp[MAXLEN];
    int ival, leftAlign, width, precision, formatFlag;
    double dval;

    va_start(ap, fmt); /* make ap point to the 1st unnamed argument */
    leftAlign = 0;
    formatFlag = 0;
    width = 0;
    precision = 0;
    p = fmt;
    while (*p) {
        // print_char(*p);
        if (*p == '%') {
            formatFlag = 1;
            p++;
            int i = 0;
            while (isdigit(*p)) {
                temp[i++] = *p++;
            }
            temp[i] = '\0';
            width = atoi(temp);
            temp[0] = '\0';
            p--;
        }
        else if (*p == '-') {
            leftAlign = 1;
        }
        else if (*p == '.') {
            p++;
            int i = 0;
            while (isdigit(*p)) {
                temp[i++] = *p++;
            }
            temp[i] = '\0';
            precision = atoi(temp);
            temp[0] = '\0';
            p--;
        }
        else if (formatFlag == 1 && (*p == 'd' || *p == 'f' || *p == 's')) {
            switch (*p) {
                case 'd':
                    // printf("d matched\n");
                    ival = va_arg(ap, int); /* get one argument and let ap point to the next */
                    if (leftAlign != 0) {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%-*.*d", width, precision, ival);
                            }
                            else {
                                printf("%-*d", width, ival);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%-.*d", precision, ival);
                            }
                            else {
                                printf("%-d", ival);
                            }
                        }
                    }
                    else {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%*.*d", width, precision, ival);
                            }
                            else {
                                printf("%*d", width, ival);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%.*d", precision, ival);
                            }
                            else {
                                printf("%d", ival);
                            }
                        }
                    }
                    break;
                case 'f':
                    // printf("f matched\n");
                    dval = va_arg(ap, double);
                    if (leftAlign != 0) {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%-*.*f", width, precision, dval);
                            }
                            else {
                                printf("%-*f", width, dval);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%-.*f", precision, dval);
                            }
                            else {
                                printf("%-f", dval);
                            }
                        }
                    }
                    else {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%*.*f", width, precision, dval);
                            }
                            else {
                                printf("%*f", width, dval);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%.*f", precision, dval);
                            }
                            else {
                                printf("%f", dval);
                            }
                        }
                    }
                    break;
                case 's':
                    // printf("s matched\n");
                    sval = va_arg(ap, char *);
                    if (leftAlign != 0) {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%-*.*s", width, precision, sval);
                            }
                            else {
                                printf("%-*s", width, sval);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%-.*s", precision, sval);
                            }
                            else {
                                printf("%-s", sval);
                            }
                        }
                    }
                    else {
                        if (width != 0) {
                            if (precision != 0) {
                                printf("%*.*s", width, precision, sval);
                            }
                            else {
                                printf("%*s", width, sval);
                            }
                        }
                        else {
                            if (precision != 0) {
                                printf("%.*s", precision, sval);
                            }
                            else {
                                printf("%s", sval);
                            }
                        }
                    }
                    break;
                default:
                    // printf("default matched\n");
                    putchar(*p);
                    break;
            }
        }
        else {
            putchar(*p);
        }
        p++;
    }
    va_end(ap); /* clean up */
}