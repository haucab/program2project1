#ifndef PROJECT1_MENU_3_CONSULTAS_H
#define PROJECT1_MENU_3_CONSULTAS_H

#include "common.h"
#include "common_cli_windows.h"
#include "sucursal.h"
#include "paquete.h"
#include "persona.h"
#include "utils.h"

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

void menuConsultas_op1(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas_op2(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas_op3(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas_op4(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas_op5(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas_op6(struct Sucursal** cabezaS, struct Persona** cabezaP);
void menuConsultas(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    int opc = 99;
    while (opc != 7) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuConsultasPrintf, NULL);
        switch (opc) {
            case 1:
                menuConsultas_op1(cabezaS, cabezaP);
                break;
            case 2:
                menuConsultas_op2(cabezaS, cabezaP);
                break;
            case 3:
                menuConsultas_op3(cabezaS, cabezaP);
                break;
            case 4:
                menuConsultas_op4(cabezaS, cabezaP);
                break;
            case 5:
                menuConsultas_op5(cabezaS, cabezaP);
                break;
            case 6:
                menuConsultas_op6(cabezaS, cabezaP);
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
void menuConsultas_op1(struct Sucursal** cabezaS, struct Persona** cabezaP) {
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
        while (opc != 3) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuConsultas_3_1_Printf, NULL);
            switch (opc) {
                case 1:
                    printf("Formato: CODIGO-SUCURSAL, CODIGO-ENVIO, FECHA-ENVIO, FECHA-RECIBO, DESCRIPCION\n");
                    printf("----------------------------------------------------------\n");
                    struct BusquedaEnvios* result1 = buscarEnviosPorCedulaEmisorOrdenadosPorFecha(*cabezaS, id);
                    while (result1) {
                        char dat1[15];
                        dateToString(result1->valorE->dateDelivery, dat1);
                        char dat2[15];
                        dateToString(result1->valorE->dateReceived, dat2);
                        printf("%s, %s, %s, %s, %s\n", result1->valorR->codeOriginSucursal, result1->valorE->codeDelivery, dat1, dat2, result1->valorE->description);

                        struct BusquedaEnvios* resultgarbage = result1;
                        result1 = result1->prox;
                        result1->prev = NULL;
                        free(resultgarbage);
                    }
                    printf("----------------------------------------------------------\n");
                    system("pause");
                    break;
                case 2:
                    char code[25];
                    printf("Codigo de envio: ");
                    gets_truncate(code, 25);

                    struct EnvioPaquete* temp1;
                    struct ReciboPaquete* temp2;
                    consultarEnvioRecibo(cabezaS, code, &temp1, &temp2);
                    printf("----------------------------------------------------------\n");
                    printEnvio(temp1, temp2);
                    printf("----------------------------------------------------------\n");
                    system("pause");
                    break;
                case 3: break;
                default:
                    printf(" [Opcion invalida]\n");
                    system("pause");
                    break;
            }
        }
    }
}

void __restricted__MenuConsultas_3_2_Printf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+------------ Dada el codigo de una sucursal ------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|  1.  Mostrar envios y recepciones entre dos fechas...  |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|            2. Mostrar envios no cerrados...            |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|       3.  Mostrar los clientes de la sucursal...       |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|              4. Regresar al menu anterior              |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}
void menuConsultas_op2(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    system("cls");
    printf("CONSULTA 3.2\n\n");

    char code[25];
    printf("Codigo de Sucursal: ");
    gets_truncate(code, 25);

    struct Sucursal* s = consultarSucursal(cabezaS, code);
    if (!s) {
        printf("ERROR: La identificacion dada no existe en el sistema.\n\n");
        system("pause");
    } else {
        int opc = 99;
        while (opc != 4) {
            system("cls");
            scanf_integer(&opc, &__restricted__MenuConsultas_3_2_Printf, NULL);
            switch (opc) {
                case 1:
                    struct Date* dateStart, * dateEnd;
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

                        dateStart = newDate(d1, m1, y1, &valDat);
                        dateEnd = newDate(d2, m2, y2, &valDat);

                        if (validatePaqueteDates(dateStart, dateEnd) == ERR_DATE_MISMATCH) {
                            printf("ERROR: La fecha de inicial debe ser anterior a la fecha final.\n\n");
                            continue;
                        }

                        break;
                    }

                    struct BusquedaEnvios* result1 = buscarEnviosPorSucursalEntreDosFechasOrdenadoPorCodigoDeEnvio(s, dateStart, dateEnd);
                    while (result1) {
                        printf("----------------------------------------------------------\n");
                        printEnvio(result1->valorE, result1->valorR);

                        struct BusquedaEnvios* resultgarbage = result1;
                        result1 = result1->prox;
                        result1->prev = NULL;
                        free(resultgarbage);
                        printf("----------------------------------------------------------\n\n");
                    }
                    struct BusquedaEnvios* result2 = buscarRecibosPorSucursalEntreDosFechasOrdenadoPorCodigoDeEnvio(cabezaS, s, dateStart, dateEnd);
                    while (result2) {
                        printf("----------------------------------------------------------\n");
                        printEnvio(result2->valorE, result2->valorR);

                        struct BusquedaEnvios* resultgarbage = result2;
                        result2 = result2->prox;
                        result2->prev = NULL;
                        free(resultgarbage);
                        printf("----------------------------------------------------------\n\n");
                    }
                    system("pause");
                    break;
                case 2:
                    struct BusquedaEnvios* result3 = buscarEnviosPorSucursalNoCerrados(s);
                    while (result3) {
                        printf("----------------------------------------------------------\n");
                        printEnvio(result3->valorE, result3->valorR);

                        struct BusquedaEnvios* resultgarbage = result3;
                        result3 = result3->prox;
                        result3->prev = NULL;
                        free(resultgarbage);
                        printf("----------------------------------------------------------\n\n");
                    }
                    system("pause");
                    break;
                case 3:
                    printf("Por mayor cantidad de envios o de recepciones (E/r) > ");
                    int currchar = getcharnobuf();
                    if (currchar == 'r' || currchar == 'R') {
                        struct BusquedaPersonasExtra* busc = buscarPersonasPorSucursalConMayorCantidadRecepciones(s, cabezaP);
                        printf("----------------------------------------------------------\n");
                        while (busc) {
                            if (busc->ptr) printf("%s %s, %s, %s", busc->ptr->fnames, busc->ptr->lnames, busc->ptr->id, busc->ptr->streetaddress);
                            else printf("[Persona no registrada] %s", busc->id);

                            struct BusquedaPersonasExtra* resultgarbage = busc;
                            busc = busc->prox;
                            busc->prev = NULL;
                            free(resultgarbage);
                        }
                        printf("----------------------------------------------------------\n\n");
                    } else {
                        struct BusquedaPersonasExtra* busc = buscarPersonasPorSucursalConMayorCantidadEnvios(s, cabezaP);
                        printf("----------------------------------------------------------\n");
                        while (busc) {
                            printf("%s %s, %s, %s", busc->ptr->fnames, busc->ptr->lnames, busc->ptr->id, busc->ptr->streetaddress);

                            struct BusquedaPersonasExtra* resultgarbage = busc;
                            busc = busc->prox;
                            busc->prev = NULL;
                            free(resultgarbage);
                        }
                        printf("----------------------------------------------------------\n\n");
                    }
                    system("pause");
                    break;
                case 4: break;
                default:
                    printf(" [Opcion invalida]\n");
                    system("pause");
                    break;
            }
        }
    }
}

void menuConsultas_op3(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    struct BusquedaPersonasExtra* busc = buscarPersonasConMayorCantidadEnvios(cabezaS, cabezaP);
    while (busc) {
        printf("----------------------------------------------------------\n");
        printPersona(busc->ptr);

        struct BusquedaPersonasExtra* resultgarbage = busc;
        busc = busc->prox;
        busc->prev = NULL;
        free(resultgarbage);
        printf("----------------------------------------------------------\n\n");
    }
    system("pause");
}

void menuConsultas_op4(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    struct Date* dateStart, * dateEnd;
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

        dateStart = newDate(d1, m1, y1, &valDat);
        dateEnd = newDate(d2, m2, y2, &valDat);

        if (validatePaqueteDates(dateStart, dateEnd) == ERR_DATE_MISMATCH) {
            printf("ERROR: La fecha de inicial debe ser anterior a la fecha final.\n\n");
            continue;
        }

        break;
    }

    struct BusquedaSucursales* busc = buscarSucursalConMayorCantidadEnviosEntreFechas(cabezaS, dateStart, dateEnd);
    while (busc) {
        printf("----------------------------------------------------------\n");
        printSucursal(busc->ptr);
        printf("Envios: %ld", busc->enviosRecibos);

        struct BusquedaSucursales* resultgarbage = busc;
        busc = busc->prox;
        busc->prev = NULL;
        free(resultgarbage);
        printf("----------------------------------------------------------\n\n");
    }
    system("pause");
}

