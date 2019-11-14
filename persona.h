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
        struct Persona** cabeza,
        char id[15], // ID puede ser Cedula o Pasaporte
        char fnames[50], char lnames[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    ValidationError_Persona result = validatePersona(cabeza, id, email);
    if (result != PERSONA_OK) return result;

    struct Persona* dato = __private__newPersona(id, fnames, lnames, streetaddress, email, city, state, country, phoneNumber);

    struct Persona* p = *cabeza;
    if (!p) {
        *cabeza = dato;
    } else {
        while (p->prox) p = p->prox;

        p->prox = dato;
        dato->prev = p;
    }
    return PERSONA_OK;
}

bool __private__person_exists(struct Persona* cabeza, char *idSender) {
    struct Persona* p = cabeza;

    while (p) {
        if (stringIgualAString(p->id, idSender))
            return true;
        p = p->prox;
    }

    return false;
}
struct Persona* consultarPersonaID(struct Persona** cabeza, char id[15]) {
    struct Persona* p = *cabeza;
    if (!p) return NULL;
    else {
        while (p) {
            if (stringIgualAString(p->id, id)) return p;
            p = p->prox;
        }
        return NULL;
    }
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

struct BusquedaPersonas* consultarPersonaNombre(struct Persona** cabeza, char fnames[50], char lnames[50]) {
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

void eliminarPersona(struct Persona** cabeza, char id[15]) {
    struct Persona* p = *cabeza;
    if (!p) return;
    else while (p) {
        if (stringIgualAString(p->id, id)) {
            if (p->prev) p->prev->prox = p->prox;
            if (p->prox) p->prox->prev = p->prev;
            free(p);
            return;
        }
        p = p->prox;
    }
}

#endif //PROJECT1_PERSONA_H