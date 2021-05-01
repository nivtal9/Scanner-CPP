cmake_minimum_required(VERSION 3.17)
project(scanner)

set(CMAKE_CXX_STANDARD 14)

add_executable(scanner main.cpp token.cpp token.h symtab.cpp symtab.h scanner.cpp scanner.h tokenstrings.h tokentype.h)