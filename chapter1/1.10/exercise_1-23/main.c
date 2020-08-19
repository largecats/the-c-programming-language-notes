/*
Exercise 1-23. Write a program to remove all comments from a C program. Don’t forget to handle quoted strings and
character constants properly. C comments don’t nest.

Note: single block comments that start wth "//" are C++ syntax and are ignored
*/

#include <stdio.h>
#define IN 1
#define OUT 0

int main() {
    char c, cNext;
    int commentState, quoteState;

    c = getchar();
    cNext = getchar();
    commentState = OUT;
    quoteState = OUT;
    while (cNext != EOF) {
        // printf("c=%c, cNext=%c\n", c, cNext);
        if (c == '"' || c == '\'') {
            if (commentState == OUT) {
                quoteState = IN - quoteState;
            }
        }
        if (quoteState == IN) {
            putchar(c);
            c = cNext;
            cNext = getchar();
        }
        else {
            if (c == '/' && cNext == '*') {
                commentState = IN; // start of multiblock comment
                c = getchar();
                cNext = getchar();
            }
            else if (c == '*' && cNext == '/') {
                commentState = OUT; // end of multiblock comment
                c = getchar();
                if (c == '\n') {
                    putchar('\n');
                    c = getchar();
                    cNext = getchar();
                }
                else{
                    cNext = getchar();
                }
            }
            else {
                if (commentState == OUT) {
                    putchar(c);
                }
                c = cNext;
                cNext = getchar();
            }
        }
        if (cNext == '\n') {
            putchar(c);
            putchar('\n');
            c = getchar();
            cNext = getchar();
        }
    }
}

/*
$ gcc chapter1/1.10/exercise_1-23/main.c -o chapter1/1.10/exercise_1-23/result.out

$ chapter1/1.10/exercise_1-23/result.out
int i = 0; / * hello * /
int i = 0;
int i; / * "hello" * /
int i;
*/