#ifndef PROJECT1_PAQUETE_H
#define PROJECT1_PAQUETE_H

#include "common.h"
#include "date.h"
#include "sucursal.h"

struct EnvioPaquete {
	char codeDestinationSucursal[25];
	struct Date* dateDelivery, * dateReceived;
	bool insured;
	char description[50], codeDelivery[25];
	long long weightPackageGrams, debitedCost;
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
        struct Date* dateDelivery,
        struct Date* dateReceived,
        bool insured,
        char description[50],
        char codeDelivery[25],
        long long weightPackageGrams,
        long long debitedCost,
        char idSender[15],
        char idReceiver[15]) {
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
        char codeOriginSucursal[25],
        char codeDelivery[25]) {
    struct ReciboPaquete* recibo = (struct ReciboPaquete*) malloc(sizeof(struct ReciboPaquete));
    strcpy_s(recibo->codeOriginSucursal, 25, codeOriginSucursal);
    strcpy_s(recibo->codeDelivery, 25, codeDelivery);
    recibo->prev = NULL;
    recibo->prox = NULL;

    return recibo;
}

bool agregarEnvio(
        struct Sucursal* cabeza,
        char codeDestinationSucursal[25],
        char codeOriginSucursal[25],
        struct Date* dateDelivery,
        struct Date* dateReceived,
        bool insured,
        char description[50],
        char codeDelivery[25],
        long long weightPackageGrams,
        long long debitedCost,
        char idSender[15],
		char idReceiver[15]) {
	if (stringIgualAString(codeDestinationSucursal, codeOriginSucursal)) return false;

	struct Sucursal* s = cabeza;
	bool hasEnvio = false, hasRecibo = false;
    while (s && !hasEnvio && !hasRecibo) {
		if (!hasEnvio) 
			if (stringIgualAString(s->code, codeOriginSucursal)) hasEnvio = true;

		if (!hasRecibo)
			if (stringIgualAString(s->code, codeDestinationSucursal)) hasRecibo = true;

		s = s->prox;
	}
	
	s = cabeza;
	if (hasEnvio && hasRecibo) while (s && (hasEnvio || hasRecibo)) {
		if (hasEnvio) if (stringIgualAString(s->code, codeOriginSucursal)) {
			struct EnvioPaquete* datoE = __private__newEnvioPaquete(codeDestinationSucursal, dateDelivery, dateReceived, insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);
			struct EnvioPaquete* cabezaE = s->sentPackages;
			//TODO FINISH
		}
		if (hasRecibo) if (stringIgualAString(s->code, codeDestinationSucursal)){
			//TODO FINISH
		} 
	} else return false;

    
    struct ReciboPaquete* datoR = __private__newReciboPaquete(codeOriginSucursal, codeDelivery);
}
// seal __private__new{Envio,Recibo}Paquete from outside calling
#define __private__newEnvioPaquete cant_call_private_function
#define __private__newReciboPaquete cant_call_private_function

struct Sucursal* consultarEnvio(struct Sucursal** cabeza, int code) {
    //TODO REFORMAR
    struct Sucursal* s = *cabeza;
    if (!s) return NULL;
    else {
        while (s) {
            if (s->code == code) return s;
            s = s->prox;
        }
        return NULL;
    }
}

void eliminarEnvio(struct Sucursal** cabeza, int code) {
    //TODO REFORMAR
    struct Sucursal* s = *cabeza;
    if (!s) return;
    else while (s) {
            if (s->code == code) {
                s->prev->prox = s->prox;
                s->prox->prev = s->prev;
                free(s);
                return;
            }
            s = s->prox;
        }
}

#endif //PROJECT1_PAQUETE_H
