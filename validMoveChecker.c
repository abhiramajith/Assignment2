//
// Created by Abhiram on 17/05/2021.
// This file contains validMove and legalMove which checks if the entered move is bot valid and legal and if it is it will be passed to isSandwich

#include "library.h"

//This function checks if a move entered is valid on the board
//Returns 1 if invalid, 0 otherwise
int validMove (int a, int b, unsigned char colour, int check){

    if ( (a >= 0) && (a <= 7) && (b >= 0) && (b <= 7)){ //If the move is between 0 and 7 on both row and column

        if ((board.board[a][b] == colours[0] || board.board[a][b] == colours[1]) || legalMove(a, b, colour, check) == 1 ) { //If the move has a piece of either colour already on the board or if legalMove returns 1

            return 1; //Return 1 as move is not valid
        }

    }

    return 0;

}

//This function checks if the move entered is legal
//Returns 1 if not legal and 0 otherwise
//Takes in an integer called check that is 1 when being called by anyMove (ensures no changes are made to the board)
// Check is 0 when being called after a move is entered (for when board must be altered)
int legalMove(int a, int b, unsigned char colour, int check){

    bool oppAdj = false; //Truth value (Tv) for if there is an opponent piece adjacent to the current move
    bool isBet = false; //Tv for if the current move is between another piece of the same colour

    //Truth values for whether the move made is on the top, left, bottom or right perimeter of the board respectively
    //This must be taken into account as for move on the perimeter you ar not able to check all positions around current move depending on which perimeter it is on
    bool topPerim = false;
    bool leftPerim = false;
    bool botPerim = false;
    bool rightPerim = false;

    unsigned char playerColour;
    unsigned char oppColour;

    //These variables represent areas around the current move

    int upx = a-1; //upx refers to the row above the current move
    int botx = a+1; //botx refers to row below
    int leftY = b-1; // column to the left
    int rightY = b+1; //column to the right

    if ( a == 0 ){ //If a is 0 the move is on the top perimeter
        topPerim = true;
    }
    if ( b == 0 ){ //left perimeter
        leftPerim = true;
    }
    if ( a == 7 ){ //bottom perimeter
        botPerim = true;
    }
    if (b == 7){ //right perimeter
        rightPerim = true;
    }


    if (colour == colours[0]) { //If passed in colour = B
        playerColour = colours[0];
        oppColour = colours[1]; // = W
    }

    else{
        playerColour = colours[1];
        oppColour = colours[0];
    }

    if (board.board[upx][b] == oppColour && !topPerim){ //if piece above is of opposite colour and current move is not on top perimeter

        /*isSandwich takes in the current move (a, b) and the co-ordinate of an opponent piece and checks if there is a piece of the player's
         * colour anywhere in the same line*/

        if (isSandwich(a, b, upx, b, playerColour,check) == -1){ //If call to isSandwich returns -1
            isBet = false; //not between any piece above
        }

        else{
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[upx][leftY] == oppColour && !leftPerim && !topPerim){ //if piece on top left diagonal is of opposite colour and current move is not on left perimeter or top perimeter

        if (isSandwich(a, b, upx, leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of player's colour sandwiching opponents pieces to top left diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[upx][rightY] == oppColour && !topPerim && !rightPerim){ //if piece on top right diagonal is of the opposite colour and current move is not on top perimeter or right perimeter

        if (isSandwich(a, b, upx, rightY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to the top right diagonal of the current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][b] == oppColour && !botPerim){ //if piece on bottom is of the opposite colour and current move is not on bottom perimeter

        if (isSandwich(a, b, botx, b, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][leftY] == oppColour && !leftPerim && !botPerim){ //if piece on bottom left diagonal is of opposite colour and current move is not on left perimeter or bottom perimeter

        if (isSandwich(a, b, botx,leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom left diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][rightY] == oppColour && !rightPerim && !botPerim){ //if piece on bottom right diagonal is of opposite colour and current move is not on right perimeter or bottom perimeter

        if (isSandwich(a, b, botx, rightY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom right diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }


    if (board.board[a][leftY] == oppColour && !leftPerim){ //if piece on left is of opposite colour and current move is not on left perimeter

        if (isSandwich(a, b, a, leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to left of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[a][rightY] == oppColour && !rightPerim){ //if piece on right is of opposite colour and current move is not on right perimeter

        if ( isSandwich(a, b, a, rightY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to right of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if(!oppAdj && !isBet){ //if no opponent piece adjacent to current move and no player piece sandwiches opponent pieces

        return 1; //Signifies illegal move

    }


    return 0; //Signifies legal move

}