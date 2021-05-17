#include "library.h"

//Declaring global variables
int row = 0, col = 0;
int gameWon = 0; //signifies if the game has been won
bool bValidmove = true; //holds whether there exists valid move for black
bool wValidmove = true; //holds whether there exists valid move for white
char colours[NUM_OF_COLOURS] = {'B', 'W'}; //Holds game pieces/player colours

int main() {

    int wincheck = 0; //wincheck is needed for outFile function, wincheck of 0 allows for time of game start to be written to the outfile

    board.symbol = '.'; //symbol to show empty spaces on board

    //Setting size of rows and columns
    board.row = BOARD_SIZE;
    board.col = BOARD_SIZE;

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


