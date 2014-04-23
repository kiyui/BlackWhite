#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<curses.h>

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

void countScore(char token, char board[8][8], int *score)
{
	int loopXVar, loopYVar;
	int count = 0;
	for (loopXVar = 0; loopXVar < 8; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < 8; loopYVar++)
		{
			if (board[loopXVar][loopYVar] == token)
			{
				count++;
			}
		}
	}
	*score = count;
}

void drawBoard(char board[8][8], struct player player1, struct player player2, char (*gameMessage)[64])
{
	//Draw the board received each time using proper formatting
	int loopXVar, loopYVar;
	clrscr();
	
	if (!strcmp(*gameMessage, "1"))
	{
		printw("Player %s's turn!", player1.name);
	}
	else if (!strcmp(*gameMessage, "2"))
	{
		printw("\nPlayer %s's turn!", player2.name);
	}
	else
	{
		//printf("\n%s", *gameMessage);
	}
	
	printw("%s\t :\t%i\n", player1.name, player1.score);
	printw("%s\t :\t%i\n", player2.name, player2.score);
	for (loopXVar = 0; loopXVar < 8; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < 8; loopYVar++)
		{
			printw("|\t%c\t", board[loopXVar][loopYVar]);
		}
		printw("|");
		printw("\n");
	}
	refresh();
}

struct player playGame()
{
	//Actual game function, returns winner
	//Boards
	char actualBoard[8][8];
	char playBoard[8][8];
	//Stats
	//Game message to display
	char gameMessage[64];
	//Player input for in-game
	char playerInput;
	//Sets currently playing player
	int playingNo = 1;
	//Get player scores
	int score[2][1];
	//To return the winner
	struct player winner;
	//Loops
	bool gameLoop = true, playLoop = true;
	int loopXVar, loopYVar;
	//Players
	struct player player1;
	struct player player2;
	player1.token = '@';
        player2.token = 'O';
	player1.score = 0;
	player2.score = 0;
	printw("\nPlease input player names:");
	printw("\nPlayer 1 (@): ");
	refresh();
	getstr(player1.name);
	printw("Player 2 (O): ");
	refresh();
	getstr(player2.name);
	//Initial board
	for (loopXVar = 0; loopXVar < 8; loopXVar++)
		for (loopYVar = 0; loopYVar < 8; loopYVar++)
			playBoard[loopXVar][loopYVar] = ' ';
	playBoard[3][4] = player1.token;
	playBoard[4][3] = player1.token;
	playBoard[3][3] = player2.token;
	playBoard[4][4] = player2.token;
	memcpy(actualBoard, playBoard, sizeof actualBoard);
	drawBoard(playBoard, player1, player2, &gameMessage);
	getch();
	//Initial Display
	countScore(player1.token, playBoard, &player1.score);
	countScore(player2.token, playBoard, &player2.score);
	strcpy(gameMessage, "Welcome sucker");
	drawBoard(playBoard, player1, player2, &gameMessage);
	getch();
	/*
	while (gameLoop)
	{
		playLoop = true;
		while (playLoop)
		{
			for (loopXVar = 0; loopXVar < 8; loopXVar++)
			{
				for (loopYVar = 0; loopYVar < 8; loopYVar++)
				{
					if (playBoard[loopXVar][loopYVar] != '@' || playBoard[loopXVar][loopYVar] != 'O' )
					{
						playBoard[loopXVar][loopYVar] = 'X';
					}
				}
			}
			if (playerNo == 1)
			{
				strcpy()
			}
			drawBoard(playBoard, score, player1, player2, "")

		}	
	}*/
	winner = player1;
	return winner;
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

