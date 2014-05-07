/*Now on AI branch, will allow the user to challenge a PC*/
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<curses.h>
#define BS 8
struct player
{
	char name[32];
	char token;
	int score;
	int location[2];
};

struct availableMove
{
	int location[2];
	int score;
	int available;
};

void showOptions()
{
	printw("\nOptions:");
	printw("\nP - Play Black White.");
	printw("\nQ - Quit program.");
	printw("\nSelection: ");
}

void clrscr()
{
	clear();
	refresh();
}

void quit()
{
	refresh();
	getch();
	endwin();
}

void clearBoard(char userBoard[BS][BS])
{
	int loopXVar, loopYVar;
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
			userBoard[loopXVar][loopYVar] = ' ';
}

void printBoard(char userBoard[BS][BS])
{
	int loopXVar, loopYVar;
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			printw("|%c", userBoard[loopXVar][loopYVar]);
		}
		printw("|");
		printw("\n");
	}
}

void countScore(char playerToken, char userBoard[BS][BS], int *userScore)
{
	int loopXVar, loopYVar;
	int countScore = 0;
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			if (userBoard[loopXVar][loopYVar] == playerToken)
			{
				countScore++;
			}
		}
	}
	*userScore = countScore;
}

void drawBoard(char userBoard[BS][BS], struct player player1, struct player player2, char (*gameMessage)[64], int *countFlip)
{
	/*	Draw the board received each time using proper formatting*/
	int loopXVar, loopYVar;
	clrscr();
	
	if (!strcmp(*gameMessage, "1"))
	{
		printw("\nPlayer %s's turn! (%c)", player1.name, player1.token);
	}
	else if (!strcmp(*gameMessage, "2"))
	{
		printw("\nPlayer %s's turn! (%c)", player2.name, player2.token);
	}
	else
	{
		printw("\n%s", *gameMessage);
	}
	/*	Prints player stats*/
	printw("\n%s\t :\t%i", player1.name, player1.score);
	printw("\n%s\t :\t%i", player2.name, player2.score);
	if (*countFlip != 1)
	{
		printw("\n%i flips made.\n", *countFlip);
	}
	else
	{
		printw("\n%i flip made.\n", *countFlip);
	}
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			printw("|%c", userBoard[loopXVar][loopYVar]);
		}
		printw("|");
		printw("\n");
	}
	printw("\nw: Up\ts: Down\na: Left\td: Right\nx: Confirm\nc: Skip\nQ: Quit\n");
	refresh();
}

