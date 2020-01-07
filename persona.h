#ifndef PROJECT1_PERSONA_H
#define PROJECT1_PERSONA_H

#include "common.h"
#include "persona_validate.h"

struct Persona {
	char id[15]; // ID puede ser Cedula o Pasaporte
	char fnames[50], lnames[50], streetaddress[150], email[50], city[30], state[30], country[30], phoneNumber[20];
	struct Persona* prev, * prox;
};

struct BusquedaPersonas {
    struct Persona* valor;
    struct BusquedaPersonas* prev, * prox;
};

/*private*/ struct Persona* __private__newPersona(
        char id[15], // ID puede ser Cedula o Pasaporte
        char fnames[50], char lnames[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    struct Persona* persona = (struct Persona*) malloc(sizeof(struct Persona));
    strcpy_s(persona->id, 15, id);
    strcpy_s(persona->fnames, 50, fnames);
    strcpy_s(persona->lnames, 50, lnames);
    strcpy_s(persona->streetaddress, 150, streetaddress);
    strcpy_s(persona->email, 50, email);
    strcpy_s(persona->city, 30, city);
    strcpy_s(persona->state, 30, state);
    strcpy_s(persona->country, 30, country);
    strcpy_s(persona->phoneNumber, 20, phoneNumber);

    persona->prev = NULL;
    persona->prox = NULL;

    return persona;
}

ValidationError_Persona validatePersonaId(struct Persona** cabeza,
                                          char id[15] /* ID puede ser Cedula o Pasaporte */) {
    struct Persona* p = *cabeza;
    while (p) {
        if (stringIgualAString(p->id, id)) return ERR_DUPLICATE_PERSON_ID;
        p = p->prox;
    }
    return PERSONA_OK;
}

ValidationError_Persona agregarPersona(
        struct Persona** cabezaPtr,
        char id[15], // ID puede ser Cedula o Pasaporte
        char fnames[50], char lnames[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    ValidationError_Persona result = validatePersona(cabezaPtr, id, email);
    if (result != PERSONA_OK) return result;

    struct Persona* dato = __private__newPersona(id, fnames, lnames, streetaddress, email, city, state, country, phoneNumber);

    struct Persona* cabeza = *cabezaPtr, * p = cabeza;
    if (!cabeza) {
        *cabezaPtr = dato;
        dato->prev = dato;
        dato->prox = dato;
    } else {
        while (p->prox != cabeza) {
            if (strcmp(p->id, id) > 0) break;
            p = p->prox;
        }

        struct Persona* aux = p->prev;
        p->prev = dato;
        dato->prev = aux;
        dato->prox = p;
        aux->prox = dato;
    }
    return PERSONA_OK;
}

bool __private__person_exists(struct Persona* cabeza, char *idSender) {
    if (!cabeza) return false;
    if (stringIgualAString(cabeza->id, idSender)) return true;

    struct Persona* p = cabeza->prox;
    while (p != cabeza) {
        if (stringIgualAString(p->id, idSender))
            return true;
        p = p->prox;
    }

    return false;
}
struct Persona* consultarPersonaID(struct Persona** cabezaPtr, char id[15]) {
    struct Persona* cabeza  = *cabezaPtr;
    if (!cabeza) return NULL;
    if (stringIgualAString(cabeza->id, id)) return cabeza;

    struct Persona* p = cabeza->prox;
    while (p != cabeza) {
        if (stringIgualAString(p->id, id)) return p;
        p = p->prox;
    }
    return NULL;
}

void printPersona(struct Persona* p) {
    printf("    Cedula/Pasaporte: %s\n", p->id);
    printf("[1] Nombre: %s\n", p->fnames);
    printf("[2] Apellido: %s\n", p->lnames);
    printf("[3] Direccion: %s\n", p->streetaddress);
    printf("[4] Correo electronico: %s\n", p->email);
    printf("[5] Ciudad: %s\n", p->city);
    printf("[6] Estado: %s\n", p->state);
    printf("[7] Pais: %s\n", p->country);
    printf("[8] Telefono: %s\n", p->phoneNumber);
}

/*private*/ bool __private__nameMatch(struct Persona* s, char fnames[50], char lnames[50]) {
    if (!stringIsEmptyOrNull_s(fnames, 50)) {
        if (stringContieneAString(s->lnames, fnames)) {
            if (stringIsEmptyOrNull_s(lnames, 50) || stringContieneAString(s->lnames, lnames)) return true;
        }
    } else {
        if (!stringIsEmptyOrNull_s(lnames, 50) && stringContieneAString(s->lnames, lnames)) return true;
    }
    return false;
}

struct BusquedaPersonas* consultarPersonaNombre(struct Persona** cabezaPtr, char fnames[50], char lnames[50]) {
    if (!fnames && !lnames) return NULL;

    struct Persona* cabeza  = *cabezaPtr;
    if (!cabeza) return NULL;

    struct BusquedaPersonas* busqueda = NULL;
    if (__private__nameMatch(cabeza, fnames, lnames)) {
        struct BusquedaPersonas* aux = busqueda;
        busqueda = (struct BusquedaPersonas*) malloc(sizeof(struct BusquedaPersonas));
        busqueda->valor = cabeza;
        busqueda->prox = aux;
        busqueda->prev = NULL;
        busqueda->prox->prev = busqueda;
    }

    struct Persona* p = cabeza->prox;
    while (p != cabeza) {
        if (__private__nameMatch(p, fnames, lnames)) {
            struct BusquedaPersonas* aux = busqueda;
            busqueda = (struct BusquedaPersonas*) malloc(sizeof(struct BusquedaPersonas));
            busqueda->valor = p;
            busqueda->prox = aux;
            busqueda->prev = NULL;
            busqueda->prox->prev = busqueda;
        }
        p = p->prox;
    }
    return busqueda;
}

void eliminarPersona(struct Persona** cabezaPtr, char id[15]) {
    struct Persona* cabeza = *cabezaPtr, * p = cabeza;
    int i = 0;
    if (!p) return;
    else while (p != cabeza || i == 0) {
        i++;
        if (stringIgualAString(p->id, id)) {
            p->prev->prox = p->prox;
            p->prox->prev = p->prev;
            if (p == p->prox) {
                *cabezaPtr = NULL;
            }
            free(p);
            return;
        }
        p = p->prox;
    }
}

#endif //PROJECT1_PERSONA_H