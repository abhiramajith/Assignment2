#include "library.h"

//INSTRUCTIONS
/* In 'Edit Configurations' (assignment2|Debug), ensure you have working directory as "$ProjectFileDir$".
 * otherwise outFile will not be able to write to "othello-results.txt*/

//Declaring global variables so they are recognised in other source files
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

    printf("\n#### Welcome to Othello ####\n\n");

    initializeBoard(); //calling function to set up board

    assignPlayers(); //Assigning players to colours

    printBoard(board); //Print initial board to users

    outFile(wincheck, count(colours[0], board), count(colours[1], board)); //Print current date and time of game start to outfile

    while (gameWon != 1){ //While game not won

        anyMove(colours[0]); //Checks if there are any valid moves for 'B'

        anyMove(colours[1]); //Checks if there are any valid moves for 'W'

        printf("%s's (B) turn\n", Player[0].playerName);
        playerMove(Player[0].playerColour); //calling playerMove with player's colour

        printf("%s's (W) turn\n", Player[1].playerName);
        playerMove(Player[1].playerColour);


    }
}


