/*
Exercise 4-6. Add commands for handling variables. (It’s easy to provide twenty-six variables with single-letter names.) Add
a variable for the most recently printed value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/* reverse Polish calculator */
int main() {
    int type, var;
    double op2, l; /* l for latest calculated value*/
    char s[MAXOP];
    double variables[26];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '=': /* 5 X = translates to X = 5 */
                pop(); /* pop the variable symbol */
                if ( var >= 'A' && var <= 'Z') {
                    variables[var-'A'] = pop(); /* pop the value assigned to the variable */
                }
                else
                    printf("error: unknown variable name\n");
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
                l = pop(); /* if the latest input is variable assignment, this will raise stack empty error 
                    since no calculated value has been pushed to the stack*/
                printf("\t%.8g\n", l);
                break;
            default:
                if (type >= 'A' && type <= 'Z') {
                    push(variables[type-'A']);
                }  
                else if (type == 'l') { /* replace variable l with the latest calculated value */
                    push(l);
                }
                else {
                    printf("error: unknown command %s\n",s);
                }
                break;
        }
        var = type;
    }
    return 0;
}

/*
When compiling, need to add -lm after main.c to link to the module containing fmod(): https://stackoverflow.com/questions/3209721/gcc-gives-error-while-using-fmod

$ gcc chapter4/4.3/exercise_4-6/main.c -lm chapter4/4.3/exercise_4-6/getch.c chapter4/4.3/exercise_4-6/getop.c chapter4/4.3/exercise_4-6/stack.c -o chapter4/4.3/exercise_4-6/result.out

$ chapter4/4.3/exercise_4-6/result.out
10 A =
error: stack empty
        0
A
        10
5 B =
error: stack empty
        0
B
        5
A B +
        15
10 A = 5 B = A B +
        15
*/