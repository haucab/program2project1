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
    printf("+---------------------  Operaciones --------------------+\n");
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

void menuOperaciones_op1(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op2(struct Sucursal** cabeza);
void menuOperaciones_op3(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuOperaciones_op4(struct Sucursal** cabeza);
void menuOperaciones(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    int opc = 99;
    while (opc != 5) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuEnviosPrintf, NULL);
        switch (opc) {
            case 1:
                menuOperaciones_op1(cabezaS, cabezaP);
				fputs_envios(*cabezaS, "envios.dat");
                break;
            case 2:
                menuOperaciones_op2(cabezaS);
                break;
            case 3:
                menuOperaciones_op3(cabezaS, cabezaP);
				fputs_envios(*cabezaS, "envios.dat");
                break;
            case 4:
                menuOperaciones_op4(cabezaS);
				fputs_envios(*cabezaS, "envios.dat");
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
void menuOperaciones_op1(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    system("cls");
    printf("AGREGAR ENVIO\n\n");

    char codeDelivery[25];
    printf("Codigo de envio: ");
    gets_truncate(codeDelivery, 25);
    ValidationError_Paquete valPaq = validatePaqueteCodeDelivery(*cabezaS, codeDelivery);
    while (valPaq != PAQUETE_OK) {
        printf("ERROR: La identificacion dada ya existe en el sistema.\n\n");
        printf("Codigo de envio: ");
        gets_truncate(codeDelivery, 25);
        valPaq = validatePaqueteCodeDelivery(*cabezaS, codeDelivery);
    }

    char codeOriginSucursal[25], codeDestinationSucursal[25];
    while (true) {
        printf("Codigo sucursal origen: ");
        gets_truncate(codeOriginSucursal, 25);
        valPaq = validatePaqueteOrigin(*cabezaS, codeOriginSucursal);
        while (valPaq == ERR_ORIGIN_INVALID) {
            printf("ERROR: La sucursal dada no existe en el sistema.\n\n");
            printf("Codigo sucursal origen: ");
            gets_truncate(codeOriginSucursal, 25);
            valPaq = validatePaqueteOrigin(*cabezaS, codeOriginSucursal);
        }

        printf("Codigo sucursal destino: ");
        gets_truncate(codeDestinationSucursal, 25);
        valPaq = validatePaqueteOriginDestination(*cabezaS, codeDestinationSucursal, codeOriginSucursal);
        while (valPaq == ERR_DESTINATION_INVALID) {
            printf("ERROR: La sucursal dada no existe en el sistema.\n\n");
            printf("Codigo sucursal destino: ");
            gets_truncate(codeOriginSucursal, 25);
            valPaq = validatePaqueteOriginDestination(*cabezaS, codeDestinationSucursal, codeOriginSucursal);
        }

        if (valPaq == ERR_DESTINATION_EQUALS_ORIGIN) {
            printf("ERROR: La sucursal de partida no puede ser la sucursal de destino.\n\n");
            continue;
        }

        break;
    }

    struct Date* dateDelivery, * dateReceived;
    ValidationError_Date valDat;
    while (true) {
        char buffer[5];

        short y1;
        unsigned short m1, d1;
        while (true) {
            printf("Fecha de envio: ");

            printf(" - Año: ");
            gets_truncate(buffer, 5);
            short year = (short) strtol(buffer, NULL, 10);

            printf(" - Mes: ");
            gets_truncate(buffer, 3);
            short month = (short) strtol(buffer, NULL, 10);
            valDat = validateDateMonth(month);
            while (valDat == ERR_MONTH_INVALID) {
                printf("   ERROR: El mes dado no es valido.\n");
                printf(" - Mes: ");
                gets_truncate(buffer, 3);
                valDat = validateDateMonth(month);
            }

            printf(" - Dia: ");
            gets_truncate(buffer, 3);
            short day = (short) strtol(buffer, NULL, 10);
            valDat = validateDate(day, month, year);
            while (valDat == ERR_DAY_INVALID) {
                printf("   ERROR: El dia dado no es valido.\n");
                printf(" - Dia: ");
                gets_truncate(buffer, 3);
                valDat = validateDate(day, month, year);
            }

            if (valDat == ERR_NOT_LEAP_YEAR) {
                printf("ERROR: Febrero 29 no existe en el año dado.\n\n");
                continue;
            }

            y1 = year;
            m1 = month;
            d1 = day;
            break;
        }

        short y2;
        unsigned short m2, d2;
        while (true) {
            printf("Fecha de recepcion: ");

            printf(" - Año: ");
            gets_truncate(buffer, 5);
            short year = (short) strtol(buffer, NULL, 10);

            printf(" - Mes: ");
            gets_truncate(buffer, 3);
            short month = (short) strtol(buffer, NULL, 10);
            valDat = validateDateMonth(month);
            while (valDat == ERR_MONTH_INVALID) {
                printf("   ERROR: El mes dado no es valido.\n");
                printf(" - Mes: ");
                gets_truncate(buffer, 3);
                valDat = validateDateMonth(month);
            }

            printf(" - Dia: ");
            gets_truncate(buffer, 3);
            short day = (short) strtol(buffer, NULL, 10);
            valDat = validateDate(day, month, year);
            while (valDat == ERR_DAY_INVALID) {
                printf("   ERROR: El dia dado no es valido.\n");
                printf(" - Dia: ");
                gets_truncate(buffer, 3);
                valDat = validateDate(day, month, year);
            }

            if (valDat == ERR_NOT_LEAP_YEAR) {
                printf("ERROR: Febrero 29 no existe en el año dado.\n\n");
                continue;
            }

            y2 = year;
            m2 = month;
            d2 = day;
            break;
        }

        dateDelivery = newDate(d1, m1, y1, &valDat);
        dateReceived = newDate(d2, m2, y2, &valDat);
        valPaq = validatePaqueteDates(dateDelivery, dateReceived);

        if (valPaq == ERR_DATE_MISMATCH) {
            printf("ERROR: La fecha de envio debe ser anterior a la fecha de entrega.\n\n");
            continue;
        }

        break;
    }

    bool insured;
    printf("Asegurado (Presione la tecla 's' para decir que si, cualquier otra tecla para decir que no) > ");
    int currchar = getcharnobuf();
    if (currchar == 's' || currchar == 'S') {
        printf("Si\n");
        insured = true;
    } else {
        printf("No\n");
        insured = false;
    }

    char description[50];
    printf("Descripcion (una sola linea): ");
    gets_truncate(description, 50);

    char lbuffer[10];
    printf("Peso (gramos): ");
    gets_truncate(lbuffer, 10);
    unsigned long long weightPackageGrams = (unsigned long long) strtoll_compat(lbuffer, NULL, 10);

    printf("Monto facturado: ");
    gets_truncate(lbuffer, 10);
    unsigned long long debitedCost = (unsigned long long) strtoll_compat(lbuffer, NULL, 10);

    char idSender[15];
    while (true) {
        printf("Cedula/Pasaporte emisor: ");
        gets_truncate(idSender, 15);

        valPaq = validatePaqueteSender(*cabezaP, idSender);
        if (valPaq == PAQUETE_OK) break;
        printf("ERROR: No existe persona registrada en el sistema con la identificacion dada.\n\n");
    }

    char idReceiver[15];
    printf("Cedula/Pasaporte receptor: ");
    gets_truncate(idReceiver, 15);

    printf("INFO: Procesando...");

    agregarPaquete(*cabezaS, *cabezaP, codeDestinationSucursal, codeOriginSucursal, dateDelivery, dateReceived, insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);

    printf("\n\nHa sido agregado exitosamente el paquete %s al sistema!\n\n", codeDelivery);
    printf("INFO: Operacion realizada exitosamente.\n\n");
    system("pause");
}

// v - Consultar envio
void menuOperaciones_op2(struct Sucursal** cabeza) {
    system("cls");
    printf("CONSULTAR ENVIO\n\n");

    char code[25];
    printf("Codigo del envio a consultar: ");
    gets_truncate(code, 25);

    struct EnvioPaquete* e = consultarEnvio(cabeza, code);
    if (!e) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printEnvio(e, consultarRecibo(cabeza, code));
        printf("----------------------------------------------------------\n");
    }
    system("pause");
}

// v - Actualizar envio
struct __private__DatoEnvio {
    struct EnvioPaquete* envio;
    struct ReciboPaquete* recibo;
};
void __restricted__MenuOperacionesModificarEnvioPrintf(void* envio) {
    printf("MODIFICAR ENVIO\n\n");
    struct __private__DatoEnvio** e2 = (struct __private__DatoEnvio**)envio;
    struct __private__DatoEnvio* e = *e2;
    printf("\n");
    printf("----------------------------------------------------------\n");
    printEnvio(e->envio, e->recibo);
    printf("[10] Guardar y regresar al menu anterior.");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("Introduzca en el teclado el numero correspondiente al dato que desea modificar y presione ENTER.\n");
    printf(" > ");
}
void menuOperaciones_op3(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    system("cls");
    printf("MODIFICAR ENVIO\n\n");

    char code[25];
    printf("Codigo del envio a modificar: ");
    gets_truncate(code, 25);

    struct __private__DatoEnvio* dato = (struct __private__DatoEnvio*) malloc(sizeof(struct __private__DatoEnvio));
    dato->envio = NULL;
    dato->recibo = NULL;
    consultarEnvioRecibo(cabezaS, code, &dato->envio, &dato->recibo);
    if (!dato->envio) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
        system("pause");
    } else {
        int opc = 99;
        while (opc != 10) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuOperacionesModificarEnvioPrintf, &dato);
            ValidationError_Date valDat;
            ValidationError_Paquete valPaq;
			int currchar;
			unsigned long long weightPackageGrams, debitedCost;
            switch (opc) {
                case 1:
                    char codeDestinationSucursal[25];

                    while (true) {
                        printf("Codigo sucursal destino: ");
                        gets_truncate(codeDestinationSucursal, 25);
                        valPaq = validatePaqueteOriginDestination(*cabezaS, codeDestinationSucursal, dato->recibo->codeOriginSucursal);
                        while (valPaq == ERR_DESTINATION_INVALID) {
                            printf("ERROR: La sucursal dada no existe en el sistema.\n\n");
                            printf("Codigo sucursal destino: ");
                            gets_truncate(codeDestinationSucursal, 25);
                            valPaq = validatePaqueteOriginDestination(*cabezaS, codeDestinationSucursal, dato->recibo->codeOriginSucursal);
                        }

                        if (valPaq == ERR_DESTINATION_EQUALS_ORIGIN) {
                            printf("ERROR: La sucursal de partida no puede ser la sucursal de destino.\n\n");
                            continue;
                        }

                        strcpy_s(dato->envio->codeDestinationSucursal, 25, codeDestinationSucursal);

                        break;
                    }
                    break;
                case 2:
                    struct Date* dateDelivery;
                    while (true) {
                        char buffer[5];

                        short y1;
                        unsigned short m1, d1;
                        while (true) {
                            printf("Fecha de envio: ");

                            printf(" - Año: ");
                            gets_truncate(buffer, 5);
                            short year = (short) strtol(buffer, NULL, 10);

                            printf(" - Mes: ");
                            gets_truncate(buffer, 3);
                            short month = (short) strtol(buffer, NULL, 10);
                            valDat = validateDateMonth(month);
                            while (valDat == ERR_MONTH_INVALID) {
                                printf("   ERROR: El mes dado no es valido.\n");
                                printf(" - Mes: ");
                                gets_truncate(buffer, 3);
                                valDat = validateDateMonth(month);
                            }

                            printf(" - Dia: ");
                            gets_truncate(buffer, 3);
                            short day = (short) strtol(buffer, NULL, 10);
                            valDat = validateDate(day, month, year);
                            while (valDat == ERR_DAY_INVALID) {
                                printf("   ERROR: El dia dado no es valido.\n");
                                printf(" - Dia: ");
                                gets_truncate(buffer, 3);
                                valDat = validateDate(day, month, year);
                            }

                            if (valDat == ERR_NOT_LEAP_YEAR) {
                                printf("ERROR: Febrero 29 no existe en el año dado.\n\n");
                                continue;
                            }

                            y1 = year;
                            m1 = month;
                            d1 = day;
                            break;
                        }

                        dateDelivery = newDate(d1, m1, y1, &valDat);
                        valPaq = validatePaqueteDates(dateDelivery, dato->envio->dateReceived);

                        if (valPaq == ERR_DATE_MISMATCH) {
                            printf("ERROR: La fecha de envio debe ser anterior a la fecha de entrega.\n\n");
                            continue;
                        }

                        dato->envio->dateDelivery = dateDelivery;

                        break;
                    }
                    break;
                case 3:
                    struct Date* dateReceived;
                    while (true) {
                        char buffer[5];

                        short y1;
                        unsigned short m1, d1;
                        while (true) {
                            printf("Fecha de recibo: ");

                            printf(" - Año: ");
                            gets_truncate(buffer, 5);
                            short year = (short) strtol(buffer, NULL, 10);

                            printf(" - Mes: ");
                            gets_truncate(buffer, 3);
                            short month = (short) strtol(buffer, NULL, 10);
                            valDat = validateDateMonth(month);
                            while (valDat == ERR_MONTH_INVALID) {
                                printf("   ERROR: El mes dado no es valido.\n");
                                printf(" - Mes: ");
                                gets_truncate(buffer, 3);
                                valDat = validateDateMonth(month);
                            }

                            printf(" - Dia: ");
                            gets_truncate(buffer, 3);
                            short day = (short) strtol(buffer, NULL, 10);
                            valDat = validateDate(day, month, year);
                            while (valDat == ERR_DAY_INVALID) {
                                printf("   ERROR: El dia dado no es valido.\n");
                                printf(" - Dia: ");
                                gets_truncate(buffer, 3);
                                valDat = validateDate(day, month, year);
                            }

                            if (valDat == ERR_NOT_LEAP_YEAR) {
                                printf("ERROR: Febrero 29 no existe en el año dado.\n\n");
                                continue;
                            }

                            y1 = year;
                            m1 = month;
                            d1 = day;
                            break;
                        }

                        dateReceived = newDate(d1, m1, y1, &valDat);
                        valPaq = validatePaqueteDates(dato->envio->dateDelivery, dateReceived);

                        if (valPaq == ERR_DATE_MISMATCH) {
                            printf("ERROR: La fecha de envio debe ser anterior a la fecha de entrega.\n\n");
                            continue;
                        }

                        dato->envio->dateReceived = dateReceived;

                        break;
                    }
                    break;
                case 4:
                    bool insured;
                    printf("Asegurado (Presione la tecla 's' para decir que si, cualquier otra tecla para decir que no) > ");
                    currchar = getcharnobuf();
                    if (currchar == 's' || currchar == 'S') {
                        printf("Si\n");
                        insured = true;
                    } else {
                        printf("No\n");
                        insured = false;
                    }
                    dato->envio->insured = insured;
                    break;
                case 5:
                    char description[50];
                    printf("Descripcion (una sola linea): ");
                    gets_truncate(description, 50);
                    strcpy_s(dato->envio->description, 50, description);
                    break;
                case 6:
                    char lbuffer[10];
                    printf("Peso (gramos): ");
                    gets_truncate(lbuffer, 10);
                    weightPackageGrams = (unsigned long long) strtoll_compat(lbuffer, NULL, 10);
                    dato->envio->weightPackageGrams = weightPackageGrams;
                    break;
                case 7:
                    printf("Monto facturado: ");
                    gets_truncate(lbuffer, 10);
                    debitedCost = (unsigned long long) strtoll_compat(lbuffer, NULL, 10);
                    dato->envio->debitedCost = debitedCost;
                    break;
                case 8:
                    char idSender[15];
                    while (true) {
                        printf("Cedula/Pasaporte emisor: ");
                        gets_truncate(idSender, 15);

                        valPaq = validatePaqueteSender(*cabezaP, idSender);
                        if (valPaq == PAQUETE_OK) break;
                        printf("ERROR: No existe persona registrada en el sistema con la identificacion dada.\n\n");
                    }
                    strcpy_s(dato->envio->idSender, 15, idSender);
                    break;
                case 9:
                    char idReceiver[15];
                    printf("Cedula/Pasaporte receptor: ");
                    gets_truncate(idReceiver, 15);
                    strcpy_s(dato->envio->idReceiver, 15, idReceiver);
                    break;
                case 10:break;
                default:
                    printf(" [Opcion invalida]\n");
                    system("pause");
                    break;
            }
        }
    }

    free(dato);
}

// v - Eliminar envio
void menuOperaciones_op4(struct Sucursal** cabeza) {
    system("cls");
    printf("ELIMINAR ENVIO\n\n");

    char code[25];
    printf("Codigo del envio a eliminar: ");
    gets_truncate(code, 25);

    struct EnvioPaquete* e = NULL;
    struct ReciboPaquete* r = NULL;
    consultarEnvioRecibo(cabeza, code, &e, &r);
    if (!e) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
    } else {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printEnvio(e, r);
        printf("----------------------------------------------------------\n");
        printf("Esta seguro de que desea eliminar el envio indicado?\n");
        printf("(Presione la tecla 's'para confirmar, cualquier otra tecla para cancelar) > ");
        int currchar = getcharnobuf();
        if (currchar == 's' || currchar == 'S') {
            printf("INFO: Procesando...\n");
            eliminarEnvio(cabeza, code);
            printf("INFO: Operacion realizada exitosamente.\n");
        } else {
            printf("INFO: Operacion cancelada por el usuario.\n");
        }
    }
    system("pause");
}


#endif //PROJECT1_MENU_2_OPERACIONES_H
