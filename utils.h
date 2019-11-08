#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include "common.h"
#include "paquete.h"
#include "sucursal.h"

struct BusquedaEnvios {
    struct EnvioPaquete* valor;
    struct BusquedaEnvios* prev, * prox;
};

/*private*/ struct BusquedaEnvios* __private__newBusquedaEnvios(struct EnvioPaquete* valor) {
    struct BusquedaEnvios* result = (struct BusquedaEnvios*) malloc(sizeof(struct BusquedaEnvios));
    result->valor = valor;
    result->prev = NULL;
    result->prox = NULL;

    return result;
}

/*private*/ void __private__agregarEnvio(struct BusquedaEnvios** cabeza, struct EnvioPaquete* valor) {
    struct BusquedaEnvios* b = *cabeza;
    if (!b) {
        *cabeza = __private__newBusquedaEnvios(valor);
        return;
    }

    while (b->prox) b = b->prox;
    b->prox = __private__newBusquedaEnvios(valor);
    b->prox->prev = b;
}

struct BusquedaEnvios* buscarEnviosPorCedulaEmisor(struct Sucursal* lista, char id[15]) {
    struct Sucursal* s = lista;
    struct BusquedaEnvios* cabeza = NULL;
    while (s) {
        struct EnvioPaquete* p = s->sentPackages;
        while (p) {
            if (stringIgualAString(p->idSender, id)) {
                __private__agregarEnvio(&cabeza, p);
            }
            p = p->prox;
        }
        s = s->prox;
    }

    return cabeza;
}

struct EnvioPaquete* buscarEnviosPorCodigoDeTransaccion(struct Sucursal* lista, char id[15], char codeDelivery[25]) {
    struct BusquedaEnvios* b = buscarEnviosPorCedulaEmisor(lista, id);
    struct EnvioPaquete* e = NULL;
    while (b) {
        e = b->valor;
        if (stringIgualAString(e->codeDelivery, codeDelivery)) return e;
        b = b->prox;
    }

    return NULL;
}

#endif //PROJECT1_UTILS_H
