### Assignment2


**Implementing the board:**

To implement the board for my assignment, I used a struct called game_board (in library.h) to hold the variables required
to create the board. This included the actual board, a 2D array, variables for the number of rows and columns, and
a variable called symbol representing the empty spaces on the board. I used an array called
"colours" for the game pieces, which contained 'B' for black disks and 'W' for white ones. Using this array, the appropriate disks can be written to the board. In main.c, the aspects of the board were declared; this included board symbol for empty spaces, which I declared
as '.' and the number of rows and columns, which I set as eight as there are 64 squares on an Othello board. Then initialiseBoard is called to set up the board before the game starts. This function creates a 2x2 square in the middle of the board with a top row of
disks WB and bottom of BW, reflecting how the board starts in Othello. Printing the board is done by the printBoard function, which
first displays the game's score with the name of the players and how many pieces they have on the board. I wanted
The row and column signifiers on all sides in my design of the board, so I printed "a b c d e f g h" on the top and bottom and 1 - 8 down each side.
The board is then printed with the corresponding piece in each location of the board printed out,
empty spaces contain '.', areas occupied by black contain 'B' and spaces held by white contain 'W'. To
calculate the score function called count is used that, given a colour ('W' or 'B'), which goes through each position in the board and counts how many of the assigned pieces there are on the board and returns the count.

**Implementing the players:**

To implement the players, I created a struct called players (in library.h) to hold player information. It contains
variables for both player name and player colour. These variables are assigned in the function assignPlayers, where users are prompted to enter their name.
In the function, player one is assigned to black and player 2 to white. Initially, I had it where the players were randomly assigned colours, but I found this was unnecessary to the code specifications, so I altered it accordingly. The end of the function tells users that
the player playing as black plays first as per game rules.

**Game Logic:**

The next step in progressing my assignment was beginning to implement the game logic of Othello. I started by creating a function called
playerMove that allowed a user to enter a move on the board. The function is called in a while loop in main with the colours of each player; this
allows players to enter moves until the game has ceased. At its simplest stage, the function took a move in the form "letter-number" (e.g. a7)
and then placed a disk of the player's colour in that location by assigning it to the board struct as follows `board.board[x][y] = colour`. As columns
are represented by letters and rows by numbers, the move is given in the form column row, but I am more familiar with row-column, so I swapped the values accordingly ` int x = y - 1; y = xL - 'a'; `. In the function I also added checks to ensure a user cannot enter moves of the wrong from e.g `if (y < 1 || y > 8 || isalpha(y))`.
In its final form the playerMove takes in a move from the user, which can either be in the format explained before or they can enter 'p' to pass their turn, however
there is another function called anyMove which will be discussed later that checks if a player has a valid move on the board, in which case they cannot pass.

Once a correct move is entered, it is passed to a function called validMove, which takes in the move coordinates, player's colour and a check number.
The purpose of the check number is that there are functions in my assignment that require moves to be validated but the board is not to be altered, and it is the check number that signifies if the board is to be modified. The function validMove checks if the move entered is correct in
the bounds of the board i.e it is in a position greater than or equal to 0 but less than or equal to 7 (index notation) ` if ( (a >= 0) && (a <= 7) && (b >= 0) && (b <= 7)){`.
If the move is in the bounds of the board the function then checks if there is a piece of either colour in the given position or if the function legalMove returns 1.
`if ((board.board[a][b] == colours[0] || board.board[a][b] == colours[1]) || legalMove(a, b, colour, check) == 1 ) `, if this statement is true validMove returns 1 signifying
the entered move is not valid and if it is false 0 is returned. In the call to validMove from playerMove if 1 is returned by validMove the player is informed their move is
invalid and the function makes them choose a new move.

