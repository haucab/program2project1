#ifndef PROJECT1_MENU_1_MANTENIMIENTO_H
#define PROJECT1_MENU_1_MANTENIMIENTO_H

#include "common.h"
#include "common_cli_windows.h"
#include "persona.h"
#include "sucursal.h"

void __restricted__MenuPersonasPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+---------------- Mantenimiento Personas ----------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                   1. Agregar Persona                   |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|            2.  Consultar Persona por Cedula            |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                  3. Modificar Persona                  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                  4.  Eliminar Persona                  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|            5.  Consultar Persona por Nombre            |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              6. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void __restricted__MenuSucursalesPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+--------------- Mantenimiento Sucursales ---------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                  1. Agregar Sucursal                   |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                 2. Consultar Sucursal                  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                 3. Modificar Sucursal                  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                 4.  Eliminar Sucursal                  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              5. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void __restricted__MenuMantenimientoPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+--------------------- Mantenimiento --------------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|               1.  Mantenimiento personas               |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|             2. Mantenimiento de Sucursales             |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                        3.  Salir                       |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void menuMantenimientoPersonas_op1(struct Persona** cabeza);
void menuMantenimientoPersonas_op2(struct Persona** cabeza);
void menuMantenimientoPersonas_op3(struct Persona** cabeza);
void menuMantenimientoPersonas_op4(struct Persona** cabeza);
void menuMantenimientoPersonas_op5(struct Persona** cabeza);
void menuMantenimientoPersonas(struct Persona** cabeza) {
    int opc = 99;
    while (opc != 6) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuPersonasPrintf, NULL);
        switch (opc) {
            case 1:
                menuMantenimientoPersonas_op1(cabeza);
                break;
            case 2:
                menuMantenimientoPersonas_op2(cabeza);
                break;
            case 3:
                menuMantenimientoPersonas_op3(cabeza);
                break;
            case 4:
                menuMantenimientoPersonas_op4(cabeza);
                break;
            case 5:
                menuMantenimientoPersonas_op5(cabeza);
                break;
            case 6: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}

void menuMantenimientoSucursales_op1(struct Sucursal** cabeza);
void menuMantenimientoSucursales_op2(struct Sucursal** cabeza);
void menuMantenimientoSucursales_op3(struct Sucursal** cabeza);
void menuMantenimientoSucursales_op4(struct Sucursal** cabeza);
void menuMantenimientoSucursales(struct Sucursal** cabeza){
    int opc = 99;
    while (opc != 5) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuSucursalesPrintf, NULL);
        switch (opc) {
            case 1:
                menuMantenimientoSucursales_op1(cabeza);
                break;
            case 2:
                menuMantenimientoSucursales_op2(cabeza);
                break;
            case 3:
                menuMantenimientoSucursales_op3(cabeza);
                break;
            case 4:
                menuMantenimientoSucursales_op4(cabeza);
                break;
            case 5: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}

void menuMantenimiento(struct Persona** cabezaP, struct Sucursal** cabezaS){
    int opc = 99;
    while (opc != 3) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuMantenimientoPrintf, NULL);
        switch (opc) {
            case 1:
                menuMantenimientoPersonas(cabezaP);
                break;
            case 2:
                menuMantenimientoSucursales(cabezaS);
                break;
            case 3: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}

// -----------------------------------------------------------------------


