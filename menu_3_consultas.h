#ifndef PROJECT1_MENU_3_CONSULTAS_H
#define PROJECT1_MENU_3_CONSULTAS_H

#include "common.h"
#include "common_cli_windows.h"
#include "sucursal.h"
#include "paquete.h"
#include "persona.h"

void __restricted__MenuConsultasPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+----------------------  Consultas ----------------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|           1. Dada la cedula de un cliente...           |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|          2. Dado el codigo de una sucursal...          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    3. Mostrar clientes con mayor cantidad de envios    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    4.  Mostrar sucursales por cantidad de envios...    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    5. Mostrar sucursales por cantidad de recibos...    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    6.  Mostrar las cedulas de los no registrados...    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              7. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

void menuOperaciones_op1(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op2(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op3(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op4(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op5(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op6(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    int opc = 99;
    while (opc != 7) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuConsultasPrintf, NULL);
        switch (opc) {
            case 1:
                menuOperaciones_op1(cabezaS, cabezaP);
                break;
            case 2:
                menuOperaciones_op2(cabezaS, cabezaP);
                break;
            case 3:
                menuOperaciones_op3(cabezaS, cabezaP);
                break;
            case 4:
                menuOperaciones_op4(cabezaS, cabezaP);
                break;
            case 5:
                menuOperaciones_op5(cabezaS, cabezaP);
                break;
            case 6:
                menuOperaciones_op6(cabezaS, cabezaP);
                break;
            case 7: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}

void __restricted__MenuConsultas_3_1_Printf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+------------- Dada la cedula de un cliente -------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|        1. Mostrar envios ordenados por fecha...        |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|       2.  Mostrar detalles de una transaccion...       |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              3. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}
void menuOperaciones_op1(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    system("cls");
    printf("CONSULTA 3.1\n\n");

    char id[15];
    printf("Cedula/Pasaporte de la persona: ");
    gets_truncate(id, 15);

    struct Persona* p = consultarPersonaID(cabezaP, id);
    if (!p) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
        system("pause");
    } else {
        int opc = 99;
        while (opc != 9) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuConsultas_3_1_Printf, NULL);
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
                case 3: break;
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

#endif //PROJECT1_MENU_3_CONSULTAS_H
