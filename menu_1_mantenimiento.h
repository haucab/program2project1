#ifndef PROJECT1_MENU_1_MANTENIMIENTO_H
#define PROJECT1_MENU_1_MANTENIMIENTO_H

#include "common.h"
#include "common_cli_windows.h"
#include "persona.h"
#include "sucursal.h"
#include "paquete.h"
#include "file_ops.h"

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
void menuMantenimientoPersonas_op4(struct Persona** cabezaP, struct Sucursal** cabezaS);
void menuMantenimientoPersonas_op5(struct Persona** cabeza);
void menuMantenimientoPersonas(struct Persona** cabezaP, struct Sucursal** cabezaS) {
    int opc = 99;
    while (opc != 6) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuPersonasPrintf, NULL);
        switch (opc) {
            case 1:
                menuMantenimientoPersonas_op1(cabezaP);
				fputs_personas(*cabezaP, "personas.dat");
                break;
            case 2:
                menuMantenimientoPersonas_op2(cabezaP);
                break;
            case 3:
                menuMantenimientoPersonas_op3(cabezaP);
				fputs_personas(*cabezaP, "personas.dat");
                break;
            case 4:
                menuMantenimientoPersonas_op4(cabezaP, cabezaS);
				fputs_personas(*cabezaP, "personas.dat");
                break;
            case 5:
                menuMantenimientoPersonas_op5(cabezaP);
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
				fputs_sucursales(*cabeza, "sucursales.dat");
				fputs_envios(*cabeza, "envios.dat");
                break;
            case 2:
                menuMantenimientoSucursales_op2(cabeza);
                break;
            case 3:
                menuMantenimientoSucursales_op3(cabeza);
				fputs_sucursales(*cabeza, "sucursales.dat");
				fputs_envios(*cabeza, "envios.dat");
                break;
            case 4:
                menuMantenimientoSucursales_op4(cabeza);
				fputs_sucursales(*cabeza, "sucursales.dat");
				fputs_envios(*cabeza, "envios.dat");
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
                menuMantenimientoPersonas(cabezaP, cabezaS);
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
    printf("Cedula/Pasaporte de la persona a modificar: ");
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
			ValidationError_Persona valPer;
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
                    valPer = validatePersonaEmail(email);
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
void menuMantenimientoPersonas_op4(struct Persona** cabezaP, struct Sucursal** cabezaS) {
    system("cls");
    printf("ELIMINAR PERSONA\n\n");

    char id[15];
    printf("Cedula/Pasaporte de la persona a eliminar: ");
    gets_truncate(id, 15);

    struct Persona* p = consultarPersonaID(cabezaP, id);
    if (!p) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printPersona(p);
        printf("----------------------------------------------------------\n");
        printf("Esta seguro de que desea eliminar la persona indicada?\n");
        printf("NOTA: Cualquier envio hecho por dicha persona sera eliminado.\n");
        printf("(Presione la tecla 's'para confirmar, cualquier otra tecla para cancelar) > ");
        int currchar = getcharnobuf();
        if (currchar == 's' || currchar == 'S') {
            printf("INFO: Procesando...\n");
            eliminarPersona(cabezaP, id);
            struct Sucursal* s = *cabezaS;
            while (s) {
                struct EnvioPaquete* paquete = s->sentPackages;
                while (paquete) {
                    if (stringIgualAString(paquete->idSender, id)) {
                        paquete = paquete->prox;
                        eliminarEnvio(cabezaS, id);
                    } else {
                        paquete = paquete->prox;
                    }
                }
                s = s->prox;
            }
            printf("INFO: Operacion realizada exitosamente.\n");
        } else {
            printf("INFO: Operacion cancelada por el usuario.\n");
        }
    }
    system("pause");
}

