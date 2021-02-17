cmake_minimum_required(VERSION 3.17)
project(Ex6 C)

set(CMAKE_C_STANDARD 99)

add_executable(Ex6 main.c ex6.c Utils.c queue.c)