In Othello, a legal move consists of at least one opponent piece adjacent to the current move, and there must be a player's piece sandwiching the opponent piece(s) with the
current move with no empty spaces in between. I implemented this part of the game in my assignment using legalMove, which checks if an entered move has an opponent piece anywhere adjacent
within a one space vicinity. Then, the function isSandwich is called when an adjacent opponent piece is found and looks for a piece of the player's colour to sandwich the opponent's
piece(s) and flip them to the player's colour. The function legalMove takes in a move on the board, a colour and a check number (explained above). It contains boolean values to hold whether there is an opponent piece adjacent to the move entered (` bool oppAdj = false;`) and if the current move sandwiches opponent pieces with another player piece (`bool isSand = false;`). I also had to create boolean variables for holding truth values for whether a move is on any of the four perimeters of the board (`bool topPerim = false; bool leftPerim = false; bool botPerim = false; bool rightPerim = false;`).
This had to be accounted for as for pieces on the perimeter, you cannot check every space around them as some are off the board, so using these variables, certain moves can be flagged. To find if a move is on the perimeter
I checked if a was equal to 0 (top perimeter) or 7 (bottom perimeter) and if b was equal to 0 (left perimeter) or 7 (right perimeter). I also created four variables to hold values for different positions around the move.
For example, the variable upA is assigned to a - 1; this is because a holds the row position of the move and taking away 1 from it refers to the row above, so to check the move above the current move, you would check `board.board[upA][b] == oppColour`.
Similarly I assigned botA to a + 1 (row below), leftB to b - 1 (column to left) and rightB (column to left). With these variables you can check every position around the move made for an opponent piece, .e.g. to check the top
right diagonal: `if (board.board[upA][rightB] == oppColour && !topPerim && !rightPerim)`. This example also shows the use of the boolean perimeter variables as when checking the top right diagonal; the move cannot be on the top or right perimeter
because you would be checking off the board. If an opponent piece is found isSandwich is called with the current move and the location of the opponent piece, if the function returns -1 then this means a player piece was not found sandwiching the opponent piece with the current move and isSand is set to false. Otherwise, oppAdj is set to true, and so is isSand, signifying there is an opponent piece adjacent to the current move and there is a player piece to sandwich the opponent piece. This is done for every move touching the current move (1 move above, below, left, right, top left diagonal, top right diagonal, bottom left diagonal and bottom-right diagonal). At the end of the function, if both oppAdj and isSand are false, the function returns 1 to signify the move entered is illegal, and otherwise, it returns 0.

The function isSandwich is called by legalMove to check locations around the current move where there are adjacent opponent pieces for pieces of the player's colour that sandwich the opponent pieces. The function takes in the coordinates of the current move (a, b) and the coordinates
of an adjacent opponent piece (c, d). It also takes in the player's colour and a check number. When a sandwich is found, the function also flips all opponent pieces between the player pieces to the player's colour. To find which direction to search for a player piece in I used the current move and opponent piece. To capture opponent pieces, there must be a player piece on either side of a line of opponent pieces, to calculate the direction to look for the player piece once the opponent piece is found I took the coordinates of the opponent piece found from the respective
coordinates of the current move: (`int e = a - c;, int f = b - d; `). I found that this difference can be used to figure out which direction to search in as the values are the same every time for the same locations. For example, if there were a player piece at row 6 column 5 and an opponent piece at row 5 column 6, the difference between the player and the opponent move would be 1 and -1, which is the same for every move with an adjacent opponent piece on the top right diagonal so then I configured the code so if this difference is found you should continue searching in a straight line on the top right diagonal until a player piece or empty space is found. I did this for every potential direction using so this included 8 different if statements; (1,0) = upwards, (-1, 0) = downwards, (0, 1) = leftwards, (0, -1) = rightwards, (1,1) = top left diagonal, (1, -1) = top-right diagonal,
(-1, 1) = bottom-left diagonal, (-1, -1) = bottom-right diagonal. Using these calculations, once a direction is identified, I then moved in a straight line in the direction until a disk of the player's colour is found, or an empty space is found. In the cases where only either the row or column
is moved to travel in a direction (up, down, left, right), I used a for loop to do this, but for diagonal movement, a while loop had to be used as both row, and column must be moved. How the function flips opponent disks to the player's colours is as follows.
Under the if statement for any direction code, a goto label is placed. A for/while loop is run to move in a straight line in the direction specified by the difference calculated. The for loop/while contains five if statements. The function has a boolean variable called isSandwich that
is set to false by default. The boolean variable dictates whether disks are flipped or not. The first time the loop is run, an if statement looks for a piece of the player's colour while isSandwich is false ` if (board.board[i][j] == playerColour && !isSandwich){`. Once this statement is triggered isSandwich is set to
true and the goto is activated jumping back to before the for/while loop begins. This causes the for loop to be rerun, but this time as isSandwich is true, there are two if statements that can be applied, one where the board is altered and the opponent's disks are flipped (`if (isSandwich && check == 0){`) and one where the board is unaffected `if(isSandwich && check == 1){`, the latter is used by a later function (anyMove) that checks the board to see if a player has any moves on the board so no changes should be made and one is returned once a player disk is found signifying that there is a sandwich present and therefore a valid move.
The check number allows for differentiating between altering and not altering the board. In the if for flipping opponent disks the for/while loop follows the same path as it did the first run but this time all opponent disks are changed to player disks ` board.board[i][j] = playerColour;` and once the sandwiching player disk
is reached the function returns 1, `if (board.board[i][j] == playerColour){ return 1; }`. There is also an if in place for checking if an empty space is found at any point in the line `board.board[i][j] == board.symbol` and this statement returns -1, which means there is no sandwiching piece in the
direction of the opponent piece adjacent to the current move entered. -1 is also returned if the for/while loop ends and none of the conditions are met. The functions validMove, legalMove and isSandwich are vital in my implementation as it contains all the code for Othello's game logic in making valid moves and capturing pieces.

