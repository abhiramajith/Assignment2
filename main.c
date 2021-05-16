#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

//Struct to hold Player information
typedef struct players{
    char playerName[20];
    char playerColour;
}player;

player Player[20]; //defining as array to store for 2 diff players

//Struct to hold game board
typedef struct game_board
{
    unsigned char board[9][9];
    int row;
    int col;
    char symbol;
}Game_Board;

Game_Board board; //Declaring synonym as global variable so board can be referenced and altered in any function

//function prototypes
int initializeBoard();
void printBoard(Game_Board Board);
int assignPlayers(void);
int playerMove(unsigned char colour);
int count(char colour, Game_Board Board);
int validMove (int a, int b, unsigned char colour, int check);
int legalMove(int a, int b, unsigned char colour, int check);
int isBetween(int a, int b, int c, int d, unsigned char colour, int check);
int anyMove(unsigned char colour);
void gameOver(void);
void outFile(int winCheck, int score0, int score1);

//global variables
int row = 0, col = 0;
int gameWon = 0; //signifies if the game has been won
char player1[20], player2[20]; //holds name of player1 and 2
bool bValidmove = true; //holds whether there exists valid move for black
bool wValidmove = true; //holds whether there exists valid move for white
char colours[2] = {'B', 'W'};

int main() {
    int wincheck = 0;
    board.symbol = '.'; //symbol to show empty spaces on board
    board.row = 8;
    board.col = 8;

    initializeBoard(); //calling function to set up board

    assignPlayers(); //Assigning players to colours

    printBoard(board); //Print initial board to users

    outFile(wincheck, count(colours[0], board), count(colours[1], board)); //Print current date and time to outfile

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

//When this function is called players assigned to respective colours
int assignPlayers(void){


    printf("Enter player 1 name (Black): \n");
    scanf("%s", Player[0].playerName); //Storing name in player struct

    printf("Enter player 2 name (White): \n");
    scanf("%s", Player[1].playerName);


    Player[0].playerColour = colours[0];

    Player[1].playerColour = colours[1];

    printf("%s is black \n", Player[0].playerName);
    printf("%s is white \n", Player[1].playerName);

    strcpy(player2, Player[1].playerName);
    strcpy(player1, Player[0].playerName);


    printf("%s plays first as they control black.\n", Player[0].playerName);
    return 0;
}

//This function sets up the board before the game starts
int initializeBoard()
{

    for (row = 0; row < board.row; row++) //For loop for board rows
         {
        for (col = 0; col < board.col; col++)// For loop for board columns
        {
            board.board[row][col] = board.symbol; //Filling all empty spaces with board symbol '.'
            //Setting up initial othello square in middle of board
            board.board[3][3] = colours[1];
            board.board[3][4] = colours[0];
            board.board[4][3] = colours[0];
            board.board[4][4] = colours[1];
        }


    }

    return 0;
}

//This function allows users to enter a move and then executes it accordingly
int playerMove(unsigned char colour){

    bool moveExists = true; //Holds truth value for if a move exists

    char xL; //Holds letter values for x axis of board
    int y; //Holds numbers of y axis of board

    //Label for when a new move must be chosen
    newMove:

    if (anyMove(colour) == 0){ //Call to anyMove to see if there is a move available for players colour

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

//This function is for printing the board to the user
void printBoard(Game_Board Board) {

    printf("\n|Score: %s (B) - %d | %s (W) - %d|\n",player1, count(colours[0], board), player2, count(colours[1], board)); //Print the score at the top

    printf("  a b c d e f g h \n"); //Top Label for columns of board

    for (row = 0; row < Board.row; row++) {//for loop for rows of board
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
    for (row = 0; row < Board.row; row++) {
        for (col = 0; col < Board.col; col++) {

            if (Board.board[row][col] == colour) { //If a piece of the given colour is found increment the count
                count++;
            }

        }
    }

    return count;
}

//This function checks if a move entered is valid on the board
//Returns 1 if invalid, 0 otherwise
int validMove (int a, int b, unsigned char colour, int check){

    if ( (a >= 0) && (a <= 7) && (b >= 0) && (b <= 7)){ //If the move is between 0 and 7 on both axes

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

        /*isBetween takes in the current move (a, b) and the co-ordinate of an opponent piece and checks if there is a piece of the player's
         * colour anywhere in the same line*/

        if (isBetween(a, b, upx, b, playerColour,check) == -1){ //If call to isBetween returns -1
            isBet = false; //not between any piece above
        }

        else{
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[upx][leftY] == oppColour && !leftPerim && !topPerim){ //if piece on top left diagonal is of opposite colour and current move is not on left perimeter or top perimeter

        if (isBetween(a, b, upx, leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of player's colour sandwiching opponents pieces to top left diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[upx][rightY] == oppColour && !topPerim && !rightPerim){ //if piece on top right diagonal is of the opposite colour and current move is not on top perimeter or right perimeter

        if (isBetween(a, b, upx, rightY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to the top right diagonal of the current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][b] == oppColour && !botPerim){ //if piece on bottom is of the opposite colour and current move is not on bottom perimeter

        if (isBetween(a, b, botx, b, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][leftY] == oppColour && !leftPerim && !botPerim){ //if piece on bottom left diagonal is of opposite colour and current move is not on left perimeter or bottom perimeter

        if (isBetween(a, b, botx,leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom left diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[botx][rightY] == oppColour && !rightPerim && !botPerim){ //if piece on bottom right diagonal is of opposite colour and current move is not on right perimeter or bottom perimeter

        if (isBetween(a, b, botx, rightY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to bottom right diagonal of current move
            oppAdj = true;
            isBet = true;
        }

    }


    if (board.board[a][leftY] == oppColour && !leftPerim){ //if piece on left is of opposite colour and current move is not on left perimeter

        if (isBetween(a, b, a, leftY, playerColour,check) == -1){
            isBet = false;
        }

        else{ //there is another piece of the player's colour sandwiching the opponents pieces to left of current move
            oppAdj = true;
            isBet = true;
        }

    }

    if (board.board[a][rightY] == oppColour && !rightPerim){ //if piece on right is of opposite colour and current move is not on right perimeter

        if ( isBetween(a, b, a, rightY, playerColour,check) == -1){
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

int isBetween(int a, int b, int c, int d, unsigned char colour, int check){

    bool isBetween = false;
    unsigned char playerColour;
    int e = a - c;
    int f = b - d;

    if (colour == colours[0]) {
        playerColour = colours[0];
    }
    else{
        playerColour = colours[1];
    }



    if ( e == 1 && f == 0){
        flip:
        for (int i = c; i >= 0; i--){

            if (isBetween && check == 0){
                if (board.board[i][d] == playerColour){
                    return 1;
                }
                board.board[i][d] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][d] == playerColour){
                    return 1;
                }
            }

            if (board.board[i][d] == board.symbol){
                return -1;
            }


            if (board.board[i][d] == playerColour && !isBetween){
                isBetween = true;
                goto flip;

            }

        }
        return -1;

    }

    else if (e == -1 && f == 0){
        flip2:
        for (int i = c; i <= 7; i++){

            if (isBetween && check == 0){
                if (board.board[i][d] == playerColour){
                    return 1;
                }
                board.board[i][d] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][d] == playerColour){
                    return 1;
                }
            }

            if (board.board[i][d] == board.symbol){
                return -1;
            }


            if (board.board[i][d] == playerColour && !isBetween){
                isBetween = true;
                goto flip2;
            }
        }
        return -1;
    }

    else if (e == 0 && f == 1){
        flip3:
        for (int j = d; j >= 0; j--){

            if (isBetween && check == 0){
                if (board.board[c][j] == playerColour){
                    return 1;
                }
                board.board[c][j] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[c][j] == playerColour){
                    return 1;
                }
            }

            if (board.board[c][j] == board.symbol){
                return -1;
            }

            if (board.board[c][j] == playerColour && !isBetween){
                isBetween = true;
                goto flip3;
            }
        }
        return -1;

    }

    else if (e == 0 && f == -1){
        flip4:
        for (int i = d; i <= 7; i++){

            if (isBetween && check == 0){
                if (board.board[c][i] == playerColour){
                    return 1;
                }
                board.board[c][i] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[c][i] == playerColour){
                    return 1;
                }
            }

            if (board.board[c][i] == board.symbol){
                return -1;
            }


            if (board.board[c][i] == playerColour && !isBetween){
                isBetween = true;
                goto flip4;
            }
        }
        return -1;
    }

    else if (e == 1 && f == 1){

        int i, j;
        flip5:
        i = c;
        j = d;
        while (i >= 0 && j >= 0){

            if (isBetween && check == 0){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
                board.board[i][j] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
            }

            --i;
            --j;

            if (board.board[i][j] == board.symbol){
                return -1;
            }

            if (board.board[i][j] == playerColour && !isBetween){
                isBetween = true;
                goto flip5;
            }
        }
        return -1;
    }

    else if (e == 1 && f == -1){

        int i, j;
        flip6:
        i = c;
        j = d;
        while (i >= 0 && j < 8){

            if (isBetween && check == 0){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
                board.board[i][j] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
            }

            --i;
            ++j;

            if (board.board[i][j] == board.symbol){
                return -1;
            }


            if (board.board[i][j] == playerColour && !isBetween){
                isBetween = true;
                goto flip6;
            }
        }

        return -1;

    }

    else if (e == -1 && f == 1){
        int i, j;
        flip7:
        i = c;
        j = d;
        while (i < 8 && j > 0){

            if (isBetween && check == 0){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
                board.board[i][j] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
            }

            ++i;
            --j;

            if (board.board[i][j] == board.symbol){
                return -1;
            }


            if (board.board[i][j] == playerColour && !isBetween){
                isBetween = true;
                goto flip7;
            }
        }

        return -1;

    }

    else if (e == -1 && f == -1){
        int i, j;
        flip8:
        i = c;
        j = d;
        while (i < 8 && j < 8){

            if (isBetween && check == 0){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
                board.board[i][j] = playerColour;
            }

            if(isBetween && check == 1){
                if (board.board[i][j] == playerColour){
                    return 1;
                }
            }

            ++i;
            ++j;

            if (board.board[i][j] == board.symbol){
                return -1;
            }


            if (board.board[i][j] == playerColour && !isBetween){
                isBetween = true;
                goto flip8;
            }
        }

        return -1;

    }

    return 0;

}

int anyMove(unsigned char colour){

    int x = 0;

    while (x <= 7){

        for (int i = 0; i <= 7; ++i) {
            if(validMove(i ,x, colour, 1) == 0){

                if(colour == colours[0]){
                    bValidmove = true;
                }

                else if(colour == colours[1]) {
                    wValidmove = true;
                }

                return 1;
            }

        }

        x++;

    }

    if(colour == colours[0]){
        bValidmove = false;
    }

    else if (colour == colours[1]){
        wValidmove = false;
    }

    if (!bValidmove && !wValidmove){
        gameWon = 1;
        gameOver();
    }

    return 0;
}

void gameOver(){
    int wincheck = 0;

    if (count(colours[0], board) > count(colours[1], board)){

        printf("\n%s wins the game! Final Score: %s (B) - %d |  %s (W) - %d \n", player1, player1, count(colours[0], board), player2, count(colours[1], board));
        wincheck = 1;
    }

    else if (count(colours[1], board) > count(colours[0], board)){
        printf("\n%s wins the game! Final Score: %s (W) - %d |  %s (B) - %d \n", player2, player2, count(colours[1], board), player1, count(colours[0], board));
        wincheck = 2;
    }

    else{
        printf("\nIts a draw! Final Score: %s (B) - %d |  %s (W) - %d \n", player1, count(colours[0], board), player2, count(colours[1], board));
        wincheck = 3;
    }

    printBoard(board);

    outFile(wincheck, count(colours[0], board), count(colours[1], board));

    exit(0);

}

void outFile(int winCheck, int score0, int score1){

    FILE *cfPtr; // othello-results.txt file pointer

    if ((cfPtr = fopen("othello-results.txt", "ab+")) == NULL){// fopen opens file; exits if can't be opened
        //ab+ opens a binary file in append mode
        printf("Could not open file.\n");

    }

    else{

        if (winCheck == 0) {
            char dateTime[30];
            struct tm tim;
            time_t now;
            now = time(NULL);
            tim = *(localtime(&now));
            strftime(dateTime, 30, "%b %d, %Y; %H:%M\n", &tim);
            fprintf(cfPtr, "%s", dateTime);
        }

        if (winCheck == 1){
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", player1, score0, player2, score1);
            fprintf(cfPtr, "%s won the game.\n\n", player1);
        }

        else if(winCheck == 2){
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", player2, score1, player1, score0);
            fprintf(cfPtr, "%s won the game.\n\n", player2);
        }

        else if (winCheck == 3){
            fprintf(cfPtr,  "|Final score: %s - %d : %s - %d|\n", player1, score0, player2, score1);
            fprintf(cfPtr, "The game ended as a draw.\n\n");
        }

        fclose(cfPtr);

    }
}