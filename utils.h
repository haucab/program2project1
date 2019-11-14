#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include <time.h>
#include "common.h"
#include "paquete.h"
#include "sucursal.h"
#include "persona.h"

struct BusquedaEnvios {
    struct EnvioPaquete* valorE;
    struct ReciboPaquete* valorR;
    struct BusquedaEnvios* prev, * prox;
};

typedef int (*SortEnviosCallback)(struct EnvioPaquete*, struct EnvioPaquete*, struct ReciboPaquete*, struct ReciboPaquete*);

/*private*/ struct BusquedaEnvios* __private__newBusquedaEnvios(struct EnvioPaquete* valorE, struct ReciboPaquete* valorR) {
    struct BusquedaEnvios* result = (struct BusquedaEnvios*) malloc(sizeof(struct BusquedaEnvios));
    result->valorE = valorE;
    result->valorR = valorR;
    result->prev = NULL;
    result->prox = NULL;

    return result;
}

/*private*/ int __private__compareDates(struct Date* d1, struct Date* d2) {
    if (d1->year > d2->year) return 1;
    else if (d1->year == d2->year) {
        if (d1->month > d2->month) return 1;
        else if (d1->month == d2->month) {
            return d1->day > d2->day ? 1 : (d1->day == d2->day ? 0 : -1);
        } else return -1;
    } else return -1;
}

/*private*/ void __private__agregarEnvio(struct BusquedaEnvios** cabeza, struct EnvioPaquete* valorE, struct ReciboPaquete* valorR, SortEnviosCallback callback) {
    struct BusquedaEnvios* b = *cabeza;
    if (!b) {
        *cabeza = __private__newBusquedaEnvios(valorE, valorR);
        return;
    }

    struct BusquedaEnvios* aux = __private__newBusquedaEnvios(valorE, valorR);
    if (callback(valorE, b->valorE, valorR, b->valorR) < 0) {
        aux->prox = b;
        b->prev = aux;
        *cabeza = aux;
    } else {
        while (b) {
            if (callback(valorE, b->valorE, valorR, b->valorR) < 0) {
                aux->prox = b;
                aux->prev = b->prev;
                b->prev->prox = aux;
                b->prev = aux;
                return;
            }

            b = b->prox;
        }
    }
}

int __private__sortSentDate(struct EnvioPaquete* e1, struct EnvioPaquete* e2, struct ReciboPaquete* ignored1, struct ReciboPaquete* ignored2) {
    return __private__compareDates(e1->dateDelivery, e2->dateDelivery);
}
struct BusquedaEnvios* buscarEnviosPorCedulaEmisorOrdenadosPorFecha(struct Sucursal* lista, char id[15]) {
    struct Sucursal* s = lista;
    struct BusquedaEnvios* cabeza = NULL;
    while (s) {
        struct EnvioPaquete* p = s->sentPackages;
        while (p) {
            if (stringIgualAString(p->idSender, id)) {
                __private__agregarEnvio(&cabeza, p, consultarRecibo(&lista, p->codeDelivery), &__private__sortSentDate);
            }
            p = p->prox;
        }
        s = s->prox;
    }

    return cabeza;
}

struct EnvioPaquete* buscarEnviosPorCedulaEmisorCodigoDeTransaccion(struct Sucursal* lista, char id[15], char codeDelivery[25]) {
    struct BusquedaEnvios* b = buscarEnviosPorCedulaEmisorOrdenadosPorFecha(lista, id);
    struct EnvioPaquete* e = NULL;
    while (b) {
        e = b->valorE;
        if (stringIgualAString(e->codeDelivery, codeDelivery)) return e;
        b = b->prox;
    }

    return NULL;
}

int __private__sortCodigoEnvio(struct EnvioPaquete* e1, struct EnvioPaquete* e2, struct ReciboPaquete* ignored1, struct ReciboPaquete* ignored2) {
    char* c1 = &e1->codeDelivery[0];
    char* c2 = &e2->codeDelivery[0];

    unsigned int i, j;
    for (i = 0; *c1 == '0' && i < 25; i++, c1++) {}
    for (j = 0; *c2 == '0' && j < 25; j++, c2++) {}
    unsigned int len1 = strlen(e1->codeDelivery) - i;
    unsigned int len2 = strlen(e2->codeDelivery) - j;

    if (len1 > len2) return 1;
    else if (len1 < len2) return -1;
    else {
        for (; i < strlen(e1->codeDelivery) && j < strlen(e2->codeDelivery); i++, j++, c1++, c2++) {
            unsigned int digit1 = *c1 - '0';
            unsigned int digit2 = *c2 - '0';
            if (digit1 > digit2) return 1;
            else if (digit1 < digit2) return -1;
        }
        if (strlen(e1->codeDelivery) > strlen(e2->codeDelivery)) return 1;
        else if (strlen(e1->codeDelivery) < strlen(e2->codeDelivery)) return -1;
        else return 0;
    }
}
struct BusquedaEnvios* buscarEnviosPorSucursalEntreDosFechasOrdenadoPorCodigoDeEnvio(struct Sucursal* sucursal, struct Date* start, struct Date* end) {
    struct Sucursal* s = sucursal;
    struct BusquedaEnvios* cabeza = NULL;
    struct EnvioPaquete* p = s->sentPackages;
    while (p) {
        if ((__private__compareDates(p->dateDelivery, start) >= 0) && (__private__compareDates(p->dateDelivery, end) <= 0)) {
            __private__agregarEnvio(&cabeza, p, consultarRecibo(&s, p->codeDelivery), &__private__sortCodigoEnvio);
        }
        p = p->prox;
    }

    return cabeza;
}

struct BusquedaEnvios* buscarEnviosPorSucursalNoCerrados(struct Sucursal* sucursal) {
    time_t rawtime;
    time(&rawtime);
    struct tm timeinfo;
    localtime_s(&timeinfo, &rawtime);
    ValidationError_Date ignored;
    struct Date *start = newDate(
            (unsigned short) timeinfo.tm_mday,
            (unsigned short) timeinfo.tm_mon + 1,
            (short) timeinfo.tm_year + 1900, &ignored); // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    struct Date *end = (struct Date *) malloc(sizeof(struct Date));
    end->day = 32;
    end->month = 13;
    end->year = (short) timeinfo.tm_year + 1901; // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    return buscarEnviosPorSucursalEntreDosFechasOrdenadoPorCodigoDeEnvio(sucursal, start, end);
}
//
//struct BusquedaPersonas* buscarPersonasPorSucursalConMayorCantidadEnvios(struct Sucursal* sucursal, struct Persona** cabezaP) {
//    struct Sucursal* s = sucursal;
//    struct BusquedaPersonas* cabezaB = NULL;
//    struct EnvioPaquete* p = s->sentPackages;
//    while (p) {
//        if ((__private__compareDates(p->dateDelivery, start) >= 0) && (__private__compareDates(p->dateDelivery, end) <= 0)) {
//            __private__agregarEnvio(&cabezaB, p, consultarRecibo(&s, p->codeDelivery), &__private__sortCodigoEnvio);
//        }
//        p = p->prox;
//    }
//
//    return cabezaB;
//}

#endif //PROJECT1_UTILS_H
