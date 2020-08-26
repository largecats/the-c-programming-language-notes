/*
Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic
characters in octal or hexadecimal according to local custom, and break long text lines.
*/

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 20
#define OCTAL_LEN 6

int main() {
    char c;
    int pos;

    while ((c=getchar()) != EOF) {
        if (iscntrl(c)) {
            // non-graphic character
            printf("%*o", OCTAL_LEN, c); // print in 6 digits octal number (coz 8^5 < 2^16 < 8^6)
            pos = pos + OCTAL_LEN;
            if (c == '\n') {
                pos = 0; // reset pos
            }
            putchar('\n');
        }
        else {
            if (pos == MAXLINE) {
                putchar('\n');
                pos = 0;
                if (c != ' ') {
                    putchar(c);
                    pos++;
                }
            }
            else {
                putchar(c);
                pos++;
            }
        }
    }
}

/*
$ gcc chapter7/7.2/exercise_7-2/main.c -o chapter7/7.2/exercise_7-2/result.out

$ chapter7/7.2/exercise_7-2/result.out
Wake up, Neo. The Matrix has you. Follow the white rabbit. Knock knock
Wake up, Neo. The Ma
trix has you. Follow
the white rabbit. Kn
ock knock    12 // note the \n is converted to '    12' with field width 6.
*/