int changeBoard(char actualBoard[BS][BS], char playerToken, int location[2])
{
	/*	Determines if a loop has already made a flip*/
	int hasCount;
	/*	Flips made*/
	int count = 0;
	/*	Determines limit*/
	int x, y;
	/*	Loop values*/
	int xx, yy;
	/*	Right*/
	hasCount = 0;
	/*	Diagonal specific*/
	bool continueLoop = false;
	int diagonalMovement = 0;
	int diagonalLoop = 0;
	/*	Right*/
	for (y = location[1]; y < 8; y++)
	{
		if (actualBoard[location[0]][y] == ' ')
		{
			break;
		}
		else if (actualBoard[location[0]][y] == playerToken)
		{
			for (yy = location[1]; yy < y; yy++)
			{
				actualBoard[location[0]][yy] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				break;
			}
		}
	}
	/*	Left*/
	hasCount = 0;
	for (y = location[1]; y >= 0; y--)
	{
		if (actualBoard[location[0]][y] == ' ')
		{
			break;
		}
		else if (actualBoard[location[0]][y] == playerToken)
		{
			for (yy = location[1]; yy > y; yy--)
			{
				actualBoard[location[0]][yy] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				break;
			}
		}
	}
	/*	Down*/
	hasCount = 0;
	for (x = location[0]; x < 8; x++)
	{
		if (actualBoard[x][location[1]] == ' ')
		{
			break;
		}
		else if (actualBoard[x][location[1]] == playerToken)
		{
			for (xx = location[0]; xx < x; xx++)
			{
				actualBoard[xx][location[1]] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				break;
			}
		}
	}
	/*	Up*/
	hasCount = 0;
	for (x = location[0]; x >= 0; x--)
	{
		if (actualBoard[x][location[1]] == ' ')
		{
			break;
		}
		else if (actualBoard[x][location[1]] == playerToken)
		{
			for (xx = location[0]; xx > x; xx--)
			{
				actualBoard[xx][location[1]] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				break;
			}
		}
	}
	
	/*	Diagonal-Right-Down*/
	hasCount = 0;
	continueLoop = true;
	diagonalMovement = 1;
	x = location[0];
	y = location[1];
	while (continueLoop)
	{
		if (location[0] + diagonalMovement < 8)		
			x = location[0] + diagonalMovement;
		else
			break;
		if (location[1] + diagonalMovement < 8)
			y = location[1] + diagonalMovement;
		else
			break;
		if (actualBoard[x][y] == ' ')
		{
			continueLoop = false;
		}
		else if (actualBoard[x][y] == playerToken)
		{
			for (diagonalLoop = 0; diagonalLoop < diagonalMovement; diagonalLoop++)
			{
				actualBoard[location[0] + diagonalLoop][location[1] + diagonalLoop] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				continueLoop = false;
			}
		}
		else
		{
			diagonalMovement++;
		}
	}
	/*	Diagonal-Right-Up*/
	hasCount = 0;
	continueLoop = true;
	diagonalMovement = 1;
	x = location[0];
	y = location[1];
	while (continueLoop)
	{
		if (location[0] - diagonalMovement >= 0)
			x = location[0] - diagonalMovement;
		else
			break;
		if (location[1] + diagonalMovement < 8)
			y = location[1] + diagonalMovement;
		else
			break;
		if (actualBoard[x][y] == ' ')
		{
			continueLoop = false;
		}
		else if (actualBoard[x][y] == playerToken)
		{
			for (diagonalLoop = 0; diagonalLoop < diagonalMovement; diagonalLoop++)
			{
				actualBoard[location[0] - diagonalLoop][location[1] + diagonalLoop] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				continueLoop = false;
			}
		}
		else
		{
			diagonalMovement++;
		}
	}
	/*	Diagonal-Left-Down*/
	hasCount = 0;
	continueLoop = true;
	diagonalMovement = 1;
	x = location[0];
	y = location[1];
	while (continueLoop)
	{
		if (location[0] + diagonalMovement < 8)
			x = location[0] + diagonalMovement;
		else
			break;
		if (location[1] - diagonalMovement >= 0)
			y = location[1] - diagonalMovement;
		else
			break;
		if (actualBoard[x][y] == ' ')
		{
			continueLoop = false;
		}
		else if (actualBoard[x][y] == playerToken)
		{
			for (diagonalLoop = 0; diagonalLoop < diagonalMovement; diagonalLoop++)
			{
				actualBoard[location[0] + diagonalLoop][location[1] - diagonalLoop] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				continueLoop = false;
			}
		}
		else
		{
			diagonalMovement++;
		}
	}
	/*	Diagonal-Left-Up*/
	hasCount = 0;
	continueLoop = true;
	diagonalMovement = 1;
	x = location[0];
	y = location[1];
	while (continueLoop)
	{
		if (location[0] - diagonalMovement >= 0)
			x = location[0] - diagonalMovement;
		else
			break;
		if (location[1] - diagonalMovement >= 0)
			y = location[1] - diagonalMovement;
		else
			break;
		if (actualBoard[x][y] == ' ')
		{
			continueLoop = false;
		}
		else if (actualBoard[x][y] == playerToken)
		{
			for (diagonalLoop = 0; diagonalLoop < diagonalMovement; diagonalLoop++)
			{
				actualBoard[location[0] - diagonalLoop][location[1] - diagonalLoop] = playerToken;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				count--;
				continueLoop = false;
			}
		}
		else
		{
			diagonalMovement++;
		}
	}
	
	/*	We only make changes to the original board if there actually were changes made*/
	/*	count = 100;*/
	return count;
}

struct availableMove availableOptions(char actualBoard[BS][BS], char playerToken)
{
	int x, y;
	int location[2];
	int locationHighest[2];
	int currentCount = 0;
	int countHighest = 0;
	int available = 0;
	char testBoard[BS][BS];
	struct availableMove returnOption;
	for (x = 0; x < BS; x++)
	{
		for (y = 0; y < BS; y++)
		{
			
			memcpy(testBoard, actualBoard, sizeof (char) * BS * BS);
			//printBoard(testBoard);
			location[0] = x;
			location[1] = y;
			if (testBoard[location[0]][location[1]] == ' ')
			{
				testBoard[x][y] = playerToken;
				currentCount = changeBoard(testBoard, playerToken, location);
				if (currentCount > 0)
				{
					available++;
				}
				
				if (currentCount > countHighest)
				{
					countHighest = currentCount;
					memcpy(locationHighest, location, sizeof(locationHighest));
				}
			}
			clearBoard(testBoard);
		}
	}
	memcpy(returnOption.location, locationHighest, sizeof returnOption.location);
	returnOption.score = countHighest;
	returnOption.available = available;
	return returnOption;
}


