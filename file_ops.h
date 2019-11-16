#ifndef PROJECT1_FILE_OPS_H
#define PROJECT1_FILE_OPS_H

#include  <io.h>
#include "common.h"
#include "persona.h"
#include "paquete.h"
#include "sucursal.h"
#include "paquete.h"

struct EnvioPaquete* fget_envios_legacy(const char* c1) {
    if ((_access(c1, 0)) != -1) {
        FILE *f1;
        fopen_s(&f1, c1, "r");

        if (!f1 || ferror(f1) != 0) {
            return NULL;
        }

        char buffer[10];
        fgets_truncate(buffer, 10, f1);
        long max = strtol(buffer, NULL, 10);
        struct EnvioPaquete* cab = NULL;
        for (int i = 0; i < max; i++) {
            char codeDestinationSucursal[25];
            fgets_truncate(codeDestinationSucursal, 25, f1);
            struct Date* dateDelivery, struct Date* dateReceived,
            bool insured, char description[50], char codeDelivery[25],
            unsigned long long weightPackageGrams, unsigned long long debitedCost,
            char idSender[15], char idReceiver[15]
        }

        fclose(f1);
        return cab;
    }
    return NULL;
}

void fputs_envios_legacy(struct EnvioPaquete* cabeza, const char* c1) {
//    FILE* f1;
//    fopen_s(&f1, c1, "w");
//    // Do something here
//    fclose(f1);
}

#endif //PROJECT1_FILE_OPS_H
