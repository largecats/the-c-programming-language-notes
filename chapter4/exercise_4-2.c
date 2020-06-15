/*
Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include <stdio.h>
#include <math.h>

double atof(char s[]);
int isspace(char c);
int isdigit(char c);

int main() {
    char s[] = "123.45e-6";

    printf("%f", atof(s));

    return 0;
}

double atof(char s[]) {
    double val, power;
    int i, sign, seSign, seExp;
    for (i=0; isspace(s[i]); i++) { /* skip white space */
        ;
    }
    sign = (s[i] == '-')? -1: 1; /* get sign */
    if (s[i] == '+' || s[i] == '-') { /* skip sign */
        i++;
    }
    for (val=0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') { /* skip decimal point */
        i++;
    }
    for (power=1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E') { /* handle scientific notation */
        i++; /* skip scientific notation symbol e, E */
    }
    if (s[i] == '+' || s[i] == '-') {
        seSign = s[i++]; /* sign of the scientific notification exponent */
    }
    for (seExp=0; isdigit(s[i]); i++) { /* get the value of the power of the scientific notification */
        seExp = 10 * seExp + (s[i] - '0');
    }
    return seSign == '-'? sign * val / power / pow(10, seExp): sign * val / power * pow(10, seExp);
}

int isspace(char c) {
    return c == ' ';
}

int isdigit(char c) {
    return (c >= '0') && (c <= '9');
}