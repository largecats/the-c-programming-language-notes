/*
Exercise 1-22. Write a program to ‘‘fold’’ long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.
*/

#include <stdio.h>
#define TAB_STOP 8
#define LINE_WIDTH 16
#define IN 1
#define OUT 0

void fold(char line[]);

int main() {
    char c;
    char line[LINE_WIDTH];
    int charCounter, colCounter, lastBlankPos, lastNonBlankPos;

    charCounter = 0; // how many characters input so far in current line
    colCounter = 0; // how many columns input so far in current line
    lastBlankPos = 0; // position of the last blank in current line
    while ((c = getchar()) != EOF) {
        // printf("c=%c\n", c);
        if (c != '\n') {
            if (colCounter == LINE_WIDTH) {
                if (lastBlankPos > 1) {
                    for (lastNonBlankPos=lastBlankPos; line[lastNonBlankPos] == ' '; lastNonBlankPos--) {
                        ;
                    }
                }
                else { // if the string has no blank, need to set lastNonBlankPos to the last position
                // otherwise will print one character per line
                    lastNonBlankPos = charCounter-1;
                }
                for (int i=0; i<=lastNonBlankPos; i++) {
                    putchar(line[i]);
                }
                putchar('\n');
                int blankState = IN;
                lastBlankPos = 0;
                charCounter = 0;
                colCounter = 0;
                int i = 0;
                for (i=lastNonBlankPos+1; i<LINE_WIDTH; i++) {
                    // printf("i=%d, lastNonBlankPos=%d, blankState=%d\n", i, lastNonBlankPos, blankState);
                    if (line[i] != '\t' && line[i] != ' ') {
                        blankState = OUT;
                    }
                    if (blankState == OUT) {
                        line[i-lastNonBlankPos-1] = line[i];
                        if (line[i] == '\t') {
                            lastBlankPos = charCounter;
                            colCounter = colCounter + TAB_STOP;
                        }
                        else {
                            colCounter++;
                            if (c == ' ') {
                                lastBlankPos = charCounter;
                            }
                        }
                        charCounter++;
                    }
                    else {
                        lastNonBlankPos++;
                    }
                }
                if (c != '\t' && c != ' ') {
                    line[i-lastNonBlankPos-1] = c;
                    charCounter++;
                    colCounter++;
                    lastNonBlankPos++;
                }  
            }
            else {
                // printf("charCounter=%d, c=%c\n", charCounter, c);
                line[charCounter] = c;
                if (c == '\t') {
                    lastBlankPos = charCounter;
                    colCounter = colCounter + (TAB_STOP - (charCounter % TAB_STOP));
                }
                else {
                    colCounter++;
                    if (c == ' ') {
                        lastBlankPos = charCounter;
                    }
                }
                charCounter++;
            }
        }
        else {
            for (int i=0; i<charCounter; i++) {
                printf("%c", line[i]);
            }
            putchar('\n');
            charCounter = 0;
            colCounter = 0;
            lastBlankPos = 0;
        }
    }
}
    

/*
$ gcc chapter1/1.10/exercise_1-22/main.c -o chapter1/1.10/exercise_1-22/result.out

$ chapter1/1.10/exercise_1-22/result.out
The Matrix has  you. Wake up Neo. Follow the white rabbit. Knock knock.
The Matrix has  
you. Wake up 
Neo. Follow the 
white rabbit. 
Knock knock.

hello
hello

dddddddddddddddddddddddddddddddddddddddddd
dddddddddddddddd
dddddddddddddddd
dddddddddd
*/