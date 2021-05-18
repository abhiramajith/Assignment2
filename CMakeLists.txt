cmake_minimum_required(VERSION 3.17)
project(Assignment C)

set(CMAKE_C_STANDARD 99)

add_executable(Assignment library.h main.c initialiseGame.c playerMove.c gameInfo.c validMoveChecker.c isSandwich.c anyMove.c endGame.c)