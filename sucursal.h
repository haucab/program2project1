#ifndef PROJECT1_SUCURSAL_H
#define PROJECT1_SUCURSAL_H

#include "common.h"
#include "sucursal_validate.h"

struct Sucursal {
	char code[25]; // Codigo especial de sucursal
	char name[50], streetaddress[150], email[50], city[30], state[30], country[30], phoneNumber[20];
	struct Sucursal* izq, * der;

	struct ReciboPaquete* receivedPackages;
	struct EnvioPaquete*  sentPackages;
};
typedef void (*SucursalDeleteCallback)(struct Sucursal*, char[25]);
typedef void (*SucursalLoopCallback)(struct Sucursal*, bool*, void*);

/*private*/ struct Sucursal* __private__newSucursal(
        char code[25], // Codigo especial de sucursal
        char name[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    struct Sucursal* sucursal = (struct Sucursal*) malloc(sizeof(struct Sucursal));
    strcpy_s(sucursal->code, 25, code);
    strcpy_s(sucursal->name, 50, name);
    strcpy_s(sucursal->streetaddress, 150, streetaddress);
    strcpy_s(sucursal->email, 50, email);
    strcpy_s(sucursal->city, 30, city);
    strcpy_s(sucursal->state, 30, state);
    strcpy_s(sucursal->country, 30, country);
    strcpy_s(sucursal->phoneNumber, 20, phoneNumber);

    sucursal->izq = NULL;
    sucursal->der = NULL;
    sucursal->receivedPackages = NULL;
    sucursal->sentPackages = NULL;

    return sucursal;
}

ValidationError_Sucursal validateSucursalId(struct Sucursal** cabeza,
                                            char code[15] /* ID puede ser Cedula o Pasaporte */) {
    struct Sucursal* p = *cabeza;
    if (!p) return SUCURSAL_OK;
    else if (stringIgualAString(p->code, code)) return ERR_DUPLICATE_SUCURSAL_ID;
    else {
        ValidationError_Sucursal s = validateSucursalId(&p->izq, code);
        return s != SUCURSAL_OK ? s : validateSucursalId(&p->der, code);
    }
}

ValidationError_Sucursal validateSucursalName(struct Sucursal** cabeza,
                                              char name[50] /* ID puede ser Cedula o Pasaporte */) {
    struct Sucursal* p = *cabeza;
    if (!p) return SUCURSAL_OK;
    else if (stringIgualAString(p->name, name)) return ERR_DUPLICATE_SUCURSAL_NAME;
    else if ((strcmp(p->name, name) > 0)) return validateSucursalName(&p->izq, name);
    else return validateSucursalName(&p->der, name);
}

bool insertarSucursalEnSucursal(struct Sucursal** p, struct Sucursal* sucursal) {
    struct Sucursal* parent = *p;
    if (!parent) {
        // Become the parent as darth vader becomes your father
        parent = sucursal;
        *p = parent;
        return true;
    } else if (stringIgualAString(parent->code, sucursal->code) || stringIgualAString(parent->name, sucursal->name)) return false;
    else if (strcmp(parent->name, sucursal->name) > 0) return insertarSucursalEnSucursal(&parent->izq, sucursal);
    else return insertarSucursalEnSucursal(&parent->der, sucursal);
}

ValidationError_Sucursal agregarSucursal(
        struct Sucursal** cabeza,
        char code[25], // Codigo especial de sucursal
        char name[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    ValidationError_Sucursal result = validateSucursal(cabeza, code, name, email);
    if (result != SUCURSAL_OK) return result;

    struct Sucursal* dato = __private__newSucursal(code, name, streetaddress, email, city, state, country, phoneNumber);
    insertarSucursalEnSucursal(cabeza, dato);
    return SUCURSAL_OK;
}

void printSucursal(struct Sucursal* s) {
    printf("    Codigo sucursal: %s\n", s->code);
    printf("[1] Nombre: %s\n", s->name);
    printf("[2] Direccion: %s\n", s->streetaddress);
    printf("[3] Correo electronico: %s\n", s->email);
    printf("[4] Ciudad: %s\n", s->city);
    printf("[5] Estado: %s\n", s->state);
    printf("[6] Pais: %s\n", s->country);
    printf("[7] Telefono: %s\n", s->phoneNumber);
}

struct Sucursal* consultarSucursal(struct Sucursal** cabeza, char code[25]) {
    struct Sucursal* p = *cabeza;
    if (!p) return NULL;
    else if (stringIgualAString(p->code, code)) return p;
    else {
        struct Sucursal* s = consultarSucursal(&p->izq, code);
        return s != NULL ? s : consultarSucursal(&p->der, code);
    }
}

struct Sucursal* consultarSucursalNombre(struct Sucursal** cabeza, char name[50]) {
    struct Sucursal* p = *cabeza;
    if (!p) return NULL;
    else if (stringIgualAString(p->name, name)) return p;
    else if ((strcmp(p->name, name) > 0)) return consultarSucursalNombre(&p->izq, name);
    else return consultarSucursalNombre(&p->der, name);
}

void forEachSucursal(struct Sucursal* p, SucursalLoopCallback callback, void* data) {
    if (!p) return;

    bool breakFlag = false;
    callback(p, &breakFlag, data);
    if (breakFlag) return;
    forEachSucursal(p->izq, callback, data);
    forEachSucursal(p->der, callback, data);
}

void __private__mayorDeMenores(struct Sucursal** cabeza, struct Sucursal** curr) {
    struct Sucursal* s = *curr;
    if (s->der) __private__mayorDeMenores(cabeza, &s->der);
    else {
        struct Sucursal* aux = s->izq;
        s->der = (*cabeza)->der;
        s->izq = (*cabeza)->izq;
        *curr = aux;

        aux = *cabeza;
        *cabeza = s;
        free(aux);
    }
}

void __private__menorDeMayores(struct Sucursal** cabeza, struct Sucursal** curr) {
    struct Sucursal* s = *curr;
    if (s->izq) __private__menorDeMayores(cabeza, &s->izq);
    else {
        struct Sucursal* aux = s->der;
        s->der = (*cabeza)->der;
        s->izq = (*cabeza)->izq;
        *curr = aux;
        aux = *cabeza;
        *cabeza = s;
        free(aux);
    }
}

struct Sucursal** __private__consultarSucursalCodigo(struct Sucursal** cabeza, char code[25]) {
    struct Sucursal* p = *cabeza;
    if (!p) return NULL;
    else if (stringIgualAString(p->code, code)) return cabeza;
    else {
        struct Sucursal** s = __private__consultarSucursalCodigo(&p->izq, code);
        return s != NULL ? s : __private__consultarSucursalCodigo(&p->der, code);
    }
}

void eliminarSucursal(struct Sucursal** cabeza,  char code[25], SucursalDeleteCallback callback, char possiblecode[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else {
        struct Sucursal** toDelete = __private__consultarSucursalCodigo(cabeza, code);
        if (toDelete == NULL) return;

        struct Sucursal* td = *toDelete;
        callback(td, possiblecode);

        if (td->izq) __private__mayorDeMenores(cabeza, toDelete);
        else if (td->der) __private__menorDeMayores(cabeza, toDelete);
        else {
            *toDelete = NULL;
            free(td);
        }
    }
}

#endif // PROJECT1_SUCURSAL_H
