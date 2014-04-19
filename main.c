#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
void showOptions();			//Shows the main options
void drawBoard(char board[8][8]);	//Draws the updated board
int playGame();		 		//Play the game

int main()
{
	//Declaration
	//Main game loops
	bool gameLoop;
	//User Input
	char userOption;
	//Winner
	int winner;
	gameLoop = true;
	while (gameLoop == true)
	{
		printf("Black White");
		showOptions();
		scanf(" %c", &userOption);
		if (userOption == 'p' || userOption == 'P')
		{
			winner = playGame();
			printf("\nPlayer %i wins!", winner);
		}
		else if (userOption == 'q' || userOption == 'Q')
		{
			printf("\nGoodbye!");
			gameLoop = false;
		}
		else
		{
			printf("\n"%c": Invalid option.", userOption);
		}
	}
	return 0;
}

void showOptions()
{
	printf("\nOptions:");
	printf("\nP - Play Black White.");
	printf("\nQ - Quit program.");
}

int playGame(int boardSize)
{
	//User Names
	char player1[32], player2[32];
	//Board
	char playBoard[8][8];
	//Stats
	int winner;
	int turns = 0;
	//Loops
	int loopXVar, loopYVar;
	printf("\nPlease input player names:");
	printf("\nPlayer 1: ");
	scanf(" %s", &player1);
	printf("\nPlayer 2: ");
	scanf(" %s", &player2);
	//We create the initial board
	return winner;
}