void menuConsultas_op5(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    struct Date* dateStart, * dateEnd;
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

        dateStart = newDate(d1, m1, y1, &valDat);
        dateEnd = newDate(d2, m2, y2, &valDat);

        if (validatePaqueteDates(dateStart, dateEnd) == ERR_DATE_MISMATCH) {
            printf("ERROR: La fecha de inicial debe ser anterior a la fecha final.\n\n");
            continue;
        }

        break;
    }

    struct BusquedaSucursales* busc = buscarSucursalConMayorCantidadRecibosEntreFechas(cabezaS, dateStart, dateEnd);
    while (busc) {
        printf("----------------------------------------------------------\n");
        printSucursal(busc->ptr);
        printf("Recibos: %ld", busc->enviosRecibos);

        struct BusquedaSucursales* resultgarbage = busc;
        busc = busc->prox;
        busc->prev = NULL;
        free(resultgarbage);
        printf("----------------------------------------------------------\n\n");
    }
    system("pause");
}

void menuConsultas_op6(struct Sucursal** cabezaS, struct Persona** cabezaP) {
    struct BusquedaPersonasExtra* busc = buscarPersonasNoRegistradas(cabezaS, cabezaP);
    while (busc) {
        printf("----------------------------------------------------------\n");
        printf("ID: %s", busc->id);
        printf("Recibos: %ld", busc->enviosRecibos);

        struct BusquedaPersonasExtra* resultgarbage = busc;
        busc = busc->prox;
        busc->prev = NULL;
        free(resultgarbage);
        printf("----------------------------------------------------------\n\n");
    }
}

#endif //PROJECT1_MENU_3_CONSULTAS_H
