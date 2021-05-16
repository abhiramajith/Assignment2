//
// Created by Abhiram on 16/05/2021.
//

#ifndef ASSIGNMENT2_LIBRARY_H
#define ASSIGNMENT2_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define NAME_SIZE 30 //Max size of player name
#define STRUCT_SIZE 20 //Size of struct array
#define BOARD_SIZE 8 //Max size of rows and columns on board
#define NUM_OF_COLOURS 2 //Number of colours

//Struct to hold Player information
typedef struct players{
    char playerName[NAME_SIZE];
    char playerColour;
}player;

player Player[STRUCT_SIZE]; //defining as array to store for 2 diff players

//Struct to hold game board
typedef struct game_board
{
    unsigned char board[BOARD_SIZE][BOARD_SIZE];
    int row;
    int col;
    char symbol;
}Game_Board;

Game_Board board; //Declaring synonym as global variable so board can be referenced and altered in any function

//global variables
int row = 0, col = 0;
int gameWon = 0; //signifies if the game has been won
char player1[NAME_SIZE], player2[NAME_SIZE]; //holds name of player1 and 2
bool bValidmove = true; //holds whether there exists valid move for black
bool wValidmove = true; //holds whether there exists valid move for white
char colours[NUM_OF_COLOURS] = {'B', 'W'}; //Holds game pieces/player colours

//function prototypes
int initializeBoard();
void printBoard(Game_Board Board);
int assignPlayers(void);
int playerMove(unsigned char colour);
int count(char colour, Game_Board Board);
int validMove (int a, int b, unsigned char colour, int check);
int legalMove(int a, int b, unsigned char colour, int check);
int isSandwich(int a, int b, int c, int d, unsigned char colour, int check);
int anyMove(unsigned char colour);
void gameOver(void);
void outFile(int winCheck, int score0, int score1);

#endif //ASSIGNMENT2_LIBRARY_H
