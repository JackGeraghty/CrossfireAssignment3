//C file for setting up the Board and it's elements

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CrossfireA3Head.h"

//Function to create the board and assign all the adjacent slots for each elements. Also assign the slot types to each slot and player
void createBoard(int Size, struct Slot **upLeft, struct Slot **upRight, struct Slot **downLeft, struct Slot **downRight)
{
	int i, j, k;

	//Assign the Board memory based on the BOARD_SIZE
	Board = malloc(Size * sizeof(struct Slot *));

	for (i = 0 ; i < Size ; i++)
	{
		//Allocates memory the space for the slots in each row of the Board
		Board[i] = malloc(Size * sizeof(struct Slot));

		//For each slot it sets up the row and column number
		for(j = 0 ; j < Size ; j++)
		{
			Board[i][j].row = i;
			Board[i][j].column = j;

		}
	}

	//Setup adjacent slots for those that have adjacent slots on four sides
	for (i = 1 ; i < Size - 1 ; i++)
	{
		for(j = 1 ; j < Size - 1 ; j++)
		{
			Board[i][j].up = &Board[i-1][j];
			Board[i][j].right = &Board[i][j+1];
			Board[i][j].down = &Board[i+1][j];
			Board[i][j].left = &Board[i][j-1];
		}
	}

	//Setup adjacent slots for those that have adjacent slots on three sides and are the top and bottom rows
	for(int j = 1; j < Size - 1 ; j++)
	{


		//Have no adjacent slot in the up direction
		Board[0][j].right = &Board[0][j+1];
		Board[0][j].left = &Board[0][j-1];
		Board[0][j].down = &Board[1][j];
		Board[0][j].up = NULL;

		//Have no adjacent slot in the down direction
		Board[Size - 1][j].right = &Board[Size - 1][j+1];
		Board[Size -1][j].left = &Board[Size - 1][j-1];
		Board[Size - 1][j].up = &Board[Size - 2][j];
		Board[Size - 1][j].down = NULL;
	}

	//Setup adjacent slots for those that have adjacent slots on three sides and are the left and right columns
	for(i = 1; i < Size - 1 ; i++)
	{

		//Have no adjacent slot in the left direction
		Board[i][0].right = &Board[i][1];
		Board[i][0].up = &Board[i-1][0];
		Board[i][0].down = &Board[i+1][0];
		Board[i][0].left = NULL;

		//Have no adjacent slot in the right direction
		Board[i][Size-1].left = &Board[i][Size-2];
		Board[i][Size -1].up = &Board[i -1][Size-1];
		Board[i][Size -1].down = &Board[i+1][Size - 1];
		Board[i][Size -1].right = NULL;
	}


	//Setup slots that only have two adjacent slots, i.e. the corners

	//Top left corner
	Board[0][0].right = &Board[0][1];
	Board[0][0].down = &Board[1][0];
	Board[0][0].up = NULL;
	Board[0][0].left = NULL;

	//Top right corner
	Board[0][Size-1].left = &Board[0][Size-2];
	Board[0][Size -1].down = &Board[1][Size -1];
	Board[0][Size-1].right = NULL;
	Board[0][Size -1].up = NULL;

	//Bottom left corner
	Board[Size -1][0].right = &Board[Size -1][1];
	Board[Size -1][0].up = &Board[Size -2][0];
	Board[Size -1][0].left = NULL;
	Board[Size -1][0].down = NULL;

	//Bottom right corner
	Board[Size - 1][Size-1].up = &Board[Size-2][Size-1];
	Board[Size - 1][Size -1].left = &Board[Size -1][Size -2];
	Board[Size - 1][Size-1].right = NULL;
	Board[Size - 1][Size -1].down = NULL;

	//assigns a pointer to slot at position (0, 0)
	*upLeft = &Board[0][0];
	//assigns pointer of pointer to slot at position (0, Size -1)
	*upRight = &Board[0][Size -1];
	//assigns pointer of pointer to slot at position ( Size -1,)
	*downLeft = &Board[Size -1][0];
	//assigns pointer of pointer to slot at position (Size -1, Size -1)
	*downRight = &Board[Size -1][Size -1];

	//Print the board
	for (i = 0; i < Size;i++)
	{
		for (j = 0; j < Size; j++)
		{
			printf("[%d][%d] ", Board[i][j].row,Board[i][j].column);
			if (j == Size - 1)
			{
				printf("\n");
			}
		}

	}

	//Assign each player a slot on the board randomly
	fillPlayers(Size);


	srand(time(NULL));

	//Randomly assign each position a type and store them in a global array
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			k = rand() % 3;
			Board[i][j].Type = k;
		}
	}

	//Assign each player the slot type for their position
	for (i = 0; i < Num_Players; i++)
	{
		players[i].Pos->Type = Board[players[i].Pos->row][players[i].Pos->column].Type;
	}

}

//Function to randomly assign a location to each player
void fillPlayers(int Size)
{
	int i;

	//Assign them a random position
	for (i = 0; i < Num_Players; i++)
	{
		players[i].Pos = &Board[rand() % Size][rand() % Size];
	}

	//Print where each player is
	for (i = 0; i < Num_Players; i++)
	{
		printf("%s is in position [%d, %d]\n", players[i].Name, players[i].Pos->row , players[i].Pos->column);
	}
}
