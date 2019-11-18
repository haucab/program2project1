#ifndef PROJECT1_DATE_H
#define PROJECT1_DATE_H

#include "date_validate.h"

struct Date {
    unsigned short day, month;
    short year;
};

struct Date* newDate(unsigned short day, unsigned short month, short year, ValidationError_Date* err) {
    *err = validateDate(day, month, year);
    if (*err != DATE_OK) return NULL;

    struct Date* d = (struct Date*) malloc(sizeof(struct Date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

void dateToString(struct Date* d, char s[15]) {
    char buf[6];

    sprintf_s(buf, 3, "%d", d->day);
    strcpy_s(s, 15, buf);

    strcat_s(s, 15, "/");

    sprintf_s(buf, 3, "%d", d->month);
    strcat_s(s, 15, buf);

    strcat_s(s, 15, "/");

    sprintf_s(buf, 5, "%d", d->year);
    strcat_s(s, 15, buf);
}

#endif //PROJECT1_DATE_H