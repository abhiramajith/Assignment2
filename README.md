### Assignment2


**Implementing the board:**

To implement the board for my assignment I used a struct called game_board (in library.h) to hold the variables required
to create the board. This included the actual board, which is a 2D array, variables for the number of rows and columns, and
a variable called symbol that represents the empty spaces on the board. For the game pieces I used an array called
"colours" which contained 'B' for black pieces and 'W' for white ones. In main.c the aspects of the board were declared
such as the board symbol for empty spaces which I declared as '.' and the number of rows and columns which
I set as 8 as there are 64 squares on an Othello board. Then initialiseBoard is called to set up the board before the game starts.
This function creates a 2x2 square in the middle of the board with a top row of pieces WB and bottom of BW as this is how 
the board starts in Othello. Printing the board is done by the printBoard function which first displays the score of the
game with the name of the players and how many pieces they have on the board. In my design of the board I wanted
The row and column signifiers on all sides so I printed "a b c d e f g h" on the top and bottom and 1 - 8 down each side.
The board is then printed with the corresponding piece in each location of the board printed out,
empty spaces contain '.', spaces occupied by black contain 'B' and spaces held by white contain 'W'. To
calculate the score a simple function called count is used that, given a colour ('W' or 'B'), goes through each position in the board and counts how many 
of the given piece there is on the board and returns it.

**Implementing the players:**

To implement the players I created a struct called players (in library.h) to hold player information. It contains
variables for both player name and player colour. These variables are assigned in the function assignPlayers where users are prompted to enter their name.
In the function player 1 is assigned to black and player 2 to white. Initially I had it where the players were randomly assigned colours
but I found this was not necessary to the code specifications so I altered it accordingly. The end of the function tells users that 
the player playing as black plays first as per game rules.



