/*
Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.
*/

/*
http://www.learntosolveit.com/cprogramming/Ex_5.19_undcl.html
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../helper_functions.h"

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int nexttoken(void);

int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last toekn string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000]; /* output string */
int prevtoken;

/* undcl: convert word description to declaraction */
int main() {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token); /* copy token value to out */
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                /* directly put (), [] behind token value */
                strcat(out, token);
            }
            else if (type == '*') {
                /* peek at the next token to see if need to add parentheses */
                if ((type = nexttoken()) == PARENS || type == BRACKETS) {
                    sprintf(temp, "(*%s)", out);
                }
                else {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            }
            else if (type == NAME) {
                /* put name in front of current output */
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

/*
$ gcc chapter5/5.12/exercise_5-19/main.c chapter5/5.12/exercise_5-19/gettoken.c helper_functions.c -o chapter5/5.12/exercise_5-19/result.out

Before:
$ chapter5/5.12/exercise_5-19/result.out
argv * * char
char (*(*argv))

After:
$ chapter5/5.12/exercise_5-19/result.out
argv * * char
char **argv
*/

/* nexttoken: get the next token and push it back */
int nexttoken(void) {
    int type;

    type = gettoken();
    prevtoken = YES;
    return type;
}