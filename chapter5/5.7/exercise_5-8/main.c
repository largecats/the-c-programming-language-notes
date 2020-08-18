/*
Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect.
*/

#include <stdio.h>
#include "../../../helper_functions.h"

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int m, d;
    print_variable(day_of_year(1988, 3, 1));
    month_day(1988, 60, &m, &d); /* p109: "Since the operator & produces the address of a variable, &a is a pointer to a" by definition. */
    print_variable(m);
    print_variable(d);
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        printf("error: invalid month or day");
        return -1;
    }
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i=1; i<month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

/* month day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (year < 1 || yearday < 1 || (leap && (yearday > 366)) || (!leap && (yearday > 365))) {
        printf("error: invalid yearday");
        *pmonth = -1;
        *pday = -1;
    }
    else {
        for (i = 1; yearday > daytab[leap][i]; i++) {
            yearday -= daytab[leap][i];
        }
        *pmonth = i;
        *pday = yearday;
    }
}

/*
$ gcc chapter5/5.7/exercise_5-8/main.c helper_functions.c -o chapter5/5.7/exercise_5-8/result.out

$ chapter5/5.7/exercise_5-8/result.out

day_of_year(1988, 3, 1) = 61
m = 2
d = 29
*/