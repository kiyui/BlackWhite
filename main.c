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

void drawBoard(char userBoard[BS][BS], struct player player1, struct player player2, char (*gameMessage)[64])
{
	//Draw the board received each time using proper formatting
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
	//Prints player stats
	printw("\n%s\t :\t%i", player1.name, player1.score);
	printw("\n%s\t :\t%i\n", player2.name, player2.score);
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			printw("|%c", userBoard[loopXVar][loopYVar]);
		}
		printw("|");
		printw("\n");
	}
	refresh();
}

int changeBoard(char actualBoard[BS][BS], char playerToken, int location[2])
{
	char userBoard[BS][BS];
	memcpy(userBoard, actualBoard, sizeof userBoard);
	//Determines if a loop has already made a flip
	int hasCount;
	//Flips made
	int count = 0;
	//Determines limit
	int x, y;
	//Loop values
	int xx, yy;
	//Right
	hasCount = 0;
	for (y = location[1]; y < 8; y++)
	{
		if (userBoard[location[0]][y] == ' ')
		{
			break;
		}
		else if (userBoard[location[0]][y] == playerToken)
		{
			for (yy = location[1]; yy < y; yy++)
			{
				userBoard[location[0]][yy] = playerToken;
				count++;
				hasCount++;
			}
			
			if (hasCount > 0)
			{
				count--;
				break;
			}
			//break; Unsure why this wouldn't work
		}
	}
	//Left
	hasCount = 0;
	for (y = location[1]; y > 0; y--)
	{
		if (userBoard[location[0]][y] == ' ')
		{
			break;
		}
		else if (userBoard[location[0]][y] == playerToken)
		{
			for (yy = location[1]; yy > y; yy--)
			{
				userBoard[location[0]][yy] = playerToken;
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
	//Down
	hasCount = 0;
	for (x = location[0]; x < 8; x++)
	{
		if (userBoard[x][location[1]] == ' ')
		{
			break;
		}
		else if (userBoard[x][location[1]] == playerToken)
		{
			for (xx = location[0]; xx < x; xx++)
			{
				userBoard[xx][location[1]] = playerToken;
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
	//Up
	hasCount = 0;
	for (x = location[0]; x > 0; x--)
	{
		if (userBoard[x][location[1]] == ' ')
		{
			break;
		}
		else if (userBoard[x][location[1]] == playerToken)
		{
			for (xx = location[0]; xx > x; xx--)
			{
				userBoard[xx][location[1]] = playerToken;
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
	//We only make changes to the original board if there actually were changes made
	if (count > 0)
	{
		for (x = 0; x < BS; x++)
			for (y = 0; y < BS; y++)
				actualBoard[x][y] = userBoard[x][y];
	}
	return count;
}

struct player playGame()
{
	//Actual game function, returns winner
	//Boards
	char actualBoard[BS][BS];
	char playBoard[BS][BS];
	//Game message to display
	char gameMessage[64];
	//Player input for in-game
	char playerInput;
	//Sets currently playing player
	int playingNo = 1;
	//Determines if a player can set the character
	int countFlip;
	//Loops
	bool gameLoop = true, playLoop = true;
	int loopXVar, loopYVar;
	//Players
	int playerTurn = 2;
	struct player player1;
	struct player player2;
	struct player currentPlayer;
	player1.token = '@';
    player2.token = 'O';
	player1.score = 0;
	player2.score = 0;
	player1.location[0] = 0;
	player1.location[1] = 0;
	player2.location[0] = 0;
	player2.location[1] = 0;
	printw("\nPlease input player names:");
	printw("\nPlayer 1 (@): ");
	refresh();
	getstr(player1.name);
	printw("Player 2 (O): ");
	refresh();
	getstr(player2.name);
	//Initial board
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
			playBoard[loopXVar][loopYVar] = ' ';
	playBoard[3][4] = player1.token;
	playBoard[4][3] = player1.token;
	playBoard[3][3] = player2.token;
	playBoard[4][4] = player2.token;
	memcpy(actualBoard, playBoard, sizeof actualBoard);
	currentPlayer = player2;
	while (gameLoop) //Main game loop, only exits once game is over
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
		}
		else
		{
			playLoop = true;
		}
		while (playLoop) //Playing game loop, only exits once a player has set a token
		{
			memcpy(playBoard, actualBoard, sizeof playBoard);
			playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = 'X';
			drawBoard(playBoard, player1, player2, &gameMessage);
			//Player input
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
			else if (playerInput == 'x')
			{
				//Test if user is setting token on top of another token
				if (actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == '@' || actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == 'O')
				{
					strcpy(gameMessage, "Cannot set token here!");
				}
				else
				{
					//Make changes to play board to test if the user made any flips
					playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = currentPlayer.token;
					countFlip = changeBoard(playBoard, currentPlayer.token, currentPlayer.location);
					//The user must have flips otherwise the move is considered invalid
					if (countFlip < 1)
					{
						strcpy(gameMessage, "Cannot set token here!");
						memcpy(playBoard, actualBoard, sizeof playBoard);
					}
					else
					{
						playLoop = false;
						memcpy(actualBoard, playBoard, sizeof actualBoard);
						//After the user makes a flip, the game changes players
						switch (playerTurn)
						{
							case 1:
								player1 = currentPlayer;
								break;
							case 2:
								player2 = currentPlayer;
								break;
							default:
								break;
						}
					}
				}
			}
			else if (playerInput == 'Q')
			{
				//Force quits the game
				playLoop=false;
				gameLoop=false;
			}
			else
			{
				strcpy(gameMessage, "Invalid move!");
			}
			
		}
	}
	if (player1.score > player2.score)
	{
		return player1;
	}
	else if (player2.score < player1.score)
	{
		return player2;
	}
	else
	{
		//If players are tied, return 404
		currentPlayer.score = 404;
		return currentPlayer;
	}
}

int main()
{
	//Declaration
	//UserMessage
	char gameMessage[32];
	strcpy(gameMessage, "\nWelcome to BlackWhite!\n");
	//Main game loops
	bool gameLoop;
	//User Input
	char userOption;
	//Winner
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
			//We call the game
			winner = playGame();
			if (winner.score == 404)
			{
				sprintf(gameMessage, "\nGame tied!");
			}
			else
			{
				sprintf(gameMessage, "\nPlayer %i wins!\n", winner.name);
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
	return 0; //returns 0
}

