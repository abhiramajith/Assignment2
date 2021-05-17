//
// Created by Abhiram on 17/05/2021.
// This file is responsible for displaying game info such as the score and the current state of the board to the screen

#include "library.h"

//This function is for printing the board to the user
void printBoard(Game_Board Board) {

    printf("\n|Score: %s (B) - %d | %s (W) - %d|\n",Player[0].playerName, count(colours[0], board), Player[1].playerName, count(colours[1], board)); //Print the score at the top

    printf("  a b c d e f g h \n"); //Top Label for columns of board

    for (row = 0; row < board.row; row++) {//for loop for rows of board
        printf("%d ", row + 1); //Printing row number at start of row

        for (col = 0; col < Board.col; col++) {

            printf("%c ", Board.board[row][col]); //Printing out the symbol at each location of the board
        }
        printf("%d ", row + 1); //Printing the row number at the end of the row

        printf("\n");

    }
    printf("  a b c d e f g h \n"); //Bottom Label for columns of board
}

//Function for counting number of pieces of a colour currently on the board
//Returns count
int count(char colour, Game_Board Board){

    int count = 0;

    //Going through each position on the board
    for (row = 0; row < board.row; row++) {
        for (col = 0; col < Board.col; col++) {

            if (Board.board[row][col] == colour) { //If a piece of the given colour is found increment the count
                count++;
            }

        }
    }

    return count;
}