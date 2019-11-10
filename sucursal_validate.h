#ifndef PROJECT1_SUCURSAL_VALIDATE_H
#define PROJECT1_SUCURSAL_VALIDATE_H

#include "common.h"

typedef enum {
    SUCURSAL_OK, ERR_DUPLICATE_SUCURSAL_ID, ERR_INVALID_SUCURSAL_EMAIL
} ValidationError_Sucursal;

struct Sucursal;

ValidationError_Sucursal validateSucursalId(struct Sucursal** cabeza,
                                            char code[15] /* ID puede ser Cedula o Pasaporte */); // Implemented in persona.h

ValidationError_Sucursal validateSucursalEmail(char email[50]) {
    if (!stringContieneAString(email, "@")) return ERR_INVALID_SUCURSAL_EMAIL;
    else return SUCURSAL_OK;
}

ValidationError_Sucursal validateSucursal(struct Sucursal** cabeza,
                                          char code[15], // ID puede ser Cedula o Pasaporte
                                          char email[50]) {
    ValidationError_Sucursal validationTotal = validateSucursalId(cabeza, code);
    if (validationTotal != SUCURSAL_OK) return validationTotal;

    return validateSucursalEmail(email);
    //
}

#endif //PROJECT1_SUCURSAL_VALIDATE_H
