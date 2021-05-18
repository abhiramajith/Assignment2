//
// Created by Abhiram on 17/05/2021.
// This file contains the gameOver function which displays results of the game to the screen and the outFile
// function which prints the results of the game to a text file

#include "library.h"

/* This function is called when the game has ended so the results of the game
 * can be displayed such as the winner and the final score*/

void gameOver(){

    //This variable allows for differentiation of who wins the game
    //wincheck of 1 means Black won, 2 means white won , 3 means it was a draw
    int wincheck;

    if (count(colours[0], board) > count(colours[1], board)){ //if there is more black pieces(colours[0]) than white (colours[1]) then black has won the game

        printf("\n%s wins the game! Final Score: %s (B) - %d |  %s (W) - %d \n", Player[0].playerName, Player[0].playerName, count(colours[0], board), Player[1].playerName, count(colours[1], board)); //Print game results
        wincheck = 1;
    }

    else if (count(colours[1], board) > count(colours[0], board)){ //if more white pieces than black

        printf("\n%s wins the game! Final Score: %s (W) - %d |  %s (B) - %d \n", Player[1].playerName, Player[1].playerName, count(colours[1], board), Player[0].playerName, count(colours[0], board));
        wincheck = 2;
    }

    else{ //else it is a draw

        printf("\nIts a draw! Final Score: %s (B) - %d |  %s (W) - %d \n", Player[0].playerName, count(colours[0], board), Player[1].playerName, count(colours[1], board));
        wincheck = 3;
    }

    printBoard(board); //print the final board

    outFile(wincheck, count(colours[0], board), count(colours[1], board)); //Call to outFile to write results of game to text file

    printf("\nThank you for playing!\n\n");
    exit(0); //end program

}

/* This function writes the date and time of when the game started and the final result of the game
 * to a text file called othello-results.txt*/
void outFile(int winCheck, int score0, int score1){

    FILE *cfPtr; // othello-results.txt file pointer

    if ((cfPtr = fopen("othello-results.txt", "ab+")) == NULL){// fopen opens file; exits if can't be opened

        //ab+ opens a binary file in append mode, results will be continually added to same file
        printf("Could not open file.\n");

    }

    else{

        if (winCheck == 0) { //Function is called at start of program with winCheck 0 so date and time of start of game is written to file

            //Writing date and time at start of game to file using time.h library functions
            char dateTime[30]; //Holds date and time
            struct tm tim;
            time_t now;
            now = time(NULL);
            tim = *(localtime(&now));
            strftime(dateTime, 30, "%b %d, %Y; %H:%M\n", &tim); //strftime formats time as string
            fprintf(cfPtr, "%s", dateTime); //Printing date & time to file
        }

        if (winCheck == 1){ //winCheck of 1 means black has won

            //Writing game result to file
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", Player[0].playerName, score0, Player[1].playerName, score1);
            fprintf(cfPtr, "%s won the game.\n\n", Player[0].playerName);
        }

        else if(winCheck == 2){ //winCheck of 2 means white has won

            //Writing game result to file
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", Player[1].playerName, score1, Player[0].playerName, score0);
            fprintf(cfPtr, "%s won the game.\n\n", Player[1].playerName);
        }

        else if (winCheck == 3){ //winCheck of 3 means draw

            //Writing game result to file
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", Player[0].playerName, score0, Player[1].playerName, score1);
            fprintf(cfPtr, "The game ended as a draw.\n\n");
        }

        fclose(cfPtr); //Closing file

    }
}