struct player playGame()
{
	/*	Actual game function, returns winner*/
	/*	Boards*/
	char actualBoard[BS][BS];
	char playBoard[BS][BS];
	/*	Game message to display*/
	char gameMessage[64];
	/*	Player input for in-game*/
	char playerInput;
	/*	Determines if a player can set the character*/
	int countFlip = 0;
	/*	Loops*/
	bool gameLoop = true, playLoop = true, nameQuery = true;
	/*	Players*/
	int playerTurn = 2;
	struct player player1;
	struct player player2;
	struct player currentPlayer;
	struct availableMove returnOption;
	struct availableMove playerPC;
	player1.token = '@';
    player2.token = 'O';
	player1.score = 0;
	player2.score = 0;
	player1.location[0] = 0;
	player1.location[1] = 0;
	player2.location[0] = 0;
	player2.location[1] = 0;
	while (nameQuery)
	{
		printw("\nPlease input player names:");
		printw("\nPlayer 1 (@): ");
		refresh();
		getstr(player1.name);
		printw("Player 2 (O): ");
		refresh();
		getstr(player2.name);
	}
	/*	Initial board*/
	clearBoard(playBoard);
	playBoard[3][4] = player1.token;
	playBoard[4][3] = player1.token;
	playBoard[3][3] = player2.token;
	playBoard[4][4] = player2.token;
	memcpy(actualBoard, playBoard, sizeof (char) * BS * BS);
	currentPlayer = player2;
	/*	Main game loop, only exits once game is over*/
	while (gameLoop)
	{
		if (playerTurn == 2)
		{
			strcpy(gameMessage, "1");
			playerTurn = 1;
			currentPlayer = player1;
		}
		else
		{
			strcpy(gameMessage, "2");
			playerTurn = 2;
			currentPlayer = player2;
		}
		countScore(player1.token, actualBoard, &player1.score);
		countScore(player2.token, actualBoard, &player2.score);
		if ((player1.score + player2.score) == (BS*BS))
		{
			gameLoop = false;
			printw("\nGame over!\nPress any key to continue.\n");
			getch();
		}
		else
		{
			playLoop = true;
		}
		/*	Playing game loop, only exits once a player has set a token*/
		while (playLoop)
		{
			memcpy(playBoard, actualBoard, sizeof (char) * BS * BS);
			playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = 'X';
			drawBoard(playBoard, player1, player2, &gameMessage, &countFlip);
			/*	Player input*/
			playerInput = getch();
			if (playerInput == 'w' && currentPlayer.location[0] > 0)
			{
				currentPlayer.location[0]--;
			}
			else if (playerInput == 'a' && currentPlayer.location[1] > 0)
			{
				currentPlayer.location[1]--;
			}
			else if (playerInput == 'd' && currentPlayer.location[1] < 7)
			{
				currentPlayer.location[1]++;
			}
			else if (playerInput == 's' && currentPlayer.location[0] < 7)
			{
				currentPlayer.location[0]++;
			}
			else if (playerInput == 'c')
			{
				//Test if player can skip
				playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = ' ';
				returnOption = availableOptions(playBoard, currentPlayer.token);
				printw("\nScore:%i", returnOption.score);
				printw("\nAvailable:%i", returnOption.available);
				refresh();
				getch();
				if (returnOption.available > 0)
				{
					sprintf(gameMessage, "Player %s still has available moves!", currentPlayer.name);
					playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = currentPlayer.token;
				}
				else
					playLoop = false;
			}
			else if (playerInput == 'x')
			{
				/*	Test if user is setting token on top of another token*/
				if (actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == '@' || actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == 'O')
				{
					strcpy(gameMessage, "Cannot set token here!");
				}
				else
				{
					/*	Make changes to play board to test if the user made any flips*/
					playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = currentPlayer.token;
					countFlip = changeBoard(playBoard, currentPlayer.token, currentPlayer.location);
					/*	The user must have flips otherwise the move is considered invalid*/
					if (countFlip < 1)
					{
						strcpy(gameMessage, "Cannot set token here!");
						memcpy(playBoard, actualBoard, sizeof (char) * BS * BS);
					}
					else
					{
						playLoop = false;
						memcpy(actualBoard, playBoard, sizeof (char) * BS * BS);
					}
				}
			}
			else if (playerInput == 'Q')
			{
				/*	Force quits the game*/
				playLoop=false;
				gameLoop=false;
			}
			else
			{
				strcpy(gameMessage, "Invalid move!");
			}
			
		}
	}
	countScore(player1.token, actualBoard, &player1.score);
	countScore(player2.token, actualBoard, &player2.score);
	if (player1.score > player2.score)
	{
		return player1;
	}
	else if (player2.score > player1.score)
	{
		return player2;
	}
	else
	{
		/*	If players are tied, return 404*/
		currentPlayer.score = 404;
		return currentPlayer;
	}
}

int main()
{
	/*	Declaration*/
	/*	UserMessage*/
	char gameMessage[32];
	strcpy(gameMessage, "\nWelcome to BlackWhite!\n");
	/*	Main game loops*/
	bool gameLoop;
	/*	User Input*/
	char userOption;
	/*	Winner*/
	struct player winner;
	gameLoop = true;
	initscr();
	clrscr();
	while (gameLoop)
	{
		printw("Black White");
		printw("\n%s", gameMessage);
		showOptions();
		userOption = getch();
		if (userOption == 'p' || userOption == 'P')
		{
			/*	We call the game*/
			winner = playGame();
			if (winner.score == 404)
			{
				sprintf(gameMessage, "\nGame tied!\n");
			}
			else
			{
				sprintf(gameMessage, "\nPlayer %s wins with a score of %i!\n", winner.name, winner.score);
			}
		}
		else if (userOption == 'q' || userOption == 'Q')
		{
			printw("\nThanks for playing BlackWhite, bye!\nPress any key to return.");
			gameLoop = false;
			quit();
		}
		else
		{
			sprintf(gameMessage, "\n%c : Invalid option.\n", userOption);
		}
		if (gameLoop == true)
			clrscr();
	}
	return 0;/* returns 0*/
}
