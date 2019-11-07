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
// seal __private__newBusquedaEnvios from outside calling
#define __private__newBusquedaEnvios cant_call_private_function

struct BusquedaEnvios* buscarEnviosPorCedulaEmisor(struct Sucursal* lista, long long id) {
    struct Sucursal* s = lista;
    struct BusquedaEnvios* cabeza = NULL;
    while (s) {
        struct EnvioPaquete* p = s->sentPackages;
        while (p) {
            if (p->idSender == id) {
                __private__agregarEnvio(&cabeza, p);
            }
            p = p->prox;
        }
        s = s->prox;
    }

    return cabeza;
}
// seal __private__agregarEnvio from outside calling
#define __private__agregarEnvio cant_call_private_function

struct EnvioPaquete* buscarEnviosPorCodigoDeTransaccion(struct Sucursal* lista, long long id, long long codeDelivery) {
    struct BusquedaEnvios* b = buscarEnviosPorCedulaEmisor(lista, id);
    struct EnvioPaquete* e = NULL;
    while (b) {
        e = b->valor;
        if (e->codeDelivery == codeDelivery) return e;
        b = b->prox;
    }

    return NULL;
}

#endif //PROJECT1_UTILS_H
