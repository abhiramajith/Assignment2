//
// Created by Abhiram on 17/05/2021.
//

#include "library.h"

/*This function checks locations around the current move where there are adjacent opponent pieces for pieces of the player's colour that
 * sandwich the opponent pieces. If a suitable piece is found all opponent pieces are turned into pieces of the player's colour.
 * The function takes in the current move (a,b) and the location of an adjacent opponent piece (c,d).
 * Using these two points you can calculate which direction to check for a sandwiching player piece by getting the difference between the
 * two points.
 * The players colour is also passed in to differentiate player and opp colours.
 * a check number is passed in, this is for differentiating between calls to the function where the board is
 * changed and calls where the board is not altered.*/

int isSandwich(int a, int b, int c, int d, unsigned char colour, int check){

    bool isSandwich = false; //Truth value for whether there is a player piece sandwiching opponent piece

    unsigned char playerColour; //Holds players colour

    //Using the difference between the two points you can find which direction to search in
    int e = a - c; // e holds the difference of a and c
    int f = b - d; // f holds the difference of a and c

    //assigning correct player colour to playerColour
    if (colour == colours[0]) {
        playerColour = colours[0];
    }
    else{
        playerColour = colours[1];
    }

    //An e of 1 and f of 0 means you should search in a straight line above the current move
    if ( e == 1 && f == 0){

        flip: //label that is called when opponent pieces need to be flipped to player colour

        for (int i = c; i >= 0; i--){ //for loop starting at row of opponent piece and moves up the board with each iteration

            if (isSandwich && check == 0){ //this if statement only runs if isSandwich is true and check is 0, this indicates changes should be made to the board

                if (board.board[i][d] == playerColour){ //If the position [i][d] on the board is a piece of the players colour (moving up on rows but column stays the same)

                    return 1; //Signifies that a players piece has been found so stop searching
                }

                board.board[i][d] = playerColour; //Turning opponent pieces to player pieces
            }

            if(isSandwich && check == 1){ //if isSandwich is true and check == 1 this means the function was called by anyMove to observe if there is a valid move to be
                //made without making changes to the board

                if (board.board[i][d] == playerColour){

                    return 1; //Stop searching
                }

            }

            if (board.board[i][d] == board.symbol){ //If an empty space is found

                return -1; //returning -1 means the current moves is not part of a sandwich
            }


            if (board.board[i][d] == playerColour && !isSandwich){ //If a player piece is found and isSandwich is false

                //isSandwich is set to true as there is a player piece sandwiching the opponent pieces with the current move
                isSandwich = true;

                goto flip; /* goto line 460 as now isSandwich is true so opponent pieces can be flipped to players colour */

            }

        }
        return -1; //No sandwich is found

    }

        //An e of -1 and f of 0 means you should search in a straight line below the current move
    else if (e == -1 && f == 0){

        flip2:

        for (int i = c; i <= 7; i++){//for loop starting at row of opponent piece and moves down the board with each iteration

            if (isSandwich && check == 0){

                if (board.board[i][d] == playerColour){

                    return 1; //sandwich found
                }

                board.board[i][d] = playerColour; //flip to playerColour
            }

            if(isSandwich && check == 1){

                if (board.board[i][d] == playerColour){

                    return 1; //sandwich found
                }
            }

            if (board.board[i][d] == board.symbol){

                return -1; //No sandwich is found
            }


            if (board.board[i][d] == playerColour && !isSandwich){

                isSandwich = true;

                goto flip2; //goto line 507 so pieces can be flipped to player's colours

            }
        }

        return -1; //No sandwich is found

    }

        //An e of 0 and f of 1 means you should search in a straight line left of the current move
    else if (e == 0 && f == 1){

        flip3:

        for (int j = d; j >= 0; j--){ //for loop starting at column of opponent piece and moves left of the board with each iteration

            if (isSandwich && check == 0){
                if (board.board[c][j] == playerColour){

                    return 1; //sandwich found
                }

                board.board[c][j] = playerColour;
            }

            if(isSandwich && check == 1){
                if (board.board[c][j] == playerColour){

                    return 1; //sandwich found
                }
            }

            if (board.board[c][j] == board.symbol){

                return -1; //No sandwich is found
            }

            if (board.board[c][j] == playerColour && !isSandwich){

                isSandwich = true;

                goto flip3; //goto line 552
            }
        }
        return -1; //No sandwich is found

    }

        //An e of 0 and f of -1 means you should search in a straight line right of the current move
    else if (e == 0 && f == -1){

        flip4:

        for (int i = d; i <= 7; i++){ //for loop starting at column of opponent piece and moves right of the board with each iteration

            if (isSandwich && check == 0){

                if (board.board[c][i] == playerColour){

                    return 1; //sandwich found
                }
                board.board[c][i] = playerColour;
            }

            if(isSandwich && check == 1){
                if (board.board[c][i] == playerColour){

                    return 1; //sandwich found
                }
            }

            if (board.board[c][i] == board.symbol){

                return -1; //No sandwich is found
            }


            if (board.board[c][i] == playerColour && !isSandwich){

                isSandwich = true;
                goto flip4; //goto line 591
            }
        }

        return -1; //No sandwich is found
    }

        //An e of 1 and f of 1 means you should search in a straight line to the top left diagonal of the current move
    else if (e == 1 && f == 1){

        //When searching diagonally both row and column positions change as you move so both must be iterated
        int i, j;

        flip5:
        i = c;
        j = d;

        while (i >= 0 && j >= 0){ //As your moving on top left diagonal you get closer to 0 each time

            if (isSandwich && check == 0){
                if (board.board[i][j] == playerColour){

                    return 1; //sandwich found
                }

                board.board[i][j] = playerColour;
            }

            if(isSandwich && check == 1){

                if (board.board[i][j] == playerColour){

                    return 1; //sandwich found
                }
            }

            //Decrementing i and j to move to next position on diagonal
            --i;
            --j;

            if (board.board[i][j] == board.symbol){

                return -1; //No sandwich is found
            }

            if (board.board[i][j] == playerColour && !isSandwich){

                isSandwich = true;
                goto flip5; //goto line 633
            }
        }

        return -1; //No sandwich is found
    }

        //An e of 1 and f of -1 means you should search in a straight line to the top right diagonal of the current move
    else if (e == 1 && f == -1){

        int i, j;

        flip6:
        i = c;
        j = d;
        while (i >= 0 && j < 8){ //As your moving on top right diagonal you get closer to 0 each time on rows and to 7 on columns

            if (isSandwich && check == 0){
                if (board.board[i][j] == playerColour){

                    return 1;
                }

                board.board[i][j] = playerColour;
            }

            if(isSandwich && check == 1){
                if (board.board[i][j] == playerColour){

                    return 1;
                }
            }

            //Decrementing i and incrementing j allows you to move along the diagonal to the top right
            --i;
            ++j;

            if (board.board[i][j] == board.symbol){

                return -1;
            }


            if (board.board[i][j] == playerColour && !isSandwich){

                isSandwich = true;
                goto flip6; //goto line 680
            }
        }

        return -1;

    }

        //An e of -1 and f of 1 means you should search in a straight line to the bottom left diagonal of the current move
    else if (e == -1 && f == 1){

        int i, j;

        flip7:
        i = c;
        j = d;

        while (i < 8 && j > 0){ //As your moving on bottom left diagonal you get closer to 7 each time on rows and to 0 on columns

            if (isSandwich && check == 0){
                if (board.board[i][j] == playerColour){

                    return 1;
                }

                board.board[i][j] = playerColour;
            }

            if(isSandwich && check == 1){
                if (board.board[i][j] == playerColour){

                    return 1;
                }
            }

            //Incrementing i and decrementing j allows you to move along the diagonal to the bottom left
            ++i;
            --j;

            if (board.board[i][j] == board.symbol){

                return -1;
            }

            if (board.board[i][j] == playerColour && !isSandwich){

                isSandwich = true;
                goto flip7; //goto line 727
            }
        }

        return -1;

    }

        //An e of -1 and f of -1 means you should search in a straight line to the bottom right diagonal of the current move
    else if (e == -1 && f == -1){

        int i, j;

        flip8:
        i = c;
        j = d;

        while (i < 8 && j < 8){ //As your moving on bottom right diagonal you get closer to 7 each time

            if (isSandwich && check == 0){
                if (board.board[i][j] == playerColour){

                    return 1;
                }

                board.board[i][j] = playerColour;
            }

            if(isSandwich && check == 1){

                if (board.board[i][j] == playerColour){

                    return 1;
                }
            }

            //Incrementing i and j allows you to move along the diagonal to the bottom right
            ++i;
            ++j;

            if (board.board[i][j] == board.symbol){

                return -1;
            }


            if (board.board[i][j] == playerColour && !isSandwich){

                isSandwich = true;
                goto flip8;
            }
        }

        return -1;

    }

    return 0;

}
