#ifndef PROJECT1_MENU_1_MANTENIMIENTO_H
#define PROJECT1_MENU_1_MANTENIMIENTO_H

#include "common.h"
#include "common_cli_windows.h"

void __restricted__MenuPersonasPrintf(void) {
    printf("+--------------------------------------------------------+\n");
    printf("+------------------ Mantenimiento Personas --------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                     1. Agregar Persona                 |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              2.  Consultar Persona por Cedula          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                    3. Modificar Persona                |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                    4.  Eliminar Persona                |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              5.  Consultar Persona por Nombre          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                6. Regresar al menu anterior            |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void menuPersonas(void) {

    int opc;

    opc = 99;

    system("cls");

    while(opc != 0){
        scanf_integer(&opc, &__restricted__MenuPersonasPrintf);

        switch (opc){
            case 1:break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:break;
            default:break;
        }
    }

    system("cls");
}

void menuSucursales(void){

    int opc;

    opc = 99;

    system("cls");

    while(opc != 0){

        gotoxy(28,5);
        printf("Mantenimiento Sucursales");
        gotoxy(28,7);
        printf("1.Agregar Sucursal");
        gotoxy(28,8);
        printf("2.Consultar Sucursal");
        gotoxy(28,9);
        printf("3.Modificar Sucursal");
        gotoxy(28,10);
        printf("4.Eliminar Sucursal");
        gotoxy(28,11);
        printf("0.Salir");
        gotoxy(28,13);
        printf("Digite una Opcion[   ]");
        gotoxy(47,13);
        scanf("%d",&opc);

        switch(opc){

            case 1:break;
            case 2:break;
            case 3:break;
            case 4:break;
        }
    }

    system("cls");
}

#endif //PROJECT1_MENU_1_MANTENIMIENTO_H
