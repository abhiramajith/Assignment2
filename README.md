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
This had to be accounted for as, for pieces on the perimeter you cannot check every space around them as some are off the board so using these variables certain moves can be flagged. To find if a move is on the perimeter 
I checked if a was equal to 0 (top perimeter) or 7 (bottom perimeter) and if b was equal to 0 (left perimeter) or 7 (right perimeter). I also created 4 variables to hold values for different positions around the move.
For example the variable upA is assigned to a - 1 this is because a holds the row position of the move and taking away 1 from it refers to the row above so to check the move above the current move you would check `board.board[upA][b] == oppColour`.
Similarly I assigned botA to a + 1 (row below), leftB to b - 1 (column to left) and rightB (column to left). With these variables you can check every position around the move made for an opponent piece .eg to check the top
right diagonal: `if (board.board[upA][rightB] == oppColour && !topPerim && !rightPerim)`, this example also shows the use of the boolean perimeter variables as when checking the top right diagonal the move cannot be on the top or right perimeter
because you would be checking off of the board. If an opponent piece is found isSandwich is called with the current move and the location of the opponent piece, if the function returns -1 then this means a player piece was not found sandwiching the 
opponent piece with the current move and isSand is set to false. Otherwise oppAdj is set to true and so is isSand signifying there is an opponent piece adjacent to the current move and there is a player piece to sandwich the opponent piece. This is done for 
every move touching the current move (1 move above, below, left, right, top left diagonal, top right diagonal, bottom left diagonal and bottom right diagonal). At the end of the function if both oppAdj and isSand are false the function returns 1 to signify 
the move entered is illegal and otherwise it returns 0.

The function isSandwich is called by legalMove to check locations around the current move where there are adjacent opponent pieces for pieces of the player's colour that sandwich the opponent pieces. The function takes in the coordinates of the current move (a, b) and the coordinates
of an adjacent opponent piece (c, d). It also takes in the player's colour and a check number. When a sandwich is found the function also flips all opponent pieces between the player pieces to the player's colour. To find which direction to search for a player piece in I used the current 
move and opponent piece. To capture opponent pieces there must be a player piece on either side of a line of opponent pieces,to calculate the direction to look for the player piece once the opponent piece is found I took the coordinates of the opponent piece found from the respective
coordinates of the current move: (`int e = a - c;, int f = b - d; `). I found that this difference can be used to figure out which direction to search in as the values are the same every time for the same locations. For example if there was a player piece at row 6 column 5 and an opponent 
piece at row 5 column 6 the difference between the player and opponent move would be 1 and -1 which is the same for every move with an adjacent opponent piece on the top right diagonal so then I configured the code so if this difference is found you should continue searching in a straight 
line on the top right diagonal until a player piece or empty space is found. I did this for every potential direction using so this included 8 different if statements; (1,0) = upwards, (-1, 0) = downwards, (0, 1) = leftwards, (0, -1) = rightwards, (1,1) = top left diagonal, (1, -1) = top right diagonal,
(-1, 1) = bottom left diagonal, (-1, -1) = bottom right diagonal. Using these calculations once a direction is identified I then moved in a straight line in the direction until a disk of the player's colour is found or an empty space is found. In the cases where only either the row or column
is moved to travel in a direction (up, down, left, right) I used a for loop to do this but for diagonal movement a while loop had to be used as both row and column must be moved. How the function flips opponent disks to ones of the player's colours is as follows.
Under the if statement for any direction code a goto label is placed, then a for loop (or while if it's a diagonal) is run to move in a straight line in the direction specified by the difference calculated. The for loop/while contains 5 if statements. The function has a boolean variable called isSandwich that
is set to false by default. The boolean variable dictates whether disks are flipped or not. The first time the loop is run, an if statement looks for a piece of the player's colour while isSandwich is false ` if (board.board[i][j] == playerColour && !isSandwich){`. Once this statement is triggered isSandwich is set to 
true and the goto is activated jumping back to before the for/while loop begins. This causes the for loop to be run again but this time as isSandwich is true there are 2 if statements that can be applied, one where the board is altered and the opponents disks are flipped (`if (isSandwich && check == 0){`) and one where 
the board is unaffected `if(isSandwich && check == 1){` , the latter is used by a later function (anyMove) that checks the board to see if a player has any moves on the board so no changes should be made and 1 is returned once a player disk is found signifying that there is a sandwich present and therefore a valid move. 
The check number allows for differentiating between altering and not altering the board. In the if for flipping opponent disks the for/while loop follows the same path as it did the first run but this time all opponent disks are changed to player disks ` board.board[i][j] = playerColour;` and once the sandwiching player disk
is reached the function returns 1, `if (board.board[i][j] == playerColour){ return 1; }`. There is also an if in place for 

                 



