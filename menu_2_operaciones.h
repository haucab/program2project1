#ifndef PROJECT1_MENU_2_OPERACIONES_H
#define PROJECT1_MENU_2_OPERACIONES_H

#include "common.h"
#include "common_cli_windows.h"
#include "persona.h"
#include "sucursal.h"
#include "paquete.h"
#include "file_ops.h"

void __restricted__MenuEnviosPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+----------------- Mantenimiento Envios -----------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                    1. Agregar Envio                    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                   2. Consultar Envio                   |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                   3. Modificar Envio                   |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                   4.  Eliminar Envio                   |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              5. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void menuMantenimientoEnvios_op1(struct Sucursal** cabeza);
void menuMantenimientoEnvios_op2(struct Sucursal** cabeza);
void menuMantenimientoEnvios_op3(struct Sucursal** cabeza);
void menuMantenimientoEnvios_op4(struct Sucursal** cabeza);
void menuMantenimientoEnvios(struct Sucursal** cabeza){
    int opc = 99;
    while (opc != 5) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuEnviosPrintf, NULL);
        switch (opc) {
            case 1:
                menuMantenimientoEnvios_op1(cabeza);
                break;
            case 2:
                menuMantenimientoEnvios_op2(cabeza);
                break;
            case 3:
                menuMantenimientoEnvios_op3(cabeza);
                break;
            case 4:
                menuMantenimientoEnvios_op4(cabeza);
                break;
            case 5: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}

// v - Agregar envio
void menuMantenimientoEnvios_op1(struct Sucursal** cabeza) {

}

// v - Consultar envio
void menuMantenimientoEnvios_op2(struct Sucursal** cabeza) {

}

// v - Actualizar envio
void menuMantenimientoEnvios_op3(struct Sucursal** cabeza) {

}

// v - Eliminar envio
void menuMantenimientoEnvios_op4(struct Sucursal** cabeza) {

}


#endif //PROJECT1_MENU_2_OPERACIONES_H
