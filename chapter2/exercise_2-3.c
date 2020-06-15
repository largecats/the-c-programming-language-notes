/*
Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.
*/

#include <stdio.h>

int htoi(char h[]) {
    int i = 0;
    int n = 0;
    if (h[0]=='0' && (h[1]=='x' || h[1]=='X')) {
        i = 2;
    }
    for(; h[i]!='\0'; i++) {
        char s = h[i];
        if (s >= '0' && s <= '9') {
            n = 16 * n + (s - '0');
        }
        else if (s >= 'a' && s <= 'f') {
            n = 16 * n + (s - 'a') + 10;
        }
        else if (s >= 'A' && s <= 'F') {
            n = 16 * n + (s - 'A') + 10;
        }
    }
    return n;
}

main() {
    char h[] = "0x1E";

    printf("%d\n", htoi(h));
}
