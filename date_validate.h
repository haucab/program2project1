#ifndef PROJECT1_DATE_VALIDATE_H
#define PROJECT1_DATE_VALIDATE_H

typedef enum {
    DATE_OK, ERR_NOT_LEAP_YEAR, ERR_DAY_INVALID, ERR_MONTH_INVALID
} ValidationError_Date;

ValidationError_Date validateDateMonth(unsigned int month) {
    if (month > 12) return ERR_MONTH_INVALID;
    else return DATE_OK;
}

ValidationError_Date __private__validateDatePreAugust(unsigned short day, unsigned short int month, short year) {
    if (month % 2 == 0) {
        if (month == 2) {
            if (day > 29) return ERR_DAY_INVALID;
            if (year % 4 != 0) {
                if (day == 29) return ERR_NOT_LEAP_YEAR;
            }
        } else if (day > 30) return ERR_DAY_INVALID;
    } else if (day > 31) return ERR_DAY_INVALID;

    return DATE_OK;
}

ValidationError_Date __private__validateDatePostAugust(unsigned short day, unsigned short month) {
    if (day > (month % 2 == 0 ? 31 : 30)) return ERR_DAY_INVALID;
    else return DATE_OK;
}

ValidationError_Date validateDate(unsigned short day, unsigned short month, short year) {
    ValidationError_Date validMonth = validateDateMonth(month);
    if (validMonth != DATE_OK) return validMonth;
    if (month < 8) return __private__validateDatePreAugust(day, month, year);
    else return __private__validateDatePostAugust(day, month);
}

#endif //PROJECT1_DATE_VALIDATE_H
