/*
Exercise 4-10. An alternate organization uses getline to read an entire input line; this makes getch and ungetch
unnecessary. Revise the calculator to use this approach.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/* reverse Polish calculator */
main() {
    int type;
    double op2;
    char s[MAXOP];

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
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

/*
$ gcc chapter4/4.3/exercise_4-10/main.c chapter4/4.3/exercise_4-10/getop.c chapter4/4.3/exercise_4-10/stack.c -o chapter4/4.3/exercise_4-10/result.out

$ chapter4/4.3/exercise_4-10/result.out
1 1 +
        2
1 2 - 4 5 + *
        -9
*/