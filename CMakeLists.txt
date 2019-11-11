cmake_minimum_required(VERSION 3.15)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 SourceMain.c common.h date.h paquete.h persona.h sucursal.h utils.h date_validate.h paquete_validate.h persona_validate.h sucursal_validate.h menu_1_mantenimiento.h menu_2_operaciones.h menu_3_consultas.h common_cli_windows.h)