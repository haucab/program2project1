#ifndef PROJECT1_PERSONA_H
#define PROJECT1_PERSONA_H

#include "common.h"

//TODO REFORMAR

struct Persona {
	long long id; // ID puede ser Cedula o Pasaporte
	char* fnames, * lnames, * streetaddress, * email, * city, * state, * country;
	long long phoneNumber;
	struct Persona* prev, * prox;
};

struct BusquedaPersonas {
    struct Persona* valor;
    struct BusquedaPersonas* prev, * prox;
};

/*private*/ struct Persona* __private__newPersona(
        long long id, // ID puede ser Cedula o Pasaporte
        char* fnames,
        char* lnames,
        char* streetaddress,
        char* email,
        char* city,
        char* state,
        char* country,
        long long phoneNumber) {
    struct Persona* persona = (struct Persona*) malloc(sizeof(struct Persona));
    persona->id = id;
    persona->fnames = fnames;
    persona->lnames = lnames;
    persona->streetaddress = streetaddress;
    persona->email = email;
    persona->city = city;
    persona->state = state;
    persona->country = country;
    persona->phoneNumber = phoneNumber;

    persona->prev = NULL;
    persona->prox = NULL;

    return persona;
}

void agregarPersona(
        struct Persona** cabeza,
        long long id, // ID puede ser Cedula o Pasaporte
        char* fnames,
        char* lnames,
        char* streetaddress,
        char* email,
        char* city,
        char* state,
        char* country,
        long long phoneNumber) {
    struct Persona* dato = __private__newPersona(id, fnames, lnames, streetaddress, email, city, state, country, phoneNumber);

    struct Persona* p = *cabeza;
    if (!p) {
        *cabeza = dato;
    } else {
        while (p->prox) p = p->prox;

        p->prox = dato;
        dato->prev = p;
    }
}
// seal __private__newPersona from outside calling
#define __private__newPersona cant_call_private_function

struct Persona* consultarPersonaID(struct Persona** cabeza, long long id) {
    struct Persona* p = *cabeza;
    if (!p) return NULL;
    else {
        while (p) {
            if (p->id == id) return p;
            p = p->prox;
        }
        return NULL;
    }
}

/*private*/ bool __private__nameMatch(struct Persona* s, char* fnames, char* lnames) {
    if (fnames) {
        if (stringContieneAString(s->lnames, fnames)) {
            if (!lnames || stringContieneAString(s->lnames, lnames)) return true;
        }
    } else {
        if (lnames && stringContieneAString(s->lnames, lnames)) return true;
    }
    return false;
}

struct BusquedaPersonas* consultarPersonaNombre(struct Persona** cabeza, char* fnames, char* lnames) {
    if (!fnames && !lnames) return NULL;

    struct Persona* p = *cabeza;
    if (!p) return NULL;
    else {
        struct BusquedaPersonas* busqueda = NULL;
        while (p) {
            if (__private__nameMatch(p, fnames, lnames)) {
                struct BusquedaPersonas* aux = busqueda;
                busqueda = (struct BusquedaPersonas*) malloc(sizeof(struct BusquedaPersonas));
                busqueda->valor = p;
                busqueda->prox = aux;
                busqueda->prox->prev = busqueda;
            }
            p = p->prox;
        }
        return NULL;
    }
}
// seal __private__nameMatch from outside calling
#define __private__nameMatch cant_call_private_function

void eliminarPersona(struct Persona** cabeza, long long id) {
    struct Persona* p = *cabeza;
    if (!p) return;
    else while (p) {
        if (p->id == id) {
            p->prev->prox = p->prox;
            p->prox->prev = p->prev;
            free(p);
            return;
        }
        p = p->prox;
    }
}

#endif //PROJECT1_PERSONA_H