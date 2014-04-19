#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<curses.h>


void clrscr();
void quit();
void showOptions();//-----------------------------------------------------------------------//Shows the main options
void drawBoard(char board[8][8], int score[2][1], char player1[32], char player2[32], char gameMessage[64]);//----//Draws the updated board
int playGame();//---------------------------------------------------------------------------//Play the game
struct playerScores
{
	int player1;
	int player2;
};
struct playerScores countScore(char board[8][8]);//------------------------------------------//Returns player scores

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
	int winner;
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
			sprintf(gameMessage, "\nPlayer %i wins!\n", winner);
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
			system("clear");
	}
	return 0;
}

void showOptions()
{
	printw("\nOptions:");
	printw("\nP - Play Black White.");
	printw("\nQ - Quit program.");
	printw("\nSelection: ");
}

void drawBoard(char board[8][8], int score[2][1], char player1[32], char player2[32], char gameMessage[64])
{
	//Draw the board received each time using proper formatting
	int loopXVar, loopYVar;
	clrscr();
	if (!strcmp(gameMessage, "1"))
	{
		printw("Player %s's turn!", player1);
	}
	else if (!strcmp(gameMessage, "2"))
	{
		printw("\nPlayer %s's turn!", player2);
	}
	else
	{
		printf("\n%s", gameMessage);
	}
	printw("%s\t :%i\n", player1, score[0][0]);
	printw("%s\t :%i\n", player2, score[1][0]);
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

int playGame(int boardSize)
{
	//Actual game function, returns winner
	//User Names
	char player1[32], player2[32];
	//Board
	char playBoard[8][8];
	//Stats
	struct playerScores getScores;
	char gameMessage[64];
	int score[2][1];
	int winner = 0;
	char xyz;
	//Loops
	bool gameLoop = true;
	int loopXVar, loopYVar;
	printw("\nPlease input player names:");
	printw("\nPlayer 1 (O): ");
	refresh();
	getstr(player1);
	printw("Player 2 (@): ");
	refresh();
	getstr(player2);
	//Initial board
	for (loopXVar = 0; loopXVar < 8; loopXVar++)
		for (loopYVar = 0; loopYVar < 8; loopYVar++)
			playBoard[loopXVar][loopYVar] = '-';
	playBoard[3][3] = 'O';
	playBoard[4][4] = 'O';
	playBoard[3][4] = '@';
	playBoard[4][3] = '@';
	//Initial Display
	getScores = countScore(playBoard);
	score[0][0] = getScores.player1;
	score[1][0] = getScores.player2;
	drawBoard(playBoard, score, player1, player2, "1");
	getch();
	while (gameLoop)
	{

	}
	return winner;
}

struct playerScores countScore(char board[8][8])
{
	//Counts the number of pieces placed by each player
	//@ is for black
	//O is for white
	struct playerScores returnScores;
	int loopXVar, loopYVar;
	int countW = 0, countB = 0;
	for (loopXVar = 0; loopXVar < 8; loopXVar++)
	{
		for (loopYVar = 0; loopYVar < 8; loopYVar++)
		{
			switch (board[loopXVar][loopYVar])
			{
				case '@':
					countB++;
					break;
				case 'O':
					countW++;
					break;
				default:
					break;
			}
		}
	}
	returnScores.player1 = countW;
	returnScores.player2 = countB;
	return returnScores;
};

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
