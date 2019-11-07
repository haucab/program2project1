#ifndef PROJECT1_COMMON_H
#define PROJECT1_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool stringContieneAString(char* c1, char* c2) {
    return strstr(c1, c2) != NULL;
}

bool stringIgualAString(char* c1, char* c2) {
    return strcmp(c1, c2) == 0;
}

#endif //PROJECT1_COMMON_H
