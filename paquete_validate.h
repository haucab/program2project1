#ifndef PROJECT1_PAQUETE_VALIDATE_H
#define PROJECT1_PAQUETE_VALIDATE_H

#include "common.h"
#include "sucursal.h"
#include "date.h"

typedef enum {
    PAQUETE_OK, ERR_DESTINATION_INVALID, ERR_ORIGIN_INVALID, ERR_DESTINATION_EQUALS_ORIGIN, ERR_DATE_MISMATCH, ERR_DELIVERY_CODE_DUPLICATE, ERR_SENDER_INVALID
} ValidationError_Paquete;

struct Persona; // Implemented in persona.h

ValidationError_Paquete validatePaqueteOrigin(struct Sucursal* cabeza, char codeOriginSucursal[25]) {
    struct Sucursal* s = cabeza;
    bool hasEnvio = false;

    while (s && (!hasEnvio)) {
        if (stringIgualAString(s->code, codeOriginSucursal)) hasEnvio = true;
        s = s->prox;
    }

    if (!hasEnvio) return ERR_ORIGIN_INVALID;
    else return PAQUETE_OK;
}

ValidationError_Paquete validatePaqueteOriginDestination(struct Sucursal* cabeza, char codeDestinationSucursal[25], char codeOriginSucursal[25]) {
    ValidationError_Paquete validationOrigin = validatePaqueteOrigin(cabeza, codeOriginSucursal);
    if (validationOrigin != PAQUETE_OK) return validationOrigin;

    if (stringIgualAString(codeDestinationSucursal, codeOriginSucursal)) return ERR_DESTINATION_EQUALS_ORIGIN;

    struct Sucursal* s = cabeza;
    bool hasRecibo = false;

    while (s && (!hasRecibo)) {
        if (stringIgualAString(s->code, codeDestinationSucursal)) hasRecibo = true;
        s = s->prox;
    }

    if (!hasRecibo) return ERR_DESTINATION_INVALID;
    else return PAQUETE_OK;
}

ValidationError_Paquete validatePaqueteDates(struct Date* dateDelivery, struct Date* dateReceived) {
    if (dateDelivery->year > dateReceived->year) return ERR_DATE_MISMATCH;
    else if (dateDelivery->year == dateReceived->year) {
        if (dateDelivery->month > dateReceived->month) return ERR_DATE_MISMATCH;
        else if (dateDelivery->month == dateReceived->month) {
            if (dateDelivery->day > dateReceived->day) return ERR_DATE_MISMATCH;
        }
    }

    return PAQUETE_OK;
}

ValidationError_Paquete validatePaqueteCodeDelivery(struct Sucursal* cabeza, char codeDelivery[25]); // Implemented in paquete.h

bool __private__person_exists(struct Persona* cabeza, char *idSender);
ValidationError_Paquete validatePaqueteSender(struct Persona* cabeza, char idSender[15]) {
    if (__private__person_exists(cabeza, idSender)) return PAQUETE_OK;
    else return ERR_SENDER_INVALID;
}

ValidationError_Paquete validatePaquete(struct Sucursal* cabezaS, struct Persona* cabezaP,
                                        char codeDestinationSucursal[25], char codeOriginSucursal[25],
                                        struct Date* dateDelivery, struct Date* dateReceived,
                                        bool insured, char description[50], char codeDelivery[25],
                                        unsigned long long weightPackageGrams, unsigned long long debitedCost,
                                        char idSender[15], char idReceiver[15]) {
    ValidationError_Paquete validationTotal = validatePaqueteOriginDestination(cabezaS, codeDestinationSucursal, codeOriginSucursal);
    if (validationTotal != PAQUETE_OK) return validationTotal;

    validationTotal = validatePaqueteDates(dateDelivery, dateReceived);
    if (validationTotal != PAQUETE_OK) return validationTotal;

    validationTotal = validatePaqueteCodeDelivery(cabezaS, codeDelivery);
    if (validationTotal != PAQUETE_OK) return validationTotal;

    return validatePaqueteSender(cabezaP, idSender);
}

#endif //PROJECT1_PAQUETE_VALIDATE_H
