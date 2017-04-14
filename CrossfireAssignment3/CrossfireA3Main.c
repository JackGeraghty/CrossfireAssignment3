//Crossfire Assignment 3 Main C file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CrossfireA3Head.h"

//Main Function
int  main()
{
	setbuf(stdout, NULL);

	//Set number of players and slots to zero
	Num_Players = 0;	//Stores the number of players
	bool do_once = false;	//Bool used to determine who is the winner
	int is_game_over = 0;	//Used to check if there is only one player left


	int BoardSize;
	int i;
	//Print a welcome
	printf("|| Welcome to Crossfire ||\n");


	//Get number of players
	getNumInRange(2, 6);

	//Get their info
	getPlayerInfo();

	//Set the remaining players
	Remaining_Players = Num_Players;

	//Get the size of the board
	BoardSize = BOARD_SIZE;	//BOARD_SIZE is a constant which can be changed in the header file

	//Create the board
	createBoard(BoardSize, &upLeft, &upRight, &downLeft, &downRight);

	//Set up slot types
	for (i = 0; i < Num_Players; i++)
	{
		players[i].Pos->Type = Board[players[i].Pos->row][players[i].Pos->column].Type;
	}

	//Do the turn function and check to see if the game is over while there is more than one player
	do
	{
		Turn(BoardSize);
		is_game_over = checkGameState();
	} while  (is_game_over == 0);


	//Determine who has won by checking the has_quit variable of each player
	for (i = 0; i < Num_Players; i++)
		{
			if (players[i].has_quit == 0 && do_once == false)
			{
				printf("Game Over, %s is the winner\n", players[0].Name);
				do_once = true;
			}
		}
	return 0;
}
