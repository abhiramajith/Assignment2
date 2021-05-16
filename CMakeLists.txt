cmake_minimum_required(VERSION 3.17)
project(assignment2 C)

set(CMAKE_C_STANDARD 99)

add_executable(assignment2 main.c library.h initialiseGame.c playerMove.c gameInfo.c validMoveFinder.c isSandwich.c anyMove.c endGame.c)