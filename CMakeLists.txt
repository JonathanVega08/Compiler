cmake_minimum_required(VERSION 3.8)
project(Compilador)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Lexico.cpp Lexico.h Stack.h Stack.cpp LRTable.h LR_Table.cpp Simbolo.h Simbolo.cpp SymbolTable.h SymbolTable.cpp ErrorTable.h ErrorTable.cpp CodeGeneration.h Sintactico.h Sintactico.cpp)
add_executable(Compilador ${SOURCE_FILES})