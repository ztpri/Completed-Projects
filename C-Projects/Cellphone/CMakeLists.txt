cmake_minimum_required(VERSION 3.17)
project(Cellphone C)

set(CMAKE_C_STANDARD 11)

add_executable(Cellphone main.c newfile.h Phone.c Tower.c PhoneTower.h)