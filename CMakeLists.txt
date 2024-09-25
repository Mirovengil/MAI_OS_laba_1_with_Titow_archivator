cmake_minimum_required(VERSION 3.5.0)
project(laba_1_byIVAN VERSION 0.1.0 LANGUAGES C)
include_directories(
    headers
)
add_executable(laba_1_byIVAN dearchivate.c ./src/archivator.c ./src/tree.c ./src/console_functions.c)

