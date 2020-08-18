/*
Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top
two elements. Add a command to clear the stack.
*/

/*
Note that case '\n' will always pop() whenever ENTER is pressed, including when invoking the commands top, duplicate, swap, and clear.
So printing the top element of the stack will always be accompanied by a pop() from case '\n'.
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

$ gcc chapter4/4.3/exercise_4-4/main.c -lm chapter4/4.3/exercise_4-4/getch.c chapter4/4.3/exercise_4-4/getop.c chapter4/4.3/exercise_4-4/stack.c -o chapter4/4.3/exercise_4-4/result.out

$ chapter4/4.3/exercise_4-4/result.out
1 d +
        2
3 2 s
        3
t 1 +
2
        3
*/

/*
1 d + => 1 1 +
3 2 s => swaps (3, 2) in stack to (2, 3), with 3 at the top
t 1 + => 2 1 +
*/