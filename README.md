### Assignment2


**Implementing the board:**

To implement the board for my assignment I used a struct called game_board (in library.h) to hold the variables required
to create the board. This included the actual board, which is a 2D array, variables for the number of rows and columns, and
a variable called symbol that represents the empty spaces on the board. For the game pieces I used an array called
"colours" which contained 'B' for black pieces and 'W' for white ones. Using this array the appropriate disks can be 
written to the board. In main.c the aspects of the board were declared such as the board symbol for empty spaces which I declared
as '.' and the number of rows and columns which I set as 8 as there are 64 squares on an Othello board. Then initialiseBoard is 
called to set up the board before the game starts.This function creates a 2x2 square in the middle of the board with a top row of
pieces WB and bottom of BW as this is how the board starts in Othello. Printing the board is done by the printBoard function which
first displays the score of the game with the name of the players and how many pieces they have on the board. In my design of the board I wanted
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

**Game Logic:**

The next step in progressing my assignment was beginning to implement the game logic of Othello. I started off by creating a function called
playerMove that allowed a user to enter a move on the board. The function is called in a while loop in main with the colours of each player which
allows players to enter moves until the game has ceased. At it's simplest stage the function simply took a move in the form "letternumber" (e.g a7)
and then placed a disk of the player's colour in that location by assigning it to the board struct as follows `board.board[x][y] = colour`. As columns
are represented by letters and rows by numbers the move is given in the form column row but I am more familiar with row column so I swapped the values 
accordingly ` int x = y - 1; y = xL - 'a'; `. In the function I also added checks to ensure a user cannot enter moves of the wrong from e.g `if (y < 1 || y > 8 || isalpha(y))`.
In it's final fom the playerMove takes in a move from the user which can either be in the form explained before or they can enter 'p' to pass their turn, however
there is another function called anyMove which will be discussed later that checks if a player has a valid move on the board in which case they cannot pass.

Once a correct move is entered it is passed to a function called validMove which takes in the move coordinates, player's colour and a check number.
The purpose of the check number is that there are functions in my assignment that require moves to be validated but the board to not be altered and 
it is the check number which signifies if the board is to be altered or not. The function validMove simply checks if the move entered is correct in
the bounds of the board i.e it is in a position greater than or equal to 0 but less than or equal to 7 (index notation) ` if ( (a >= 0) && (a <= 7) && (b >= 0) && (b <= 7)){`.
If the move is in the bounds of the board the function then checks if there is a piece of either colour in the given position or if the function legalMove returns 1.
`if ((board.board[a][b] == colours[0] || board.board[a][b] == colours[1]) || legalMove(a, b, colour, check) == 1 ) `, if this statement is true validMove returns 1 signifying
the entered move is not valid and if it is false 0 is returned. In the call to validMove from playerMove if 1 is returned by validMove the player is informed their move is 
invalid and the function makes them choose a new move.

In othello a legal move consists of one that has at least one opponent piece adjacent to the current move and there must be a player's piece sandwiching the opponent piece(s) with the
current move with no empty spaces in between. I implemented this part of the game in my assignment using legalMove which checks if an entered move has an opponent piece anywhere adjacent
within a 1 space vicinity and with the function isSandwich which is called when an adjacent opponent piece is found and looks for a piece of the player's colour to sandwich the opponent's
piece(s) and flip them to the player's colour. The function legalMove takes in a move on the board, a colour and a check number (explained above). It contains boolean values to hold whether 
there is an opponent piece adjacent to the move entered (` bool oppAdj = false;`) and if the current move sandwiches opponent pieces with another player piece (`bool isSand = false;`). I also 
had to create boolean variables for holding truth values for whether a move is on any of the 4 perimeters of the board (`bool topPerim = false; bool leftPerim = false; bool botPerim = false; bool rightPerim = false;`).
This had to be accounted for as, for pieces on the perimeter you cannot check every space around them as some are off the board so using these variables certain moves can be flagged.  
I also created 4 variables to hold values for different positions around the move. For example the variable upx is assigned to 


