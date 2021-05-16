#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct players{
    char playerName[20];
    char playerColour[5];
}player;

player Player[20];

typedef struct board{
    int xPos;
    int yPos;
    char disc[2];
}board;
board Board[64];


const char *colours[2] = {"white", "black"};

int rows = 0;


void assignPlayers(void);
int main() {

    assignPlayers();
    for (int i = 0; i < 8; i++) {
        Board[i].xPos = i + 1;
        for (int j = 0; j < 8; j++) {

            Board[j].yPos = j + 1;
        }
    }

    printf("%d %d", Board[5].xPos, Board[7].yPos);

}
void assignPlayers(void){

    srand(time(NULL));

    printf("Enter player 1 name: \n");
    scanf("%s", Player[rows].playerName);

    rows++;

    printf("Enter player 2 name: \n");
    scanf("%s", Player[rows].playerName);

    int randnum = rand() % 2;


    printf("%s\n", Player[0].playerName);
    printf("%s\n", Player[1].playerName);

    if ( randnum == 0) {
        rows = 0;
        strcpy(Player[rows].playerColour, colours[randnum]);

        rows++;
        strcpy(Player[rows].playerColour, colours[randnum + 1]);
    }

    else if (randnum == 1){
        rows = 0;
        strcpy(Player[rows].playerColour, colours[randnum]);
        rows++;
        strcpy(Player[rows].playerColour, colours[randnum - 1]);

    }

    if (randnum == 0){
        printf("%s is white \n", Player[0].playerName);
        printf("%s is black \n", Player[1].playerName);
    }

    else{
        printf("%s is black \n", Player[0].playerName);
        printf("%s is white \n", Player[1].playerName);
    }

}
