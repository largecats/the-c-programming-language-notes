/*
Exercise 4-5. Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.
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
            case FUNC:
                func(s);
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
                if(op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case 't': /* print top element */
                top();
                break;
            case 'd': /* duplicate top element */
                duplicate();
                break;
            case 's': /* swap the first two elements */
                swap();
                break;
            case 'c': /* clear stack */
                clear();
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

$ gcc chapter4/4.3/exercise_4-5/main.c -lm chapter4/4.3/exercise_4-5/getch.c chapter4/4.3/exercise_4-5/getop.c chapter4/4.3/exercise_4-5/stack.c -o chapter4/4.3/exercise_4-5/result.out

$ chapter4/4.3/exercise_4-5/result.out
2 3 pow
        8
1 exp
        2.7182818
1 sin
        0.84147098
2 sin
        0.90929743
*/