// v - Agregar persona
void menuMantenimientoPersonas_op1(struct Persona** cabeza) {
    system("cls");
    printf("AGREGAR PERSONA\n\n");

    char id[15];
    printf("Cedula/Pasaporte: ");
    gets_truncate(id, 15);
    ValidationError_Persona valPer = validatePersonaId(cabeza, id);
    while (valPer != PERSONA_OK) {
        printf("ERROR: La identificacion dada ya existe en el sistema.\n\n");
        printf("Cedula/Pasaporte: ");
        gets_truncate(id, 15);
        valPer = validatePersonaId(cabeza, id);
    }

    char fnames[50];
    printf("Nombres: ");
    gets_truncate(fnames, 50);

    char lnames[50];
    printf("Apellidos: ");
    gets_truncate(lnames, 50);

    char streetadress[150];
    printf("Direccion: ");
    gets_truncate(streetadress, 150);

    char email[50];
    printf("Correo electronico: ");
    gets_truncate(email, 50);
    valPer = validatePersonaEmail(email);
    while (valPer != PERSONA_OK) {
        printf("ERROR: El correo electronico que usted ha dado no es valido.\n\n");
        printf("Correo electronico: ");
        gets_truncate(email, 50);
        valPer = validatePersonaEmail(email);
    }

    char city[30];
    printf("Ciudad: ");
    gets_truncate(city, 30);

    char state[30];
    printf("Estado: ");
    gets_truncate(state, 30);

    char country[30];
    printf("Pais: ");
    gets_truncate(country, 30);

    char phoneNumber[20];
    printf("Telefono: ");
    gets_truncate(phoneNumber, 20);


    printf("INFO: Procesando...");

    agregarPersona(cabeza, id, fnames, lnames, streetadress, email, city, state, country, phoneNumber);

    printf("\n\nHa sido agregado exitosamente la persona %s %s (CI/Pasaporte: %s) al sistema!\n\n", fnames, lnames, id);
    printf("INFO: Operacion realizada exitosamente.\n\n");
    system("pause");
}

// v - Consultar persona por ID
void menuMantenimientoPersonas_op2(struct Persona** cabeza) {
    system("cls");
    printf("CONSULTAR PERSONA POR ID\n\n");

    char id[15];
    printf("Cedula/Pasaporte de la persona a consultar: ");
    gets_truncate(id, 15);

    struct Persona* p = consultarPersonaID(cabeza, id);
    if (!p) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printPersona(p);
        printf("----------------------------------------------------------\n");
    }
    system("pause");
}

// v - Modificar persona
void __restricted__MenuMantenimientoModificarPersonaPrintf(void* persona) {
    printf("MODIFICAR PERSONA\n\n");
    struct Persona** p2 = (struct Persona**)persona;
    struct Persona* p = *p2;
    printf("\n");
    printf("----------------------------------------------------------\n");
    printPersona(p);
    printf("[9] Guardar y regresar al menu anterior.");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("Introduzca en el teclado el numero correspondiente al dato que desea modificar y presione ENTER.\n");
    printf(" > ");
}
void menuMantenimientoPersonas_op3(struct Persona** cabeza) {
    system("cls");
    printf("MODIFICAR PERSONA\n\n");

    char id[15];
    printf("Cedula/Pasaporte de la persona a consultar: ");
    gets_truncate(id, 15);

    struct Persona* p = consultarPersonaID(cabeza, id);
    if (!p) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
        system("pause");
    } else {
        int opc = 99;
        while (opc != 9) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuMantenimientoModificarPersonaPrintf, &p);
            switch (opc) {
                case 1:
                    // Change first name
                    char fnames[50];
                    printf("Nombres: ");
                    gets_truncate(fnames, 50);
                    strcpy_s(p->fnames, 50, fnames);
                    break;
                case 2:
                    // Change last name
                    char lnames[50];
                    printf("Apellidos: ");
                    gets_truncate(lnames, 50);
                    strcpy_s(p->lnames, 50, lnames);
                    break;
                case 3:
                    // Change street adress
                    char streetadress[150];
                    printf("Direccion: ");
                    gets_truncate(streetadress, 150);
                    strcpy_s(p->streetaddress, 150, streetadress);
                    break;
                case 4:
                    // Change email address
                    char email[50];
                    printf("Correo electronico: ");
                    gets_truncate(email, 50);
                    ValidationError_Persona valPer = validatePersonaEmail(email);
                    while (valPer != PERSONA_OK) {
                        printf("ERROR: El correo electronico que usted ha dado no es valido.\n\n");
                        printf("Correo electronico: ");
                        gets_truncate(email, 50);
                        valPer = validatePersonaEmail(email);
                    }
                    strcpy_s(p->email, 50, email);
                    break;
                case 5:
                    // Change city
                    char city[30];
                    printf("Ciudad: ");
                    gets_truncate(city, 30);
                    strcpy_s(p->city, 30, city);
                    break;
                case 6:
                    // Change state
                    char state[30];
                    printf("Estado: ");
                    gets_truncate(state, 30);
                    strcpy_s(p->state, 30, state);
                    break;
                case 7:
                    // Change country
                    char country[30];
                    printf("Pais: ");
                    gets_truncate(country, 30);
                    strcpy_s(p->country, 30, country);
                    break;
                case 8:
                    // Change phone number
                    char phoneNumber[20];
                    printf("Telefono: ");
                    gets_truncate(phoneNumber, 20);
                    strcpy_s(p->phoneNumber, 20, phoneNumber);
                    break;
                case 9: break;
                default:
                    printf(" [Opcion invalida]\n");
                    system("pause");
                    break;
            }
        }
    }
}

