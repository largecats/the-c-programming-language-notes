/*
Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each
operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).
*/

/*
Actually cannot test using * coz it translates to names of all files in the directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "../../../helper_functions.h"

/* expr: evaluates reverse Polish expression from command line */
int main(int argc, char *argv[]) {
    int i, op2;

    i = 0;
    while (++i < argc) {
        char *s;
        s = argv[i];
        // print_string(s);
        switch(getop(s)) {
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
            default:
                printf("error: unknown command");
                break;
        }
    }
    printf("\t %8g\n",pop());
    return 0;
}

/*
$ gcc chapter5/5.10/exercise_5-10/main.c chapter5/5.10/exercise_5-10/getop.c chapter5/5.10/exercise_5-10/stack.c helper_functions.c -o chapter5/5.10/exercise_5-10/result.out

$ chapter5/5.10/exercise_5-10/result.out 2 3 4 + -
               -5
2 - (3+4)
*/