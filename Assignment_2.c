#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
typedef struct players{
    char playerName[20];
    char playerColour[1];
}player;

player Player[20];

typedef struct game_board
{
    int board[9][9];
    int row;
    int col;
    char symbol;
}Game_Board;
Game_Board board;

int initializeBoard();
void printBoard(Game_Board Board);
int playerMove(char colour[5]);
int count(char colour, Game_Board Board);
int validMove (int X, int Y);

const char *colours[2] = {"W", "B"};

int rows = 0;
int row_index = 0, col_index = 0;
int gameWon = 0;
char black[20], white[20];
int assignPlayers(void);
int main() {

    board.symbol = '.';
    board.row = 8;
    board.col = 8;

    initializeBoard();

    if (assignPlayers() == 0){

        printf("%s plays first as they control black.\n", Player[1].playerName);
    }

    else{
        printf("%s plays first as they control black.\n", Player[0].playerName);
    }

    while (gameWon != 1){

        playerMove(Player[0].playerColour);

        playerMove(Player[1].playerColour);


    }


}
int assignPlayers(void){

    srand(time(NULL));

    printf("Enter player 1 name: \n");
    scanf("%s", Player[rows].playerName);

    rows++;

    printf("Enter player 2 name: \n");
    scanf("%s", Player[rows].playerName);

    int randnum = rand() % 2;


    if ( randnum == 0) {
        rows = 0;

        strncpy(Player[0].playerColour, colours[randnum], 1);

        strncpy(Player[1].playerColour, colours[randnum + 1], 1);

        printf("%s is white \n", Player[0].playerName);
        printf("%s is black \n", Player[1].playerName);

        strcpy( black, Player[1].playerName);
        strcpy(white, Player[0].playerName);
    }

    else if (randnum == 1){

        rows = 0;
        strncpy(Player[0].playerColour, colours[randnum],1);

        strncpy(Player[1].playerColour, colours[randnum - 1],1);

        printf("%s is black \n", Player[0].playerName);
        printf("%s is white \n", Player[1].playerName);

        strcpy( white, Player[1].playerName);
        strcpy(black, Player[0].playerName);

    }

    return randnum;


}

int initializeBoard()
{

    for (row_index = 0; row_index < board.row; row_index++)
    {
        for (col_index = 0; col_index < board.col; col_index++)
        {
            board.board[row_index][col_index] = board.symbol;
            board.board[3][3] = 'W';
            board.board[3][4] = 'B';
            board.board[4][3] = 'B';
            board.board[4][4] = 'W';
        }


    }


}

int playerMove(char colour[5]){
    int x, y;
    label:


        printf("Enter the coordinates of the move you would like to make (e.g 7 7): \n");
        scanf("%d %d", &x, &y);

        x -= 1;
        y -= 1;

        if (board.board[x][y] != '.') {

            printf("There is a piece already at that location.\n");
            goto label;
        }



        if (strcmp(colour , "W") == 0){
        board.board[x][y] = 'W';
        }

        else{
            board.board[x][y] = 'B';
        }

    printBoard(board);
}

void printBoard(Game_Board Board) {

    printf("\n|Score: %s(W) - %d | %s(B) - %d|\n",white, count('W', board), black, count('B', board));
    printf("  1 2 3 4 5 6 7 8 \n");
    for (row_index = 0; row_index < Board.row; row_index++) {
        printf("%d ", row_index + 1);
        for (col_index = 0; col_index < Board.col; col_index++) {

            printf("%c ", Board.board[row_index][col_index]);
        }
        printf("\n");

    }
}

int count(char colour, Game_Board Board){
    int count = 0;

    for (row_index = 0; row_index < Board.row; row_index++) {
        for (col_index = 0; col_index < Board.col; col_index++) {

            if (Board.board[row_index][col_index] == colour) {
                count++;
            }

        }
    }

    return count;
}

int validMove (int X, int Y){

    if ( (X >= 1) && (X <= 8) && (Y >= 1) && (Y <= 8)){
        return 1;
    }

    else{
        return 0;
    }

}
