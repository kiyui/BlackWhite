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

void countScore(char token, char board[BS][BS], int *score)
{
	int loopXVar, loopYVar;
	int count = 0;
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			if (board[loopXVar][loopYVar] == token)
			{
				count++;
			}
		}
	}
	*score = count;
}

void drawBoard(char board[BS][BS], struct player player1, struct player player2, char (*gameMessage)[64])
{
	//Draw the board received each time using proper formatting
	int loopXVar, loopYVar;
	clrscr();
	
	if (!strcmp(*gameMessage, "1"))
	{
		printw("\nPlayer %s's turn!", player1.name);
	}
	else if (!strcmp(*gameMessage, "2"))
	{
		printw("\nPlayer %s's turn!", player2.name);
	}
	else
	{
		printw("\n%s", *gameMessage);
	}
	
	printw("\n%s\t :\t%i", player1.name, player1.score);
	printw("\n%s\t :\t%i\n", player2.name, player2.score);
	for (loopXVar = 0; loopXVar < BS; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < BS; loopYVar++)
		{
			printw("|%c", board[loopXVar][loopYVar]);
		}
		printw("|");
		printw("\n");
	}
	refresh();
}

void changeBoard(char board[BS][BS], char token, int location[2])
{
	int hasCount;
	int count = 0;
	int x, y;
	int xx, yy;
	//Right
	hasCount = 0;
	for (y = location[1]; y < 8; y++)
	{
		if (board[location[0]][y] == ' ')
		{
			break;
		}
		else if (board[location[0]][y] == token)
		{
			for (yy = location[1]; yy < y; yy++)
			{
				board[location[0]][yy] = token;
				count++;
				hasCount++;
			}
			
			if (hasCount > 0)
			{
				break;
			}
			//break; Unsure why this wouldn't work
		}
	}
	//Left
	hasCount = 0;
	for (y = location[1]; y > 0; y--)
	{
		if (board[location[0]][y] == ' ')
		{
			break;
		}
		else if (board[location[0]][y] == token)
		{
			for (yy = location[1]; yy > y; yy--)
			{
				board[location[0]][yy] = token;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				break;
			}
		}
	}
	//Down
	hasCount = 0;
	for (x = location[0]; x < 8; x++)
	{
		if (board[x][location[1]] == ' ')
		{
			break;
		}
		else if (board[x][location[1]] == token)
		{
			for (xx = location[0]; xx < x; xx++)
			{
				board[xx][location[1]] = token;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				break;
			}
		}
	}
	//Up
	hasCount = 0;
	for (x = location[0]; x > 0; x--)
	{
		if (board[x][location[1]] == ' ')
		{
			break;
		}
		else if (board[x][location[1]] == token)
		{
			for (xx = location[0]; xx > x; xx--)
			{
				board[xx][location[1]] = token;
				count++;
				hasCount++;
			}
			if (hasCount > 0)
			{
				break;
			}
		}
	}
}

struct player playGame()
{
	//Actual game function, returns winner
	//Boards
	char actualBoard[BS][BS];
	char playBoard[BS][BS];
	//Stats
	//Game message to display
	char gameMessage[64];
	//Player input for in-game
	char playerInput;
	//Sets currently playing player
	int playingNo = 1;
	//Get player scores
	int score[2][1];
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
	//Initial Display
	countScore(player1.token, playBoard, &player1.score);
	countScore(player2.token, playBoard, &player2.score);
	strcpy(gameMessage, "Welcome, players!");
	drawBoard(playBoard, player1, player2, &gameMessage);
	currentPlayer = player2;
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
		playLoop = true;
		countScore(player1.token, actualBoard, &player1.score);
		countScore(player2.token, actualBoard, &player2.score);
		while (playLoop)
		{
			memcpy(playBoard, actualBoard, sizeof playBoard);
			playBoard[currentPlayer.location[0]][currentPlayer.location[1]] = 'X';
			drawBoard(playBoard, player1, player2, &gameMessage);
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
				if (actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == '@' || actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] == 'O')
				{
					strcpy(gameMessage, "Cannot set token here!");
				}
				else
				{
					actualBoard[currentPlayer.location[0]][currentPlayer.location[1]] = currentPlayer.token;
					changeBoard(actualBoard, currentPlayer.token, currentPlayer.location);
					playLoop = false;
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
			else if (playerInput == 'Q')
			{
				playLoop=false;
				gameLoop=false;
			}
			else
			{
				strcpy(gameMessage, "Invalid move!");
			}
			
		}
	}
	return currentPlayer;
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
			sprintf(gameMessage, "\nPlayer %i wins!\n", winner.name);
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
	return 0;
}

