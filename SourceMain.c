#include "common.h"
#include "common_cli_windows.h"
#include "sucursal.h"
#include "utils.h"

void printffunc(void) {
    printf("You said: ");
}

int main(void) {
    printf("Hello, World!\n");
    printffunc();
    int result = 0;
    scanf_integer(&result, &printffunc);
    printf("\nResult: %i\n", result);
    system("pause");
    return 0;
}
