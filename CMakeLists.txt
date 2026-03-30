CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

project(BS_Code C)

set(CMAKE_C_STANDARD 99)

add_executable(ccut ccut.c
        ccut.h
        helpers.c
        helpers.h
)
