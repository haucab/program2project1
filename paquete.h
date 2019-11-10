#ifndef PROJECT1_PAQUETE_H
#define PROJECT1_PAQUETE_H

#include "common.h"
#include "paquete_validate.h"

struct EnvioPaquete {
	char codeDestinationSucursal[25];
	struct Date* dateDelivery, * dateReceived;
	bool insured;
	char description[50], codeDelivery[25];
	unsigned long long weightPackageGrams, debitedCost;
	char idSender[15], idReceiver[15]; // ID puede ser Cedula o Pasaporte
	struct EnvioPaquete* prev, * prox;
};

struct ReciboPaquete {
	char codeOriginSucursal[25];
    char codeDelivery[25];
	struct ReciboPaquete* prev, * prox;
};

/*private*/ struct EnvioPaquete* __private__newEnvioPaquete(
        char codeDestinationSucursal[25],
        struct Date* dateDelivery, struct Date* dateReceived,
        bool insured, char description[50], char codeDelivery[25],
        unsigned long long weightPackageGrams, unsigned long long debitedCost,
        char idSender[15], char idReceiver[15]) {
    struct EnvioPaquete* envio = (struct EnvioPaquete*) malloc(sizeof(struct EnvioPaquete));
    strcpy_s(envio->codeDestinationSucursal, 25, codeDestinationSucursal);
    envio->dateDelivery = dateDelivery;
    envio->dateReceived = dateReceived;
    envio->insured = insured;
    strcpy_s(envio->description, 50, description);
    strcpy_s(envio->codeDelivery, 25, codeDelivery);
    envio->weightPackageGrams = weightPackageGrams;
    envio->debitedCost = debitedCost;
    strcpy_s(envio->idSender, 25, idSender);
    strcpy_s(envio->idReceiver, 25, idReceiver);
    envio->prev = NULL;
    envio->prox = NULL;

    return envio;
}

/*private*/ struct ReciboPaquete* __private__newReciboPaquete(
        char codeOriginSucursal[25], char codeDelivery[25]) {
    struct ReciboPaquete* recibo = (struct ReciboPaquete*) malloc(sizeof(struct ReciboPaquete));
    strcpy_s(recibo->codeOriginSucursal, 25, codeOriginSucursal);
    strcpy_s(recibo->codeDelivery, 25, codeDelivery);
    recibo->prev = NULL;
    recibo->prox = NULL;

    return recibo;
}

ValidationError_Paquete validatePaqueteCodeDelivery(struct Sucursal* cabeza, char codeDelivery[25]) {
    struct Sucursal* s = cabeza;
    while (s) {
        struct EnvioPaquete* e = s->sentPackages;
        while (e) {
            if (stringIgualAString(e->codeDelivery, codeDelivery)) return ERR_DELIVERY_CODE_DUPLICATE;
            e = e->prox;
        }
        s = s->prox;
    }
    return PAQUETE_OK;
}

ValidationError_Paquete agregarPaquete(struct Sucursal* cabeza,
        char codeDestinationSucursal[25], char codeOriginSucursal[25],
        struct Date* dateDelivery, struct Date* dateReceived,
        bool insured, char description[50], char codeDelivery[25],
        unsigned long long weightPackageGrams, unsigned long long debitedCost,
        char idSender[15], char idReceiver[15]) {
	ValidationError_Paquete result = validatePaquete(cabeza, codeDestinationSucursal, codeOriginSucursal, dateDelivery, dateReceived, insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);
    if (result != PAQUETE_OK) return result;

	struct Sucursal* s = cabeza;
	bool hasEnvio = true, hasRecibo = true;
    while (s && (hasEnvio || hasRecibo)) {
        if (hasEnvio)
            if (stringIgualAString(s->code, codeOriginSucursal)) {
                struct EnvioPaquete *datoE = __private__newEnvioPaquete(codeDestinationSucursal, dateDelivery,
                                                                        dateReceived, insured, description,
                                                                        codeDelivery, weightPackageGrams, debitedCost,
                                                                        idSender, idReceiver);
                struct EnvioPaquete *e = s->sentPackages;
                if (!e) {
                    s->sentPackages = datoE;
                } else {
                    while (e->prox) e = e->prox;

                    e->prox = datoE;
                    datoE->prev = e;
                }
                hasEnvio = false;
            }
        if (hasRecibo)
            if (stringIgualAString(s->code, codeDestinationSucursal)) {
                struct ReciboPaquete *datoR = __private__newReciboPaquete(codeOriginSucursal, codeDelivery);
                struct ReciboPaquete *r = s->receivedPackages;
                if (!r) {
                    s->receivedPackages = datoR;
                } else {
                    while (r->prox) r = r->prox;

                    r->prox = datoR;
                    datoR->prev = r;
                }
                hasRecibo = false;
            }
        s = s->prox;
    }
	return PAQUETE_OK;
}

struct EnvioPaquete* consultarEnvio(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        while (s) {
            struct EnvioPaquete* e = s->sentPackages;
            while (e)  {
                if (stringIgualAString(e->codeDelivery, codeDelivery)) return e;
                e = e->prox;
            }
            s = s->prox;
        }
        return NULL;
    }
}

struct ReciboPaquete* consultarRecibo(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        while (s) {
            struct ReciboPaquete* r = s->receivedPackages;
            while (r)  {
                if (stringIgualAString(r->codeDelivery, codeDelivery)) return r;
                r = r->prox;
            }
            s = s->prox;
        }
        return NULL;
    }
}

void eliminarEnvio(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else while (s) {
        struct EnvioPaquete* e = s->sentPackages;
        while (e && e->prox)  {
            if (stringIgualAString(e->prox->codeDelivery, codeDelivery)) {
                struct EnvioPaquete* eaux = e->prox;
                e->prox = eaux->prox;
                if (eaux->prox) eaux->prox->prev = e;
                free(eaux);
            }
            e = e->prox;
        }
        e = s->sentPackages;
        if (e && stringIgualAString(e->codeDelivery, codeDelivery)) {
            s->sentPackages = e->prox;
            if (s->sentPackages) s->sentPackages->prev = NULL;
            free(e);
        }

        // ---------------------------------------------------------------

        struct ReciboPaquete* r = s->receivedPackages;
        while (r && r->prox)  {
            if (stringIgualAString(r->prox->codeDelivery, codeDelivery)) {
                struct ReciboPaquete* eaux = r->prox;
                r->prox = eaux->prox;
                if (eaux->prox) eaux->prox->prev = r;
                free(eaux);
            }
            r = r->prox;
        }
            r = s->receivedPackages;
        if (r && stringIgualAString(r->codeDelivery, codeDelivery)) {
            s->receivedPackages = r->prox;
            if (s->receivedPackages) s->receivedPackages->prev = NULL;
            free(r);
        }

        // ---------------------------------------------------------------

        s = s->prox;
    }
}

#endif //PROJECT1_PAQUETE_H
