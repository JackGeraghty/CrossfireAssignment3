#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CrossfireA3Head.h"

//C file for setting up the board and it's elements

void createBoard(int Size, struct Slot **upLeft, struct Slot **upRight, struct Slot **downLeft, struct Slot **downRight)
{
	srand(time(NULL));
	struct Slot **Board = malloc(Size * sizeof(struct Slot *));
	int i;
	int j;
	int k;

	//Set up the board as a pointer of pointer to slots
	for (int i = 0; i < Size; i++)
	{
		Board[i] = malloc(Size * sizeof(struct Slot));

		for  (j = 0; j < Size; j++)
		{
			Board[i][j].row = i;
			Board[i][j].column = j;
		}
	}

	for (i = 0; i < Size - 1; i++)
	{
		//Set up slots that don't have an element adjacent on the left
		Board[i][0].right = &Board[i][1];
		Board[i][0].up = &Board[i][0];
		Board[i][0].down = &Board[i + 1][0];

		//Set up slots that don't have an element adjacent on the right
		Board[i][Size - 1].left = &Board[Size ][Size - 2];
		Board[i][Size - 1].up = &Board[i - 1][Size - 1];
		Board[i][Size - 1].down = &Board[i + 1][Size - 1];

	}

	//Set up adjacent slots for (0,0)
	Board[0][0].right = &Board[0][1];
	Board[0][0].down = &Board[1][0];

	//Set up adjacent slots for (0, Size -1)
	Board[0][Size - 1].left = &Board[0][Size - 2];
	Board[0][Size - 1].down = &Board[1][Size - 1];

	//Adjacent slots for (Size-1, 0)
	Board[Size - 1][0].right = &Board[Size - 1][1];
	Board[Size - 1][0].up = &Board[Size - 2][0];

	//Adjacent slots for (Size - 1, Size -1)
	Board[Size - 1][Size - 1].left = &Board[Size - 2][Size - 1];
	Board[Size - 1][Size - 1].left = &Board[Size - 1][Size - 2];

	*upLeft = &Board[0][0];
	*upRight = &Board[0][Size - 1];
	*downLeft = &Board[Size - 1][0];
	*downRight = &Board[Size - 1][Size - 1];

	//Test Print the board
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

	//Randomly assign each position a type and store them in a global array
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			k = rand() % 3;
			slot_Types[i][j] = k;
		}
	}

	//Test print each slot type
/*
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			if (slot_Types[i][j] == 0)
			{
				printf("[Level Ground] ");
			}

			else if (slot_Types[i][j] == 1)
			{
				printf("[Hill] ");
			}

			else if (slot_Types[i][j] == 2)
			{
				printf("[City] ");
			}
			if (j == Size-1)
			{
				printf("\n");
			}
		}
	}
*/
}


//Function to randomly assign a location to each player
void fillPlayers(int Size)
{
	srand(time(NULL));
	int j;

	//Give each player a random row value
	for (int i = 0; i < Num_Players; i++)
	{
		j = rand() % Size;
		players[i].row = j;

	}

	//Give each player a random column value
	for (int i = 0; i < Num_Players; i++)
	{
		j = rand() % Size;
		players[i].column = j;
	}

	//Print the players locations
	for (int i = 0; i < Num_Players; i++)
	{
		printf("Player %d is in location [%d, %d].\n", i + 1, players[i].row , players[i].column );
	}

}
