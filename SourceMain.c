#include "common.h"
#include "common_cli_windows.h"
#include "sucursal.h"
#include "utils.h"
#include "file_ops.h"
#include "menu_1_mantenimiento.h"
#include "menu_2_operaciones.h"
#include "menu_3_consultas.h"



void __restricted__MenuPpalPrintf(void* ignored) {
    printf("+--------------------------------------------------------+\n");
    printf("+-------------------- MENU PRINCIPAL --------------------+\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                    1. Mantenimiento                    |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                     2. Operaciones                     |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                      3. Consultas                      |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|                        4. Salir                        |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("\n");
    printf("Introduzca su opcion en el teclado y presione ENTER.\n");
    printf(" > ");
}

int main(void) {
	struct Sucursal* cabezaSPPal = fgets_sucursales("sucursales.dat");
	struct Persona* cabezaPPPal = fgets_personas("personas.dat");
	fget_envios("envios.dat", cabezaSPPal, cabezaPPPal);

    int opc = 99;
    while (opc != 4) {
        system("cls");
        scanf_integer(&opc, &__restricted__MenuPpalPrintf, NULL);
        switch (opc) {
            case 1:
				menuMantenimiento(&cabezaPPPal, &cabezaSPPal);
                break;
            case 2:
                menuOperaciones(&cabezaSPPal, &cabezaPPPal);
                break;
            case 3:
                menuConsultas(&cabezaSPPal, &cabezaPPPal);
                break;
            case 4: break;
            default:
                printf(" [Opcion invalida]\n");
                system("pause");
                break;
        }
    }
}
