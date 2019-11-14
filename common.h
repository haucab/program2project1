#ifndef PROJECT1_COMMON_H
#define PROJECT1_COMMON_H

#include <stdlib.h>
#include <stdio.h>

#if _MSC_VER >= 1800
  #include <stdbool.h>
#else
//|//
#ifndef _MSC_VER
#include <stdbool.h>
#endif
//|//
#endif

#include <string.h>

bool stringContieneAString(char* c1, char* c2) {
    return strstr(c1, c2) != NULL;
}

bool stringIgualAString(char* c1, char* c2) {
    return strcmp(c1, c2) == 0;
}

bool stringIsEmptyOrNull_s(char* c, rsize_t s) {
    if (!c) return true;
    char* newptr = c;
    for (rsize_t i = 0; i < s; i++,newptr++) {
        char newc = *newptr;
        if (newc == 0) return true;
        if ((newc != ' ') && (newc != '\t')) return false;
    }
    return true;
}

void gets_truncate(char* s, rsize_t size) {
    fgets(s, size, stdin);
    s[strcspn(s, "\r\n")] = 0; // Drops newline
}

long long strtoll_compat(char const* string, char** endptr, int radix) {
#if _MSC_VER >= 1800
    return strtoll(string, endptr, radix);
#else
    #ifndef _MSC_VER
        #ifdef __STDC_VERSION__
            #if __STDC_VERSION__ >= 199901L
                return strtoll(string, endptr, radix);
            #else
                return (long long) strtol(string, endptr, radix);
            #endif
        #else
            return (long long) strtol(string, endptr, radix);
        #endif
    #else
        return (long long) strtol(string, endptr, radix);
    #endif
#endif
}

#endif //PROJECT1_COMMON_H
