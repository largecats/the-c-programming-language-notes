/*
Exercise 4-3. Given the basic framework, it’s straightforward to extend the calculator. Add the modulus (%) operator and
provisions for negative numbers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/* reverse Polish calculator */
int main() {
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
            case '%':
                op2 = pop();
                if(op2 != 0.0) {
                    push(fmod(pop(), op2));
                }
                else
                    printf("error: zero divisor\n");
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
When compiling, need to add -lm after main.c to link to the module containing fmod(): https://stackoverflow.com/questions/3209721/gcc-gives-error-while-using-fmod

$ gcc chapter4/4.3/exercise_4-3/main.c -lm chapter4/4.3/exercise_4-3/getch.c chapter4/4.3/exercise_4-3/getop.c chapter4/4.3/exercise_4-3/stack.c -o chapter4/4.3/exercise_4-3/result.out

$ chapter4/4.3/exercise_4-3/result.out
3 2 %
        1
2 3 %
        2
-9 5 %
        -4
-5 9 %
        -5
-5 4 %
        -1
*/

/*
https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c
3 mod 2 = 1
2 mod 3 = 2
-9 / 5 = -1 with remainder -4
-5 / 9 = 0 with remainder -5
-5 / 4 = -1 with remainder -1
*/