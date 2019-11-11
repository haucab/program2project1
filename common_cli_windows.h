#ifndef PROJECT1_COMMON_CLI_WINDOWS_H
#define PROJECT1_COMMON_CLI_WINDOWS_H

#include "common.h"
#include "conio.h"
#include <Windows.h>

#define KEY_BACKSPACE 8
#define KEY_ENTER 13

#define __private__c0 '0'
#define __private__c9 '9'

typedef void (*PrintfCallback)(void);

int getcharnobuf(void) {
    return _getch();
}

void __private__printZeroes(int z) {
    for (int i = 0; i < z; i++) {
        printf("%i", 0);
    }
}

void scanf_integer(int* result, PrintfCallback callback) {
    int resultTemp = 0;
    int zeroCounter = 0;

    for (int currchar = getcharnobuf(); currchar != KEY_ENTER; currchar = getcharnobuf()) {
        system("cls");
        callback();
        if (currchar != KEY_BACKSPACE && (currchar < __private__c0 || currchar > __private__c9)) {
            __private__printZeroes(zeroCounter);
            if (resultTemp != 0) printf("%i ", resultTemp);
            printf("[%c no es un digito del 1 al 9]", currchar);
        } else if (currchar == KEY_BACKSPACE) {
            if (resultTemp == 0) {
                if (zeroCounter != 0) if (--zeroCounter != 0) {
                    __private__printZeroes(zeroCounter);
                }
                continue;
            }
            resultTemp /= 10;
            __private__printZeroes(zeroCounter);
            if (resultTemp != 0) printf("%i", resultTemp);
        } else {
            int newResult = resultTemp * 10;
            if (newResult < resultTemp) {
                printf("%i ", resultTemp);
                printf("[%i%c es un numero muy grande]", resultTemp, currchar);
            } else {
                int digit = currchar - __private__c0;

                if (digit == 0 && resultTemp == 0) {
                    __private__printZeroes(++zeroCounter);
                } else {
                    resultTemp = newResult + digit;
                    __private__printZeroes(zeroCounter);
                    printf("%i", resultTemp);
                }
            }
        }
    }
    *result = resultTemp;
}

void gotoxy(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}

#endif //PROJECT1_COMMON_CLI_WINDOWS_H
