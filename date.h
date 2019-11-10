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

#endif //PROJECT1_DATE_H