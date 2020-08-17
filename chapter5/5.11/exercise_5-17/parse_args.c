#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

int isnumber(char c);
void get_field(char *from, char *start, char *end);

void parse_args(int argc, char *argv[], int fields[MAXFIELDS][2], int fieldArgs[MAXFIELDS][4]) {
    /* parse arguments from command line */
    int i = 0;
    int fieldPtr = 0;
    for (int row=0; row<MAXFIELDS; row++) {
        for (int col=0; col<=2; col++) {
            fields[row][col] = -1;
        }
    }
    fields[0][0] = 0;
    fields[0][1] = MAXLEN;

    while (++i < argc) {
        if (strcmp(argv[i], "-k") == 0) {
            print_string(argv[i]);
            fieldPtr++;
        }
        else {
            print_string(argv[i]);
            if (isnumber(argv[i][0])) {
                char start[MAXLEN];
                char end[MAXLEN];
                get_field(argv[i], start, end);
                fields[fieldPtr][0] = atoi(start);
                fields[fieldPtr][1] = atoi(end);
            }
            else {
                if (strcmp(argv[i], "-n") == 0) {
                    fieldArgs[fieldPtr][0] = 1;
                }
                else if (strcmp(argv[i], "-r") == 0) {
                    fieldArgs[fieldPtr][1] = 1;
                }
                else if (strcmp(argv[i], "-f") == 0) {
                    fieldArgs[fieldPtr][2] = 1;
                }
                else if (strcmp(argv[i], "-d") == 0) {
                    fieldArgs[fieldPtr][3] = 1;
                }
                else {
                    printf("Error: unknown argument");
                }
            }
        }
        // print_variable(i);
        // print_variable(fieldPtr);
    }
}

void update_args(int *n, int *r, int *f, int *d, int *fieldStart, int *fieldEnd, int fields[2], int fieldArgs[4]) {
    *n = fieldArgs[0];
    *r = fieldArgs[1];
    *f = fieldArgs[2];
    *d = fieldArgs[3];
    *fieldStart = fields[0];
    *fieldEnd = fields[1];
    print_variable(*n);
    print_variable(*r);
    print_variable(*f);
    print_variable(*d);
    print_variable(*fieldStart);
    print_variable(*fieldEnd);
}

int isnumber(char c) {
    char numbers[] = "0123456789";
    return (strchr(numbers, c) != NULL);
}

void get_field(char *from, char *start, char *end) {
    int i = 0;
    int j = 0;
    while (from[i] != ',') {
        start[j++] = from[i++];
    }
    start[j] = '\0';
    i++;
    j = 0;
    while (from[i] != '\0') {
        end[j++] = from[i++];
    }
    end[j] = '\0';
}