cmake_minimum_required(VERSION 3.17)
project(Market C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-Wall -Werror")

add_executable(Market main.c newfile.h groceryFile.c groceryFile.h stats.c stats.h)