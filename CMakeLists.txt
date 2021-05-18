cmake_minimum_required(VERSION 3.17)
project(assignment2 C)

set(CMAKE_C_STANDARD 99)

add_executable(assignment2 library.h main.c initialiseGame.c playerMove.c gameInfo.c validMoveChecker.c isSandwich.c anyMove.c endGame.c)