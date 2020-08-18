/*
Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/

#include <stdio.h>
#include<string.h>

#define MAXLINE 100

char buf = '\0'; /* use single character as buffer */

int getch(void);
void ungetch(int c);

int main() {
    char c = 'c';
    ungetch(c);

    while ((c=getch()) != EOF) {
        putchar(c);
    }
}

/*
$ gcc chapter4/4.3/exercise_4-8/main.c -o chapter4/4.3/exercise_4-8/result.out

$ chapter4/4.3/exercise_4-8/result.out
c
*/

int getch(void) { /* get character from buffer */
    if (buf != '\0') {
        int temp = buf;
        buf = '\0';
        return temp;
    }
    else {
        return getchar();
    }
}

void ungetch(int c) { /* push character into buffer */
    if (buf != '\0') {
        printf("ungetch: too many characters\n");
    }
    else {
        buf = c;
    }
}