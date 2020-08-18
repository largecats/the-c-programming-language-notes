/*
Exercise 4-11. Modify getop so that it doesn’t need to use ungetch. Hint: use an internal static variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP]; /* store op read from input */

    while ((type = getop(s)) != EOF) {
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
$ gcc chapter4/4.6/exercise_4-11/main.c chapter4/4.6/exercise_4-11/getch.c chapter4/4.6/exercise_4-11/getop.c chapter4/4.6/exercise_4-11/stack.c -o chapter4/4.6/exercise_4-11/result.out

$ chapter4/4.6/exercise_4-11/result.out
1 1 +
        2
1 2 - 4 5 + *
        -9
*/