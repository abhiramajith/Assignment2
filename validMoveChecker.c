//
// Created by Abhiram on 17/05/2021.
// This file contains validMove and legalMove which checks if the entered move is bot valid and legal and if it is it will be passed to isSandwich

#include "library.h"

//This function checks if a move entered is valid on the board
//Returns 1 if invalid, 0 otherwise
int validMove (int a, int b, unsigned char colour, int check){

        if ((board.board[a][b] == colours[0] || board.board[a][b] == colours[1]) || legalMove(a, b, colour, check) == 1 ) { //If the move has a piece of either colour already on the board or if legalMove returns 1

            return 1; //Return 1 as move is not valid
        }

    return 0;

}

//This function checks if the move entered is legal
//Returns 1 if not legal and 0 otherwise
//Takes in an integer called check that is 1 when being called by anyMove (ensures no changes are made to the board)
// Check is 0 when being called after a move is entered (for when board must be altered)
int legalMove(int a, int b, unsigned char colour, int check){

    bool oppAdj = false; //Truth value (Tv) for if there is an opponent piece adjacent to the current move
    bool isSand = false; //Tv for if the current move sanwiches opponent pieces wwith another player piece


    unsigned char playerColour;
    unsigned char oppColour;

    //These variables represent areas around the current move

    int upA = a-1; //upA refers to the row above the current move
    int botA = a+1; //botA refers to row below
    int leftB = b-1; // column to the left
    int rightB = b+1; //column to the right

    if (colour == colours[0]) { //If passed in colour = B

        playerColour = colours[0];
        oppColour = colours[1]; // = W
    }

    else{

        playerColour = colours[1];
        oppColour = colours[0];
    }

    if (board.board[upA][b] == oppColour){ //if piece above is of opposite colour

        /*isSandwich takes in the current move (a, b) and the co-ordinate of an opponent piece and checks if there is a piece of the player's
         * colour anywhere in the same line*/

        if (isSandwich(a, b, upA, b, playerColour,check) == -1){ //If call to isSandwich returns -1

            isSand = false; //not between any piece above
        }

        else{

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[upA][leftB] == oppColour){ //if piece on top left diagonal is of opposite colour

        if (isSandwich(a, b, upA, leftB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of player's colour sandwiching opponents pieces to top left diagonal of current move

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[upA][rightB] == oppColour){ //if piece on top right diagonal is of the opposite colour

        if (isSandwich(a, b, upA, rightB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to the top right diagonal of the current move

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[botA][b] == oppColour){ //if piece on bottom is of the opposite colour

        if (isSandwich(a, b, botA, b, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom of current move

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[botA][leftB] == oppColour){ //if piece on bottom left diagonal is of opposite colour

        if (isSandwich(a, b, botA,leftB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom left diagonal of current move

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[botA][rightB] == oppColour){ //if piece on bottom right diagonal is of opposite colour

        if (isSandwich(a, b, botA, rightB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom right diagonal of current move

            oppAdj = true;
            isSand = true;
        }

    }


    if (board.board[a][leftB] == oppColour){ //if piece on left is of opposite colour

        if (isSandwich(a, b, a, leftB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to left of current move

            oppAdj = true;
            isSand = true;
        }

    }

    if (board.board[a][rightB] == oppColour){ //if piece on right is of opposite colour

        if ( isSandwich(a, b, a, rightB, playerColour,check) == -1){

            isSand = false;
        }

        else{ //There is another piece of the player's colour sandwiching the opponents pieces to right of current move

            oppAdj = true;
            isSand = true;
        }

    }

    if(!oppAdj && !isSand){ //if no opponent piece adjacent to current move and no player piece sandwiches opponent pieces

        return 1; //Signifies illegal move

    }


    return 0; //Signifies legal move

}