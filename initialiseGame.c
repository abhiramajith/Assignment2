//
// Created by Abhiram on 17/05/2021.
// This c file initialises the game by assigning players to colours and by creating the starting board

#include "library.h"

//When this function is called players assigned to respective colours
int assignPlayers(void){


    printf("Enter player 1 name (Black): \n");
    scanf("%s", Player[0].playerName); //Storing name in player struct

    printf("Enter player 2 name (White): \n");
    scanf("%s", Player[1].playerName);


    Player[0].playerColour = colours[0];
    Player[1].playerColour = colours[1];

    printf("%s is black \n", Player[0].playerName);
    printf("%s is white \n", Player[1].playerName);

    printf("%s plays first as they control black.\n", Player[0].playerName);
    return 0;
}

//This function sets up the board before the game starts
int initializeBoard()
{
    for (row = 0; row < board.row; row++) //For loop for board rows
    {
        for (col = 0; col < board.col; col++)// For loop for board columns
        {
            board.board[row][col] = board.symbol; //Filling all empty spaces with board symbol '.'

            //Setting up initial othello square in middle of board
            board.board[3][3] = colours[1];
            board.board[3][4] = colours[0];
            board.board[4][3] = colours[0];
            board.board[4][4] = colours[1];
        }

    }

    return 0;
}