// v - Consultar persona por nombre
void menuMantenimientoPersonas_op5(struct Persona** cabezaP){
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

    struct BusquedaPersonas* bp = consultarPersonaNombre(cabezaP, fnames, lnames);
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

// -----------------------------------------------------------------------------------------------------------------

// v - Agregar sucursal
void menuMantenimientoSucursales_op1(struct Sucursal** cabeza) {
    system("cls");
    printf("AGREGAR SUCURSAL\n\n");

    char code[25];
    printf("Codigo sucursal: ");
    gets_truncate(code, 25);
    ValidationError_Sucursal valPer = validateSucursalId(cabeza, code);
    while (valPer != SUCURSAL_OK) {
        printf("ERROR: La identificacion dada ya existe en el sistema.\n\n");
        printf("Cedula/Pasaporte: ");
        gets_truncate(code, 25);
        valPer = validateSucursalId(cabeza, code);
    }

    char name[50];
    printf("Nombre: ");
    gets_truncate(name, 50);

    char streetadress[150];
    printf("Direccion: ");
    gets_truncate(streetadress, 150);

    char email[50];
    printf("Correo electronico: ");
    gets_truncate(email, 50);
    valPer = validateSucursalEmail(email);
    while (valPer != SUCURSAL_OK) {
        printf("ERROR: El correo electronico que usted ha dado no es valido.\n\n");
        printf("Correo electronico: ");
        gets_truncate(email, 50);
        valPer = validateSucursalEmail(email);
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

    agregarSucursal(cabeza, code, name, streetadress, email, city, state, country, phoneNumber);

    printf("\n\nHa sido agregado exitosamente la sucursal %s (codigo: %s) al sistema!\n\n", name, code);
    printf("INFO: Operacion realizada exitosamente.\n\n");
    system("pause");
}

// v - Consultar sucursal
void menuMantenimientoSucursales_op2(struct Sucursal** cabeza) {
    system("cls");
    printf("CONSULTAR SUCURSAL\n\n");

    char code[25];
    printf("Codigo de la sucursal a consultar: ");
    gets_truncate(code, 25);

    struct Sucursal* s = consultarSucursal(cabeza, code);
    if (!s) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printSucursal(s);
        printf("----------------------------------------------------------\n");
    }
    system("pause");
}

// v - Modificar sucursal
void __restricted__MenuMantenimientoModificarSucursalPrintf(void* sucursal) {
    printf("MODIFICAR SUCURSAL\n\n");
    struct Sucursal** s2 = (struct Sucursal**)sucursal;
    struct Sucursal* s = *s2;
    printf("\n");
    printf("----------------------------------------------------------\n");
    printSucursal(s);
    printf("[8] Guardar y regresar al menu anterior.");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("Introduzca en el teclado el numero correspondiente al dato que desea modificar y presione ENTER.\n");
    printf(" > ");
}
void menuMantenimientoSucursales_op3(struct Sucursal** cabeza) {
    system("cls");
    printf("MODIFICAR SUCURSAL\n\n");

    char code[25];
    printf("Codigo de la sucursal a modificar: ");
    gets_truncate(code, 25);

    struct Sucursal* s = consultarSucursal(cabeza, code);
    if (!s) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
        system("pause");
    } else {
        int opc = 99;
        while (opc != 8) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuMantenimientoModificarSucursalPrintf, &s);
			ValidationError_Persona valPer;
            switch (opc) {
                case 1:
                    // Change last name
                    char name[50];
                    printf("Nombre: ");
                    gets_truncate(name, 50);
                    strcpy_s(s->name, 50, name);
                    break;
                case 2:
                    // Change street adress
                    char streetadress[150];
                    printf("Direccion: ");
                    gets_truncate(streetadress, 150);
                    strcpy_s(s->streetaddress, 150, streetadress);
                    break;
                case 3:
                    // Change email address
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
                    strcpy_s(s->email, 50, email);
                    break;
                case 4:
                    // Change city
                    char city[30];
                    printf("Ciudad: ");
                    gets_truncate(city, 30);
                    strcpy_s(s->city, 30, city);
                    break;
                case 5:
                    // Change state
                    char state[30];
                    printf("Estado: ");
                    gets_truncate(state, 30);
                    strcpy_s(s->state, 30, state);
                    break;
                case 6:
                    // Change country
                    char country[30];
                    printf("Pais: ");
                    gets_truncate(country, 30);
                    strcpy_s(s->country, 30, country);
                    break;
                case 7:
                    // Change phone number
                    char phoneNumber[20];
                    printf("Telefono: ");
                    gets_truncate(phoneNumber, 20);
                    strcpy_s(s->phoneNumber, 20, phoneNumber);
                    break;
                case 8: break;
                default:
                    printf(" [Opcion invalida]\n");
                    system("pause");
                    break;
            }
        }
    }
}