// v - Eliminar persona
void menuMantenimientoPersonas_op4(struct Persona** cabeza) {
    system("cls");
    printf("ELIMINAR PERSONA\n\n");

    char id[15];
    printf("Cedula/Pasaporte de la persona a eliminar: ");
    gets_truncate(id, 15);

    struct Persona* p = consultarPersonaID(cabeza, id);
    if (!p) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printPersona(p);
        printf("----------------------------------------------------------\n");
        printf("Esta seguro de que desea eliminar la persona indicada?\n");
        printf("(Presione la tecla 's'para confirmar, cualquier otra tecla para cancelar) > ");
        int currchar = getcharnobuf();
        if (currchar == 's' || currchar == 'S') {
            printf("INFO: Procesando...\n");
            eliminarPersona(cabeza, id);
            printf("INFO: Operacion realizada exitosamente.\n");
        } else {
            printf("INFO: Operacion cancelada por el usuario.\n");
        }
    }
    system("pause");
}

// v - Consultar persona por nombre
void menuMantenimientoPersonas_op5(struct Persona** cabeza){
    system("cls");
    printf("CONSULTAR PERSONA POR NOMBRE\n\n");

    char fnames[50], lnames[50];
    while (true) {
        printf("Nombres (dejar en blanco si solo desea buscar por apellidos): ");
        gets_truncate(fnames, 50);
        printf("Apellidos (dejar en blanco si solo desea buscar por nombres): ");
        gets_truncate(lnames, 50);
        if (!stringIsEmptyOrNull_s(fnames, 50) || !stringIsEmptyOrNull_s(lnames, 50)) {
            break;
        }
        printf("ERROR: Debe al menos rellenar una de las anteriores casillas.\n\n");
    }

    struct BusquedaPersonas* bp = consultarPersonaNombre(cabeza, fnames, lnames);
    if (!bp) {
        printf("\n");
        printf("INFO: No hay nadie registrado en el sistema con los parametros de busqueda dados.\n\n");
    } else {
        printf("\n");
        printf("Formato: [Cedula o Pasaporte] Apellidos, Nombres\n");
        printf("----------------------------------------------------------\n");
        while (bp) {
            struct Persona* p = bp->valor;
            printf("[%s] %s, %s", p->id, p->lnames, p->fnames);

            bp = bp->prox;
        }
        printf("----------------------------------------------------------\n\n");
    }
    system("pause");
}



void menuMantenimientoSucursales_op1(struct Sucursal** cabeza) {

}
void menuMantenimientoSucursales_op2(struct Sucursal** cabeza) {

}
void menuMantenimientoSucursales_op3(struct Sucursal** cabeza) {

}
void menuMantenimientoSucursales_op4(struct Sucursal** cabeza) {

}

#endif //PROJECT1_MENU_1_MANTENIMIENTO_H
