//Crossfire Assignment 3 Main C file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CrossfireA3Head.h"

int getBoardSize();

//Main Function
int  main()
{
	setbuf(stdout, NULL);

	//Set number of players and slots to zero
	Num_Players = 0;
	Num_Slots = 0;

	struct Slot *upLeft;
	struct Slot *upRight;
	struct Slot *downRight;
	struct Slot *downLeft;
	int BoardSize;
	int i;
	//Print a welcome
	printf("|| Welcome to Crossfire ||\n");


	//Get number of players
	getNumInRange(2, 6);

	//Get their info
	getPlayerInfo();

	//Get the size of the board
	BoardSize = 7;

	//Create the board
	createBoard(BoardSize, &upLeft, &upRight, &downLeft, &downRight);

	//Fill each player into a random position on the board
	fillPlayers(BoardSize);

	//Set up slot types
	for (i = 0; i < Num_Players; i++)
	{
		players[i].slot_type = slot_Types[players[i].row][players[i].column];
		//printf("%d slot type = %d\n", i, players[i].slot_type);
	}


	Turn(BoardSize);

	return 0;
}

//Function to get the size of the board from user. Has precautions to avoid bad input
int getBoardSize()
{
	int i;
	bool is_valid;
	bool is_num;
	char input[MAX_SIZE_INPUT];
	int output;

	do
	{
		is_valid = true;
		is_num = false;
		printf("Enter the size of the board(The board is square): \n");
		fgets(input, sizeof(input), stdin);

		//Check to see if its a number
		for (i = 0; i < strlen(input);i++)
		{
			if (input[i] < 48 || input[i] > 57)
			{
				break;
				is_valid = false;
			}
		}

		if (is_valid == true)
		{
			if ((atoi(input) <= 100 && atoi(input) > 1))
			{
				is_num = true;
				output = atoi(input);

			}
		}

	} while (is_valid == false || is_num == false);

	return output;
}