// v - Eliminar sucursal
void __restricted__MenuMantenimientoEliminarSucursalPrintf(void* sucursal) {
    printf("ELIMINAR SUCURSAL\n\n");
    struct Sucursal** s2 = (struct Sucursal**)sucursal;
    struct Sucursal* s = *s2;
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf(" Codigo sucursal: %s\n", s->code);
    printf(" Nombre: %s\n", s->name);
    printf(" Direccion: %s\n", s->streetaddress);
    printf(" Correo electronico: %s\n", s->email);
    printf(" Ciudad: %s\n", s->city);
    printf(" Estado: %s\n", s->state);
    printf(" Pais: %s\n", s->country);
    printf(" Telefono: %s\n", s->phoneNumber);
    printf("----------------------------------------------------------\n");
    printf("Desea:\n");
    printf("[1] Mover transacciones a otra sucursal?\n");
    printf("[2] Archivar transacciones y eliminarlas del sistema principal?\n");
    printf("\n");
    printf("\n");
    printf("Introduzca en el teclado el numero correspondiente a la accion que desea tomar y presione ENTER.\n");
    printf(" > ");
}
void __restricted__moveToOtherSucursal(struct Sucursal* sucursal, char newcode[25]) {
    char oldcode[25];
    strcpy_s(oldcode, 25, sucursal->code);

    struct Sucursal* cabeza = sucursal;
    while (cabeza && cabeza->prev) {
        cabeza = cabeza->prev;
    }

    struct Sucursal* newSucursal = consultarSucursal(&cabeza, newcode);
    newSucursal->sentPackages = sucursal->sentPackages;
    newSucursal->receivedPackages = sucursal->receivedPackages;
    sucursal->sentPackages = NULL;
    sucursal->receivedPackages = NULL;

    struct Sucursal* s = cabeza;
    for (; s; s = s->prox) {
        if (stringIgualAString(s->code, oldcode)) continue;
        struct EnvioPaquete* envios = s->sentPackages;
        struct ReciboPaquete* recibos = s->receivedPackages;
        for (; envios; envios = envios->prox) {
            if (stringIgualAString(envios->codeDestinationSucursal, oldcode)) strcpy_s(envios->codeDestinationSucursal, 25, newcode);
        }
        for (; recibos; recibos = recibos->prox) {
            if (stringIgualAString(recibos->codeOriginSucursal, oldcode)) strcpy_s(recibos->codeOriginSucursal, 25, newcode);
        }
    }
}
void __restricted__saveToHistoricFile(struct Sucursal* sucursal, char ignored[25]) {
    struct EnvioPaquete* enviosHistoricCabeza = fget_envios_legacy("envios_historicos.dat");
    struct EnvioPaquete* envioAux;
    while (sucursal->sentPackages) {
        envioAux = sucursal->sentPackages;
        sucursal->sentPackages = sucursal->sentPackages->prox;
        if (sucursal->sentPackages) sucursal->sentPackages->prev = NULL;
        envioAux->prox = enviosHistoricCabeza;
        if (enviosHistoricCabeza) enviosHistoricCabeza->prev = envioAux;
        enviosHistoricCabeza = envioAux;
    }
    fputs_envios_legacy(enviosHistoricCabeza, "envios_historicos.dat");
    while (enviosHistoricCabeza) {
        envioAux = enviosHistoricCabeza;
        enviosHistoricCabeza = enviosHistoricCabeza->prox;
        if (enviosHistoricCabeza) enviosHistoricCabeza->prev = NULL;
        free(envioAux);
    }
}
void menuMantenimientoSucursales_op4(struct Sucursal** cabeza) {
    system("cls");
    printf("ELIMINAR SUCURSAL\n\n");

    char code[25];
    printf("Codigo de la sucursal a eliminar: ");
    gets_truncate(code, 25);

    struct Sucursal* s = consultarSucursal(cabeza, code);
    if (!s) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printSucursal(s);
        printf("----------------------------------------------------------\n");
        printf("Esta seguro de que desea eliminar la persona indicada?\n");
        printf("(Presione la tecla 's'para confirmar, cualquier otra tecla para cancelar) > ");
        int currchar = getcharnobuf();
        if (currchar == 's' || currchar == 'S') {
            int opc = 99;
            SucursalDeleteCallback callbackptr;
            char possiblecode[25];
            while (true) {
                system("cls");
                scanf_integer(&opc, &__restricted__MenuMantenimientoEliminarSucursalPrintf, &s);
                switch (opc) {
                    case 1:
                        printf("Codigo sucursal a ser asignada las transacciones: ");
                        gets_truncate(possiblecode, 25);
                        while (consultarSucursal(cabeza, possiblecode) == NULL || stringIgualAString(possiblecode, code)) {
                            printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
                            printf("Codigo sucursal a ser asignada las transacciones: ");
                            gets_truncate(possiblecode, 25);
                        }
                        callbackptr = &__restricted__moveToOtherSucursal;
                        break;
                    case 2:
                        possiblecode[0] = '\0';
                        callbackptr = &__restricted__saveToHistoricFile;
                        break;
                    default:
                        printf(" [Opcion invalida]\n");
                        system("pause");
                        continue;
                }
                break;
            }

            printf("INFO: Procesando...\n");
            eliminarSucursal(cabeza, code, callbackptr, possiblecode);
            printf("INFO: Operacion realizada exitosamente.\n");
        } else {
            printf("INFO: Operacion cancelada por el usuario.\n");
        }
    }
    system("pause");
}

#endif //PROJECT1_MENU_1_MANTENIMIENTO_H
