/*
Exercise 4-6. Add commands for handling variables. (It’s easy to provide twenty-six variables with single-letter names.) Add
a variable for the most recently printed value.
*/

/*
Exercise 4-5. Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void print_val(void);
void top(void);
void duplicate(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
main() {
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

/*******************************************/
#include <string.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void print_val(void) {
    printf("stack = ");
    while (sp >= 0) { /* use stack pointer instead of array index since the data structure is stack, not array*/
        printf("%f", val[sp--]);
    }
    putchar('\n');
}

void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    }
    else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp]; /* last occupied stack position */
    }
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void top(void) {
    if (sp > 0) {
        printf("%g\n", val[sp-1]);
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void duplicate(void) {
    if (sp > 0) {
        double e = pop();
        push(e);
        push(e);
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void swap(void) {
    if (sp > 0) {
        if (sp > 1) {
            double e1 = pop();
            double e2 = pop();
            push(e1);
            push(e2);
        }
        else {
            printf("error: not enough elements to swap\n");
        }
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void clear(void) {
    sp = 0;
}


/*******************************************/
#include <ctype.h>
#include <string.h>

int getch(void);
void ungetch(int);

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;
    int getop(char s[]);

    while ((s[0] = c = getch()) == ' ' || c =='\t') {
        ;
    }
    s[1] = '\0'; /* initialize s to contain c, the first character read */
    if (!isdigit(c) && c!='.') {
        return c;
    }
    
    i = 0;
    if (isdigit(c)) {
        while(isdigit(s[++i] =c =getch())) {
            ;
        }
    }

    if (c=='.') { /* continue reading fractional part of the operand, if any */
        while (isdigit(s[++i] = c=getch())) {
            ;
        }
    }
    
    s[i] = '\0';
    if (c!=EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
        ungetch(c);
    }
    return NUMBER;
}

/*******************************************/
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void) {
    return (bufp > 0)? buf[--bufp]: getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}