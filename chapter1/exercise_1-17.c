/*
Exercise 1-17. Write a program to print all input lines that are longer than 80 characters.
*/

#include <stdio.h>
#define MAXLINE 100 // maximum line length to print
#define THRESHOLD 80

int getline(char line[], int lim);
void copy(char to[], char from[]);

main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > THRESHOLD) {
            printf("%s\n", line);
        }
    }
    return 0;
}

int getline(char s[], int lim) {
    int c, i, j;
    
    j = 0; // j is the counter for reading the line into s
    for (i = 0; (c=getchar())!=EOF && c!='\n'; i++) { // i is the counter for the length of the line
        // s[i] = c;
        if (j < lim-1) {
            s[j] = c;
            j++; // only increment j when s is still being filled
        }
    }
    if (c == '\n') {
        if (i < lim-1) {
            s[j] = c;
            j++;
        }
    }
    s[j] = '\0';
    return i;
}

/*
Before time began, there was the Cube.
We know not where it comes from, only that it holds the power to create worlds, and fill them with life.
We know not where it comes from, only that it holds the power to create worlds, and fill them with 
That is how our race was born.    
For time we lived in harmony, but like all great power, some want it for good, others for evil.
For time we lived in harmony, but like all great power, some want it for good, others for evil.

And so began the war, the war that ravaged our planet until it was consumed by death.
And so began the war, the war that ravaged our planet until it was consumed by death.

And the Cube was lost in the far reaches of space.
We scattered across the galaxies, hoping to find it, and rebuild our home.
Searching every star, every world.
Just when all hopes seemed lost, message of a new discovery drew us to an unknown planet called Earth.
Just when all hopes seemed lost, message of a new discovery drew us to an unknown planet called Ear
*/