/* 
Exercise 1-24. Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, brackets and braces. Don’t forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.)
*/

#include <stdio.h>

void traverseComment(char c);
void traverseQuote(char c);
void traverseCode(char c);

int parentheses, brackets, braces;

main() {
    char c;

    parentheses = brackets = braces = 0;
    while ((c=getchar()) != EOF) {
        if (c == '/') {
            if ((c=getchar()) == '*') {
                c = getchar();
                traverseComment(c);
            }
            else {
                traverseCode(c);
            }
        }
        else if (c == '\'' || c == '"') {
            traverseQuote(c);
        }
        else {
            traverseCode(c);
        }
    }

    if (parentheses == 0 && brackets == 0 && braces == 0) {
        printf("No unmatched");
    }
    else {
        if (parentheses < 0) {
            printf("Detected %d unmatched )\n", -parentheses);
        }
        else if (parentheses > 0) {
            printf("Detected %d unmatched (\n", parentheses);
        }
        if (brackets < 0) {
            printf("Detected %d unmatched ]\n", -brackets);
        }
        else if (brackets > 0) {
            printf("Detected %d unmatched [\n", brackets);
        }
        if (braces < 0) {
            printf("Detected %d unmatched }\n", -braces);
        }
        else if (braces > 0) {
            printf("Detected %d unmatched {\n", braces);
        }
    }
}

void traverseComment(char c) {
    char c1, c2;

    c1 = c;
    c2 = getchar();
    while (c1 != '*' || c2 != '/') {
        c1 = c2;
        c2 = getchar();
    }
    getchar();
}

void traverseQuote(char c) {
    char c1;

    while ((c1=getchar()) != c) {
        if (c1 == '\\') {
            getchar(); // skip the escaped character, whatever it is
        }
    }
}

void traverseCode(char c) {
    if (c == '(') {
        parentheses++;
    }
    else if (c == ')') {
        parentheses--;
    }
    else if (c == '[') {
        brackets++;
    }
    else if (c == ']') {
        brackets--;
    }
    else if (c == '{') {
        braces++;
    }
    else if (c == '}') {
        braces--;
    }
}