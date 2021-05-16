#include "library.h"


int main() {
    int wincheck = 0;
    board.symbol = '.'; //symbol to show empty spaces on board
    board.row = 8;
    board.col = 8;

    initializeBoard(); //calling function to set up board

    assignPlayers(); //Assigning players to colours

    printBoard(board); //Print initial board to users

    outFile(wincheck, count(colours[0], board), count(colours[1], board)); //Print current date and time of game start to outfile

    while (gameWon != 1){ //While game not won

        if (count(colours[0], board) + count(colours[1], board) == 64){ //if player scores add up to 64 game is over
            gameOver(); //call to end game and display winners
        }

        printf("%s's (B) turn\n", Player[0].playerName);
        playerMove(Player[0].playerColour); //calling playerMove with player's colour

        printf("%s's (W) turn\n", Player[1].playerName);
        playerMove(Player[1].playerColour);


    }
}


