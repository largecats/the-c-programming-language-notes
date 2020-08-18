/*
Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design.
*/

/*
Modulo machine-dependent behaviour: https://stackoverflow.com/questions/18818349/kr-c-exercise-4-9-why-ignore-eof/18819133

An unsigned char cannot hold EOF, since its range is 0 to 255 and EOF has value -1. So we need to define buf to be an array of signed char or int.

This issue may be masked on some machines if they use signed char by default or do type conversion.
*/

#include <stdio.h>
#include<string.h>

#define BUFSIZE 100
#define MAXLINE 100

// unsigned char buf[BUFSIZE];
/*
buf =
buf = 255 - somehow EOF is converted to 255 in char and then back to -1 in int
Captured: -1
*/

// char buf[BUFSIZE];
/*
buf =
buf = -1
Captured: -1
*/

int buf[BUFSIZE];
/*
buf =
buf = -1
Captured: -1
*/

int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);
void print_buf(void);

int main() {
    char c, d;

    while ((c=getch()) != EOF) {
       putchar(c);
    }
    print_buf();
    ungetch(c);
    print_buf();
    d = getch();
    printf("Captured: %d\n", d);
}

/*
$ gcc chapter4/4.3/exercise_4-9/main.c -o chapter4/4.3/exercise_4-9/result.out

$ chapter4/4.3/exercise_4-9/result.out
hello
hello
bufp = 0
buf =
bufp = 1
buf = -1
Captured: -1
*/

int getch(void) { /* get character from buffer */
    return (bufp > 0)? buf[--bufp]: getchar();
}

void ungetch(int c) { /* push character into buffer */
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}

void print_buf(void) {
    printf("bufp = %d\n", bufp);
    printf("buf = ");
    while (bufp > 0) {
        printf("%d", buf[--bufp]);
    }
    printf("\n");
}

/*
Notes: Once getchar() reads EOF, it will only return EOF in any subsequent calls. 

main() {
    char c, d;

    while (1) {
        c = getchar();
        if (c == EOF) {
            printf("Captured: %d\n", c);
            c = getchar();
        }
        else{
            putchar(c);
        }
    }
}

Once EOF is encountered, no value other than EOF can be read and stored in buffer.
*/