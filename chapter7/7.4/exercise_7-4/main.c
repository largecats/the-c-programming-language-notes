/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous section.
*/

#include <stdio.h>
#include <stdarg.h>
#include "../../../helper_functions.h"

#define MAXLINE 100

int minscanf(char *format, ...);

int main() {
    int day;

    minscanf("Remember, remember, the %dth of November", &day);
    print_variable(day);
    return 0;
}

/*
$ gcc chapter7/7.4/exercise_7-4/main.c -o chapter7/7.4/exercise_7-4/result.out

$ chapter7/7.4/exercise_7-4/result.out
Remember, remember, the 5th of November
day = 5
*/

/* minscanf: minimal scanf with variable argument list 
Only supports one %, as it will channel the inputs to scanf once a % is encountered.
*/
int minscanf(char *format, ...) {
    va_list ap; /* points to each unamed arg in turn */
    char *p, *sp, temp[MAXLINE];
    int *ip, i;
    double *dp;

    va_start(ap, format); /* make ap point to the 1st unamed arg */
    for (p=format; *p; p++) {
        if (*p != '%') {
            temp[i++] = *p;
        }
        else {
            temp[i++] = *p++; // get '%'
            temp[i++] = *p; // get the formatting specification after '%'
            switch (*p) {
                case 'd':
                    ip = va_arg(ap, int *);
                    scanf(temp, ip);
                case 'f':
                    dp = va_arg(ap, double *);
                    scanf(temp, dp);
                case 's':
                    sp = va_arg(ap, char *);
                    scanf(temp, sp);
            }
        }
    }
    
}