The next function I implemented is anyMove which is used to check the board to see if there are any valid moves for the current player. This is needed for the assignment as a player should not be allowed to enter 'p' for pass if they have a valid move on the board. The function takes in the disk colour of the current player and goes through
every position on the board using a combination of a while and for loop. The while loop iterates the columns and the for loop iterates the rows so for each column every row on that column is checked before moving to the next column. The moves are checked using the validMove function, and it is called with a check number of 1, which informs all the functions not to alter the board as they would if they were called with a check of 0. If validMove returns 0, that means there is a valid move on the board for the colour specified. There are global boolean variables for the respective colours that hold truth values for whether a valid move exists or not and they are set to true depending on which colour
was called with the function `if(colour == colours[0]){ bValidmove = false; }` and `else if (colour == colours[1]){ wValidmove = false; }`. If both these variables are false gameWon is set to one and the gameOver function is called as there are no moves left on the board. anyMove returns 0 if there is no valid move for the colour entered. The function is called
in playerMove before the player makes their move, and if the function returns 0, the user is informed that they have no moves to make and that they must pass. A boolean variable moveExists is also set to false, which allows the player to pass their turn if it is false but gives the message "There is still a move you can make you cannot pass" when it is true, and the
user tries to pass. The anyMove function is also called twice in main before a player makes their move once with each colour disk as if there are no valid moves for either, the game should end.

The final function I wrote in terms of game logic was the gameOver function which is called once there are no moves left to make on the board. The function takes in nothing and returns nothing as it is simply for printing the results of the game to the screen and for calling the function
outFile to print the results of the game to the specified text file. The function has one variable called wincheck, which holds either 1, 2 or 3 depending on who wins the game. There are three conditional statements in the function for the three different potential outcomes of the game, Black win, White win and tie. The winner is decided by calling the count
function in the if statement and comparing the disk count of both colours on the board e.g  `if (count(colours[0], board) > count(colours[1], board))`. If there are more black pieces, black wins if there are more white pieces, white wins; else its a draw. For each case, the winner is printed out with the winner's name, the final score of the game and the final state of the board. In each case, the appropriate wincheck is also assigned. After the final board is printed, a call is made to outFile with the wincheck and scores of both players, `outFile(wincheck, count(colours[0], board), count(colours[1], board));`, this writes the results of the game to the file. Lastly, `exit(0)` is called to end the program.

**Writing to file:**

The assignment specification called for the result of a game to be written to a text file called "othello-results.txt". I created a function called outFile to do this. The specification requires the date and time at the start of the game to be printed to the file first, then once the game is over the results are then printed.
The function takes in an integer called winCheck and the scores of both players as input, winCheck tells the function what to print to the file depending on what number it is. The first thing the function does is create a text file called "othello-results.txt" in ab+ mode, this is so that the result of each game can be continually added to
the file. Calling the function with a winCheck of 0 will print the current date and time to the file, this is done at the start of the program in main when the game starts. The date and time are written to the file using functions from the time.h library. I used strftime to format the time and date as a string and the used fprintf to write it
to the file `strftime(dateTime, 30, "%b %d, %Y; %H:%M\n", &tim); ` `fprintf(cfPtr, "%s", dateTime);`. When the game ends the function gameOver is called, which calls the outFile function with a winCheck number of 1, 2 or 3 depending on the game-winner. The appropriate if statement is then triggered depending on the winCheck number and the
final score of the game and the winner's name is printed to the file. Finally, the file is closed once everything has been written.

**Testing:**

I rigorously tested my program by using an established online version of Othello and mimicking every move I made in my program in the online game. This way, I could see where my code was going wrong easily, and I could track the moves that made my program work incorrectly and fix them accordingly. This made it easy to debug errors in my code as I was able to
try the same combination of moves until I received the same result as the online game. I also played the game on my own to observe if there were any discrepancies. 



                 



