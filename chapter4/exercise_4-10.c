/*
Exercise 4-10. An alternate organization uses getline to read an entire input line; this makes getch and ungetch
unnecessary. Revise the calculator to use this approach.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void print_line(void);

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

/*******************************************/

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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

/*******************************************/
#define MAXLINE 100
char line[MAXLINE];
int lp = 0; /* next position to read in the line */

int getline(char s[], int lim) {
    int c, i;

    i = 0;
    while (i<lim-1 && (c=getchar())!=EOF && c!='\n') {
        s[i] = c;
        i++;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

void print_line(void) {
    int i = 0;
    printf("line = ");
    while (line[i] != '\0') {
        printf("%c", line[i++]);
    }
    putchar('\n');
}

/*******************************************/
#include <ctype.h>
#include <string.h>

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;
    if (line[lp] == '\0') { /* if we have finished reading the line, read the next line */
        if (getline(line, MAXLINE) == 0) {
            return EOF; /* getop now needs to return EOF explicitly as this is previously done by getch */
        }
        else {
            lp = 0; /* reset line pointer to first character in line */
        }
    }

    while ((s[0] = c = line[lp++]) == ' ' || c == '\t') { /* start reading from where we left off last time */
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') { /* not a number */
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[lp++])) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = line[lp++])) {
            ;
        }
    }
    s[i] = '\0';
    /* actually the following block will always be executed since c cannot be EOF now */
    if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
        lp--;
    }
    return NUMBER;
}

