CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

project(BS_Code C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)

add_subdirectory(util)

add_executable(ccut)

target_sources(ccut
        PRIVATE
        src/ccut.c
        src/helpers.c

        PUBLIC
        FILE_SET HEADERS
        FILES util/helpers.h
)



