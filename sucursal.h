#ifndef PROJECT1_SUCURSAL_H
#define PROJECT1_SUCURSAL_H

struct Sucursal {
	char code[25]; // Codigo especial de sucursal
	char name[50], streetaddress[150], email[50], city[30], state[30], country[30], phoneNumber[20];
	struct Sucursal* prev, * prox;

	struct ReciboPaquete* receivedPackages;
	struct EnvioPaquete*  sentPackages;
};

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

    sucursal->prev = NULL;
    sucursal->prox = NULL;
    sucursal->receivedPackages = NULL;
    sucursal->sentPackages = NULL;

    return sucursal;
}

void agregarSucursal(
        struct Sucursal** cabeza,
        char code[25], // Codigo especial de sucursal
        char name[50], char streetaddress[150], char email[50],
        char city[30], char state[30], char country[30], char phoneNumber[20]) {
    struct Sucursal* dato = __private__newSucursal(code, name, streetaddress, email, city, state, country, phoneNumber);

    struct Sucursal* s = *cabeza;
    if (!s) {
        *cabeza = dato;
    } else {
        while (s->prox) s = s->prox;

        s->prox = dato;
        dato->prev = s;
    }
}

struct Sucursal* consultarSucursal(struct Sucursal** cabeza, char code[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        while (s) {
            if (stringIgualAString(s->code, code)) return s;
            s = s->prox;
        }
        return NULL;
    }
}

void eliminarSucursal(struct Sucursal** cabeza,  char code[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else while (s) {
        if (stringIgualAString(s->code, code)) {
            if (s->prev) s->prev->prox = s->prox;
            if (s->prox) s->prox->prev = s->prev;
            free(s);
            return;
        }
        s = s->prox;
    }
}

#endif // PROJECT1_SUCURSAL_H