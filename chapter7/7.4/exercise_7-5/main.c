/*
Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"
#include "../../../helper_functions.h"

#define MAXOP 100

/* reverse Polish calculator */
int main() {
    int type, result;
    double op2;
    char s[MAXOP]; /* store op read from input */

    while ((type = getop(s)) != EOF) {
        // print_char(type);
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                }
                else {
                    printf("error: zero division");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command");
                break;
        }
    }
    return 0;
}

/*
$ gcc chapter7/7.4/exercise_7-5/main.c chapter7/7.4/exercise_7-5/getop.c chapter7/7.4/exercise_7-5/stack.c helper_functions.c -o chapter7/7.4/exercise_7-5/result.out

$ chapter7/7.4/exercise_7-5/result.out
1 2 - 4 5 + *
        -9
*/