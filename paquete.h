#ifndef PROJECT1_PAQUETE_H
#define PROJECT1_PAQUETE_H

#include "common.h"
#include "paquete_validate.h"

struct EnvioPaquete {
	char codeDestinationSucursal[25];
	struct Date* dateDelivery, * dateReceived;
	bool insured;
	char description[50], codeDelivery[25];
	unsigned long long weightPackageGrams;
    char debitedCost[20];
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
        unsigned long long weightPackageGrams, char debitedCost[20],
        char idSender[15], char idReceiver[15]) {
    struct EnvioPaquete* envio = (struct EnvioPaquete*) malloc(sizeof(struct EnvioPaquete));
    strcpy_s(envio->codeDestinationSucursal, 25, codeDestinationSucursal);
    envio->dateDelivery = dateDelivery;
    envio->dateReceived = dateReceived;
    envio->insured = insured;
    strcpy_s(envio->description, 50, description);
    strcpy_s(envio->codeDelivery, 25, codeDelivery);
    envio->weightPackageGrams = weightPackageGrams;
    strcpy_s(envio->debitedCost, 20, debitedCost);
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

struct __validatePaqueteCodeDelivery1Struct {
    char codeDelivery[25];
    ValidationError_Paquete* response;
};
void __private__validatePaqueteCodeDelivery1(struct Sucursal* s, bool* breakFlag, void* data) {
    struct __validatePaqueteCodeDelivery1Struct* parcel = (struct __validatePaqueteCodeDelivery1Struct*) data;
    struct EnvioPaquete* e = s->sentPackages;
    while (e) {
        if (stringIgualAString(e->codeDelivery, parcel->codeDelivery)) {
            *(parcel->response) = ERR_DELIVERY_CODE_DUPLICATE;
            *breakFlag = true;
            return;
        }
        e = e->prox;
    }
}
ValidationError_Paquete validatePaqueteCodeDelivery(struct Sucursal* cabeza, char codeDelivery[25]) {
    struct Sucursal* s = cabeza;
    ValidationError_Paquete response = PAQUETE_OK;
    struct __validatePaqueteCodeDelivery1Struct* parcel =
            (struct __validatePaqueteCodeDelivery1Struct*) malloc(sizeof(struct __validatePaqueteCodeDelivery1Struct));
    strcpy_s(parcel->codeDelivery, 25, codeDelivery);
    parcel->response = &response;
    forEachSucursal(cabeza, &__private__validatePaqueteCodeDelivery1, parcel);
    free(parcel);
    return response;
}


struct __agregarPaqueteStruct1 {
    bool* hasEnvio, * hasRecibo;
    struct EnvioPaquete *datoE;
    struct ReciboPaquete *datoR;
};
void __private__agregarPaquete1(struct Sucursal* s, bool* breakFlag, void* data) {
    struct __agregarPaqueteStruct1* parcel = (struct __agregarPaqueteStruct1*) data;
    bool* hasEnvio = parcel->hasEnvio, * hasRecibo = parcel->hasRecibo;
    if (!(*hasEnvio || *hasRecibo)) {
        *breakFlag = true;
        return;
    }
    if (*hasEnvio)
        if (stringIgualAString(s->code, parcel->datoR->codeOriginSucursal)) {
            struct EnvioPaquete *e = s->sentPackages;
            if (!e) {
                s->sentPackages = parcel->datoE;
            } else {
                while (e->prox) e = e->prox;

                e->prox = parcel->datoE;
                parcel->datoE->prev = e;
            }
            *hasEnvio = false;
        }
    if (*hasRecibo)
        if (stringIgualAString(s->code, parcel->datoE->codeDestinationSucursal)) {
            struct ReciboPaquete *r = s->receivedPackages;
            if (!r) {
                s->receivedPackages = parcel->datoR;
            } else {
                while (r->prox) r = r->prox;

                r->prox = parcel->datoR;
                parcel->datoR->prev = r;
            }
            *hasRecibo = false;
        }
}
ValidationError_Paquete agregarPaquete(struct Sucursal* cabezaS, struct Persona* cabezaP,
                                       char codeDestinationSucursal[25], char codeOriginSucursal[25],
                                       struct Date* dateDelivery, struct Date* dateReceived,
                                       bool insured, char description[50], char codeDelivery[25],
                                       unsigned long long weightPackageGrams, char debitedCost[20],
                                       char idSender[15], char idReceiver[15]) {
	ValidationError_Paquete result = validatePaquete(cabezaS, cabezaP, codeDestinationSucursal, codeOriginSucursal, dateDelivery, dateReceived, insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);
    if (result != PAQUETE_OK) return result;

	struct Sucursal* s = cabezaS;
	bool hasEnvio = true, hasRecibo = true;
    struct EnvioPaquete *datoE = __private__newEnvioPaquete(codeDestinationSucursal, dateDelivery,
                                                            dateReceived, insured, description,
                                                            codeDelivery, weightPackageGrams, debitedCost,
                                                            idSender, idReceiver);
    struct ReciboPaquete *datoR = __private__newReciboPaquete(codeOriginSucursal, codeDelivery);

    struct __agregarPaqueteStruct1* parcel =
            (struct __agregarPaqueteStruct1*) malloc(sizeof(struct __agregarPaqueteStruct1));
    parcel->hasEnvio = &hasEnvio;
    parcel->hasRecibo = &hasRecibo;
    parcel->datoE = datoE;
    parcel->datoR = datoR;

    forEachSucursal(cabezaS, &__private__agregarPaquete1, parcel);

    parcel->hasRecibo = NULL;
    parcel->hasEnvio  = NULL;
    parcel->datoE = NULL;
    parcel->datoR = NULL;
    free(parcel);

	return PAQUETE_OK;
}

void printEnvio(struct EnvioPaquete* envio, struct ReciboPaquete* recibo) {
    printf("    Codigo envio: %s\n", envio->codeDelivery);
    printf("    Sucursal origen: %s\n", recibo->codeOriginSucursal);
    printf("[1] Sucursal destino: %s\n", envio->codeDestinationSucursal);
    char buf[15];
    dateToString(envio->dateDelivery, buf);
    printf("[2] Fecha Envio: %s\n", buf);
    dateToString(envio->dateReceived, buf);
    printf("[3] Fecha Recibo: %s\n", buf);
    if (envio->insured) {
        printf("[4] Asegurado: Si\n");
    } else {
        printf("[4] Asegurado: No\n");
    }
    printf("[5] Descripcion: %s\n", envio->description);

    char buf2[10];
    sprintf_s(buf2, 10, "%lld", envio->weightPackageGrams);
    printf("[6] Peso (g): %s\n", buf2);
    printf("[7] Monto facturado: %s\n", envio->debitedCost);
    printf("[8] Cedula/Pasaporte emisor: %s\n", envio->idSender);
    printf("[9] Cedula/Pasaporte receptor: %s\n", envio->idReceiver);
}


struct __consultarEnvioStruct1 {
    char** codeDelivery;
    struct EnvioPaquete* response;
};
void __private__consultarEnvio1(struct Sucursal* s, bool* breakFlag, void* data) {
    struct __consultarEnvioStruct1* parcel = (struct __consultarEnvioStruct1*) data;

    struct EnvioPaquete* e = s->sentPackages;
    while (e)  {
        if (stringIgualAString(e->codeDelivery, *(parcel->codeDelivery))) {
            parcel->response = e;
            *breakFlag = true;
            return;
        }
        e = e->prox;
    }
}
struct EnvioPaquete* consultarEnvio(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        struct __consultarEnvioStruct1* parcel =
                (struct __consultarEnvioStruct1*) malloc(sizeof(struct __consultarEnvioStruct1));
        parcel->codeDelivery = &codeDelivery;
        parcel->response = NULL;
        forEachSucursal(s, &__private__consultarEnvio1, parcel);
        struct EnvioPaquete* response = parcel->response;
        parcel->response = NULL;
        parcel->codeDelivery = NULL;
        free(parcel);
        return response;
    }
}

