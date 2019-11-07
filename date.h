#ifndef PROJECT1_DATE_H
#define PROJECT1_DATE_H

struct Date {
    int day, month, year;
};

struct Date* newDate(int day, int month, int year) {
    struct Date* d = (struct Date*) malloc(sizeof(struct Date));
    d->day = day;
    d->month = month;
    d->year = year;
}

#endif //PROJECT1_DATE_H