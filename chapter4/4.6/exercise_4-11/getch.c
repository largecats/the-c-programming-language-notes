/*******************************/
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void) { /* get character from buffer */
    return (bufp > 0)? buf[--bufp]: getchar(); /* get from last occupied position in buf */
}

// void ungetch(int c) { /* push character back to buffer */
//     if (bufp >= BUFSIZE) {
//         printf("ungetch: too many characters\n");
//     }
//     else {
//         buf[bufp++] = c;
//     }
// }