struct __consultarReciboStruct1 {
    char** codeDelivery;
    struct ReciboPaquete* response;
};
void __private__consultarRecibo1(struct Sucursal* s, bool* breakFlag, void* data) {
    struct __consultarReciboStruct1* parcel = (struct __consultarReciboStruct1*) data;

    struct ReciboPaquete* r = s->receivedPackages;
    while (r)  {
        if (stringIgualAString(r->codeDelivery, *(parcel->codeDelivery))) {
            parcel->response = r;
            *breakFlag = true;
            return;
        }
        r = r->prox;
    }
}
struct ReciboPaquete* consultarRecibo(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        struct __consultarReciboStruct1* parcel =
                (struct __consultarReciboStruct1*) malloc(sizeof(struct __consultarReciboStruct1));
        parcel->codeDelivery = &codeDelivery;
        parcel->response = NULL;
        forEachSucursal(s, &__private__consultarRecibo1, parcel);
        struct ReciboPaquete* response = parcel->response;
        parcel->response = NULL;
        parcel->codeDelivery = NULL;
        free(parcel);
        return response;
    }
}

struct __consultarEnvioReciboStruct1 {
    bool* hasEnvio, * hasRecibo;
    char** codeDelivery;
    struct EnvioPaquete** envio;
    struct ReciboPaquete** recibo;
};
void __private__consultarEnvioRecibo1(struct Sucursal* s, bool* breakFlag, void* data) {
    struct __consultarEnvioReciboStruct1* parcel = (struct __consultarEnvioReciboStruct1*) data;

    bool* hasEnvio = parcel->hasEnvio, * hasRecibo = parcel->hasRecibo;
    struct EnvioPaquete** envio = parcel->envio;
    struct ReciboPaquete** recibo = parcel->recibo;
    if (*hasEnvio && *hasRecibo) {
        *breakFlag = true;
        return;
    }

    if (!*hasEnvio) {
        struct EnvioPaquete *e = s->sentPackages;
        while (e && !*hasEnvio) {
            if (stringIgualAString(e->codeDelivery, *(parcel->codeDelivery))) {
                    *envio = e;
                *hasEnvio = true;
            }
            e = e->prox;
        }
    }
    if (!*hasRecibo) {
        struct ReciboPaquete *r = s->receivedPackages;
        while (r && !*hasRecibo) {
            if (stringIgualAString(r->codeDelivery, *(parcel->codeDelivery))) {
                *recibo = r;
                *hasRecibo = true;
            }
            r = r->prox;
        }
    }
}
void consultarEnvioRecibo(struct Sucursal** cabeza, char codeDelivery[25], struct EnvioPaquete** envio, struct ReciboPaquete** recibo) {
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else {
        bool hasEnvio = false, hasRecibo = false;

        struct __consultarEnvioReciboStruct1* parcel =
                (struct __consultarEnvioReciboStruct1*) malloc(sizeof(struct __consultarEnvioReciboStruct1));
        parcel->hasEnvio = &hasEnvio;
        parcel->hasRecibo = &hasRecibo;
        parcel->codeDelivery = &codeDelivery;
        parcel->envio = envio;
        parcel->recibo = recibo;

        forEachSucursal(s, &__private__consultarEnvioRecibo1, parcel);

        parcel->hasRecibo = NULL;
        parcel->hasEnvio  = NULL;
        parcel->envio = NULL;
        parcel->recibo = NULL;

        free(parcel);
    }
}

void eliminarEnvio(struct Sucursal** cabeza, char codeDelivery[25]) {
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else while (s) {
        struct EnvioPaquete* e = s->sentPackages;
        while (e && e->prox)  {
            if (stringIgualAString(e->prox->codeDelivery, codeDelivery)) {
                struct Date* d = e->dateDelivery;
                e->dateDelivery = NULL;
                free(d);

                d = e->dateReceived;
                e->dateReceived = NULL;
                free(d);

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
