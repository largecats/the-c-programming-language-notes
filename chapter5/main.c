#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

/*
The source files need to be compiled together.

In WSL, cd to 
    /mnt/c/Users/xiaolinfan/Fun/programming/languages/languages/the-c-programming-language/chapter5
Type
    gcc main.c getch.c getop.c stack.c -o result.out
to compile the source files. Then type
    ./result.out
to run the calculater
*/

#define MAXOP 100

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