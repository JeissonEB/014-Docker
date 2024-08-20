cmake_minimum_required(VERSION 3.16.3)
project(Servers_Docker C)

set(CMAKE_C_STANDARD 11)

add_executable(Servers_Docker main.c
        commonSrc/argValidator.c
        commonSrc/commonHttpFunctions.c
        commonSrc/mime.c
        commonSrc/net.c
        headers/argValidator.h
        headers/commonHttpFunctions.h
        headers/mime.h
        headers/net.h)
