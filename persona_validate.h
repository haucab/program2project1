#ifndef PROJECT1_PERSONA_VALIDATE_H
#define PROJECT1_PERSONA_VALIDATE_H

#include "common.h"

typedef enum {
    PERSONA_OK, ERR_DUPLICATE_PERSON_ID, ERR_INVALID_PERSON_EMAIL
} ValidationError_Persona;

struct Persona;

ValidationError_Persona validatePersonaId(struct Persona** cabeza,
                                          char id[15] /* ID puede ser Cedula o Pasaporte */); // Implemented in persona.h

ValidationError_Persona validatePersonaEmail(char email[50]) {
    if (!stringContieneAString(email, "@")) return ERR_INVALID_PERSON_EMAIL;
    else return PERSONA_OK;
}

ValidationError_Persona validatePersona(struct Persona** cabeza,
                                        char id[15], // ID puede ser Cedula o Pasaporte
                                        char email[50]) {
    ValidationError_Persona validationTotal = validatePersonaId(cabeza, id);
    if (validationTotal != PERSONA_OK) return validationTotal;

    return validatePersonaEmail(email);
}

#endif //PROJECT1_PERSONA_VALIDATE_H
