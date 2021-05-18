//
// Created by Abhiram on 17/05/2021.

#include "library.h"

//This function allows users to enter a move and then executes it accordingly

int playerMove(unsigned char colour){

    bool moveExists = true; //Holds truth value for if a move exists

    char xL; //Holds letter values for column of board
    int y; //Holds numbers of row of board

    //Label for when a new move must be chosen
    newMove:

    if (anyMove(colour) == 0){ //Call to anyMove to see if there is a move available for players colour (returns 0 if no move)

        printf("\nYou have no valid moves! Enter p to pass\n");
        moveExists = false; //Set to false as there is no move to make

    }

    printf("\nEnter the coordinates of the move you would like to make (e.g a7)\n"
           "Enter 'p' to pass (can only pass if you have no valid moves):\n " );

    scanf(" %c", &xL); //Scanning in xL (column of move)

    if (xL == 'p') { //If the user enters p for pass

        if (moveExists) { //if there is a move they can make
            printf("\nThere is still a move you can make you cannot pass\n");
            goto newMove; //Choose a newmove
        }

        else{
            printf("Passing your turn to the opponent\n");
            return 0;
        }

    }

    else if (xL < 'a' || xL > 'h' || isdigit(xL)){ //If xL is not a letter between a and h or it is a number
        printf("\nInvalid move please enter a letter between a and h followed by a number between 1 and 8\n");
        getchar(); //Removes space from previous scanf
        goto newMove; //Choose a newmove
    }


    scanf("%d", &y); //Scan in y (row of move)

    if (y < 1 || y > 8 || isalpha(y)){ //if y is less than 1 or greater than 8 or if it is a letter choose new move
        printf("\nInvalid move please enter a letter between a and f followed by a number between 1 and 8\n");
        goto newMove;
    }

    //assigning y value to x and converting x value to integer and assigning to y
    //I did this because at first I had the code set up where the user entered their
    //move as row-column instead of column-row
    //1 is minused from y as the index notation goes from 0 to 7
    //This is accounted for when 'a' is taken from xL

    int x = y - 1; //Row position of move
    y = xL - 'a'; //Column position of move

    if (validMove(x ,y, colour, 0) == 1){ //Calling validMove to see if entered move is valid to games rules, returns 1 if invalid

        printf("\nThe move entered was either invalid or illegal please try again\n");
        goto newMove;

    }

    board.board[x][y] = colour; //Placing player's colour marker in move location they gave

    printBoard(board); //Print the board to display the move has been made

    return 0;
}
