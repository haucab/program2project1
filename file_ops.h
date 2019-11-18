#ifndef PROJECT1_FILE_OPS_H
#define PROJECT1_FILE_OPS_H

#include  <io.h>
#include "common.h"
#include "persona.h"
#include "paquete.h"
#include "sucursal.h"
#include "paquete.h"

void fget_envios(const char* c1, struct Sucursal* cabezaS, struct Persona* cabezaP) {
    if (true) {
        FILE *f1;
        fopen_s(&f1, c1, "r");

        if (!f1 || ferror(f1) != 0) {
            return;
        }

        char buffer[10];
        fgets_truncate(buffer, 10, f1);
        long max = strtol(buffer, NULL, 10);
        for (long i = 0; i < max; i++) {
            char codeDestinationSucursal[25];
            fgets_truncate(codeDestinationSucursal, 25, f1);
            char codeOriginSucursal[25];
            fgets_truncate(codeOriginSucursal, 25, f1);

            // ---
            fgets_truncate(buffer, 5, f1);
            short year = (short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            unsigned short month = (unsigned short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            unsigned short day = (unsigned short) strtol(buffer, NULL, 10);
            struct Date* dateDelivery = (struct Date*) malloc(sizeof(struct Date));
            dateDelivery->day = day;
            dateDelivery->month = month;
            dateDelivery->year = year;

            fgets_truncate(buffer, 5, f1);
            year = (short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            month = (unsigned short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            day = (unsigned short) strtol(buffer, NULL, 10);
            struct Date* dateReceived = (struct Date*) malloc(sizeof(struct Date));
            dateDelivery->day = day;
            dateDelivery->month = month;
            dateDelivery->year = year;

            // ---
            fgets_truncate(buffer, 5, f1);
            int readInsured = (int) strtol(buffer, NULL, 10);
            bool insured;
            if (readInsured) insured = true;
            else insured = false;

            char description[50];
            fgets_truncate(description, 50, f1);

            char codeDelivery[25];
            fgets_truncate(codeDelivery, 25, f1);

            fgets_truncate(buffer, 10, f1);
            unsigned long long weightPackageGrams = (unsigned long long) strtoll_compat(buffer, NULL, 10);

            char debitedCost[20];
            fgets_truncate(debitedCost, 20, f1);

            char idSender[15];
            fgets_truncate(idSender, 15, f1);

            char idReceiver[15];
            fgets_truncate(idReceiver, 15, f1);

			agregarPaquete(cabezaS, cabezaP, codeDestinationSucursal, codeOriginSucursal, dateDelivery, dateReceived,
                    insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);
        }

        fclose(f1);
    }
}

void fputs_envios(struct Sucursal* cabeza, const char* c1) {
    FILE* f1;
    fopen_s(&f1, c1, "w");
    if (f1 && (ferror(f1) == 0)) {
		struct Sucursal* s = cabeza;
		struct EnvioPaquete* e;
		long cont = 0;
		while (s) {
			e = s->sentPackages;
			for (; e; cont++) e = e->prox;
			s = s->prox;
		}

		char buffer[10];
		itoa(cont, buffer, 10);
		fputs_newline(buffer, f1);

		s = cabeza;
		while (s) {
            e = s->sentPackages;
			while (e) {
				fputs_newline(e->codeDestinationSucursal, f1);
				fputs_newline(s->code, f1);

		        // ---
				itoa(e->dateDelivery->year, buffer, 10);
				fputs_newline(buffer, f1);
				itoa(e->dateDelivery->month, buffer, 10);
		        fputs_newline(buffer, f1);
				itoa(e->dateDelivery->day, buffer, 10);
				fputs_newline(buffer, f1);

				itoa(e->dateReceived->year, buffer, 10);
		        fputs_newline(buffer, f1);
				itoa(e->dateReceived->month, buffer, 10);
				fputs_newline(buffer, f1);
				itoa(e->dateReceived->day, buffer, 10);
		        fputs_newline(buffer, f1);
				
				// ---
				if (e->insured) fputs_newline("1", f1);
				else fputs_newline("0", f1);

				fputs_newline(e->description, f1);
				fputs_newline(e->codeDelivery, f1);

				sprintf_s(buffer, 10, "%llu", e->weightPackageGrams);
	            fputs_newline(buffer, f1);

	            fputs_newline(e->debitedCost, f1);

				fputs_newline(e->idSender, f1);

				fputs_newline(e->idReceiver, f1);

	            e = e->prox;
			}
			s = s->prox;
		}

        fclose(f1);
    }
}

struct Persona* fgets_personas(const char* c1) {
    if (true) {
        FILE *f1;
        fopen_s(&f1, c1, "r");

        if (!f1 || ferror(f1) != 0) {
            return NULL;
        }

        char buffer[10];
        fgets_truncate(buffer, 10, f1);
        long max = strtol(buffer, NULL, 10);
        struct Persona* cab = NULL;
        for (long i = 0; i < max; i++) {
			char id[15];
            fgets_truncate(id, 15, f1);

			char fnames[50];
			fgets_truncate(fnames, 50, f1);

			char lnames[50];
			fgets_truncate(lnames, 50, f1);

			char streetaddress[150];
			fgets_truncate(streetaddress, 150, f1);

			char email[50];
			fgets_truncate(email, 50, f1);

			char city[30];
			fgets_truncate(city, 30, f1);

			char state[30];
			fgets_truncate(state, 30, f1);

			char country[30];
			fgets_truncate(country, 30, f1);

			char phoneNumber[20];
			fgets_truncate(phoneNumber, 20, f1);

			agregarPersona(&cab, id, fnames, lnames, streetaddress, email, city, state, country, phoneNumber);
        }

        fclose(f1);
        return cab;
    }
    return NULL;
}

void fputs_personas(struct Persona* cabeza, const char* c1) {
    FILE* f1;
    fopen_s(&f1, c1, "w");
    if (f1 && (ferror(f1) == 0)) {
		struct Persona* e = cabeza;
		long cont;
		for (cont = 0; e; cont++) e = e->prox;

		char buffer[10];
		itoa(cont, buffer, 10);
		fputs_newline(buffer, f1);

		e = cabeza;
		while (e) {
			fputs_newline(e->id, f1);
			fputs_newline(e->fnames, f1);
			fputs_newline(e->lnames, f1);
			fputs_newline(e->streetaddress, f1);
			fputs_newline(e->email, f1);
			fputs_newline(e->city, f1);
			fputs_newline(e->state, f1);
			fputs_newline(e->country, f1);
			fputs_newline(e->phoneNumber, f1);

            e = e->prox;
		}

        fclose(f1);
    }
}

struct Sucursal* fgets_sucursales(const char* c1) {
    if (true) {
        FILE *f1;
        fopen_s(&f1, c1, "r");

        if (!f1 || ferror(f1) != 0) {
            return NULL;
        }

        char buffer[10];
        fgets_truncate(buffer, 10, f1);
        long max = strtol(buffer, NULL, 10);
        struct Sucursal* cab = NULL;
        for (long i = 0; i < max; i++) {
			char code[25];
            fgets_truncate(code, 25, f1);

			char name[50];
			fgets_truncate(name, 50, f1);

			char streetaddress[150];
			fgets_truncate(streetaddress, 150, f1);

			char email[50];
			fgets_truncate(email, 50, f1);

			char city[30];
			fgets_truncate(city, 30, f1);

			char state[30];
			fgets_truncate(state, 30, f1);

			char country[30];
			fgets_truncate(country, 30, f1);

			char phoneNumber[20];
			fgets_truncate(phoneNumber, 20, f1);

			agregarSucursal(&cab, code, name, streetaddress, email, city, state, country, phoneNumber);
        }

        fclose(f1);
        return cab;
    }
    return NULL;
}

void fputs_sucursales(struct Sucursal* cabeza, const char* c1) {
    FILE* f1;
    fopen_s(&f1, c1, "w");
    if (f1 && (ferror(f1) == 0)) {
		struct Sucursal* e = cabeza;
		long cont;
		for (cont = 0; e; cont++) e = e->prox;

		char buffer[10];
		itoa(cont, buffer, 10);
		fputs_newline(buffer, f1);

		e = cabeza;
		while (e) {
			fputs_newline(e->code, f1);
			fputs_newline(e->name, f1);
			fputs_newline(e->streetaddress, f1);
			fputs_newline(e->email, f1);
			fputs_newline(e->city, f1);
			fputs_newline(e->state, f1);
			fputs_newline(e->country, f1);
			fputs_newline(e->phoneNumber, f1);

            e = e->prox;
		}

        fclose(f1);
    }
}

struct EnvioPaquete* fget_envios_legacy(const char* c1) {
    if (true) {
        FILE *f1;
        fopen_s(&f1, c1, "r");

        if (!f1 || ferror(f1) != 0) {
            return NULL;
        }

        char buffer[10];
        fgets_truncate(buffer, 10, f1);
        long max = strtol(buffer, NULL, 10);
        struct EnvioPaquete* cab = NULL;
        for (long i = 0; i < max; i++) {
            char codeDestinationSucursal[25];
            fgets_truncate(codeDestinationSucursal, 25, f1);

            // ---
            fgets_truncate(buffer, 5, f1);
            short year = (short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            unsigned short month = (unsigned short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            unsigned short day = (unsigned short) strtol(buffer, NULL, 10);
            struct Date* dateDelivery = (struct Date*) malloc(sizeof(struct Date));
            dateDelivery->day = day;
            dateDelivery->month = month;
            dateDelivery->year = year;

            fgets_truncate(buffer, 5, f1);
            year = (short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            month = (unsigned short) strtol(buffer, NULL, 10);
            fgets_truncate(buffer, 5, f1);
            day = (unsigned short) strtol(buffer, NULL, 10);
            struct Date* dateReceived = (struct Date*) malloc(sizeof(struct Date));
            dateDelivery->day = day;
            dateDelivery->month = month;
            dateDelivery->year = year;

            // ---
            fgets_truncate(buffer, 5, f1);
            int readInsured = (int) strtol(buffer, NULL, 10);
            bool insured;
            if (readInsured) insured = true;
            else insured = false;

            char description[50];
            fgets_truncate(description, 50, f1);

            char codeDelivery[25];
            fgets_truncate(codeDelivery, 25, f1);

            fgets_truncate(buffer, 10, f1);
            unsigned long long weightPackageGrams = (unsigned long long) strtoll_compat(buffer, NULL, 10);

            char debitedCost[20];
            fgets_truncate(debitedCost, 20, f1);

            char idSender[15];
            fgets_truncate(idSender, 15, f1);

            char idReceiver[15];
            fgets_truncate(idReceiver, 15, f1);

            struct EnvioPaquete* e = __private__newEnvioPaquete(codeDestinationSucursal, dateDelivery, dateReceived,
                    insured, description, codeDelivery, weightPackageGrams, debitedCost, idSender, idReceiver);
            e->prox = cab;
            if (cab) cab->prev = e;
            cab = e;
        }

        fclose(f1);
        return cab;
    }
    return NULL;
}

void fputs_envios_legacy(struct EnvioPaquete* cabeza, const char* c1) {
    FILE* f1;
    fopen_s(&f1, c1, "w");
    if (f1 && (ferror(f1) == 0)) {
		struct EnvioPaquete* e = cabeza;
		long cont;
		for (cont = 0; e; cont++) e = e->prox;

		char buffer[10];
		itoa(cont, buffer, 10);
		fputs_newline(buffer, f1);

		e = cabeza;
		while (e) {
			fputs_newline(e->codeDestinationSucursal, f1);

            // ---
			itoa(e->dateDelivery->year, buffer, 10);
            fputs_newline(buffer, f1);
			itoa(e->dateDelivery->month, buffer, 10);
            fputs_newline(buffer, f1);
			itoa(e->dateDelivery->day, buffer, 10);
            fputs_newline(buffer, f1);

			itoa(e->dateReceived->year, buffer, 10);
            fputs_newline(buffer, f1);
			itoa(e->dateReceived->month, buffer, 10);
            fputs_newline(buffer, f1);
			itoa(e->dateReceived->day, buffer, 10);
            fputs_newline(buffer, f1);

            // ---
			if (e->insured) fputs_newline("1", f1);
			else fputs_newline("0", f1);

			fputs_newline(e->description, f1);
			fputs_newline(e->codeDelivery, f1);

            sprintf_s(buffer, 10, "%llu", e->weightPackageGrams);

            fputs_newline(e->debitedCost, f1);

			fputs_newline(e->idSender, f1);

			fputs_newline(e->idReceiver, f1);

            e = e->prox;
		}

        fclose(f1);
    }
}

#endif //PROJECT1_FILE_OPS_H
