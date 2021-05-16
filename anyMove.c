//
// Created by Abhiram on 17/05/2021.
//

#include "library.h"

/* This function takes in a colour on the board and checks the every board position for valid moves for that colour
 * returns 1 if there is a valid move on the board
 * returns 0 if there is not */

int anyMove(unsigned char colour){

    //x represents column position
    int x = 0;

    //This while and for loop combination allows every position on the board to be checked by checking every row for
    //a particular column before it is iterated

    while (x <= 7){

        for (int i = 0; i <= 7; ++i) { //Every row position is checked with the current column

            if(validMove(i ,x, colour, 1) == 0){ //If validMove returns 0 there is a valid move on the board for the colour specified
                //validMove is called with a check number of 1, this tells the function not to alter the
                //board when checking for valid moves

                if(colour == colours[0]){ //If colour is B set global variable bValidmove to true

                    bValidmove = true;
                }

                else if(colour == colours[1]) { //If colour is W set global variable bwValidmove to true
                    wValidmove = true;
                }

                return 1; //Signifies that there is a valid move
            }

        }

        x++; //increment to next column

    }

    //if no valid move is found set appropriate variable to false

    if(colour == colours[0]){
        bValidmove = false;
    }

    else if (colour == colours[1]){
        wValidmove = false;
    }

    if (!bValidmove && !wValidmove) { //If both boolean variables are false the game should end as there are no moves left

        gameWon = 1; //causes while loop in main to stop
        gameOver(); //call to gameOver to display results of game
    }

    return 0; //Signifies there is no valid move on the board for inputted colour
}