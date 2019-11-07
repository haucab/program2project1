cmake_minimum_required(VERSION 3.15)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 SourceMain.c common.h date.h paquete.h persona.h sucursal.h utils.h)