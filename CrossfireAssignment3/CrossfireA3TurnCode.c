#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "CrossfireA3Head.h"

//C file to manage each turn
//Turn Function
//Handles what each player does while the game is still going
void Turn(int BoardSize)
{
	Remaining_Players = Num_Players;
	int is_game_over = 0;
	int player_choice;
	int i;

	//What does each player do?
	do
	{
		for (i = 0; i < Remaining_Players; i++)
		{
			player_choice = getInput(i);

			//Move
			if (player_choice == 1 && Remaining_Players  >= 1)
			{
				//printf("Entering move of turn\n");
				Move(i, BoardSize);
				printf("%s is now in position [%d, %d]\n", players[i].Name, players[i].row, players[i].column);
			}

			//Attack
			else if (player_choice == 2 && Remaining_Players  >= 1)
			{
				Attack(i);
			}

			//Quit
			else if (player_choice == 3 )
			{
				removePlayer(i);
				i--;	//Move back i to adjust to their being less players
			}

			//Checks to see if there is only one left in the game
			if (Remaining_Players <= 1)
			{
				is_game_over = 1;
			}

			printf("Remaining Players = %d\n", Remaining_Players);
			printf("End of %s's turn\n", players[i].Name);
		}
	} while (is_game_over == 0);

	printf("Game Over, %s is the winner\n", players[i].Name);
}

//Function to control the movement of each player
void Move(int PlayerID, int BoardSize)
{
	bool is_valid = false;
	char input[MAX_SIZE_INPUT];

	//printf("Entered move function\n");

	if (players[PlayerID].row == 0 &&(players[PlayerID].column != 0 || players[PlayerID].column != BoardSize - 1))
	{
		printf("Player is in to row\n");
	}
	//Player is in a corner
	else if ((players[PlayerID].row == 0 && players[PlayerID].column == 0) || (players[PlayerID].row != 0 && players[PlayerID].column == BoardSize -1)
			|| (players[PlayerID].row == BoardSize - 1 && players[PlayerID].column == 0) || (players[PlayerID].row == BoardSize - 1 && players[PlayerID].column != BoardSize - 1))
	{
		//Player is in the top left
		if (players[PlayerID].row == 0 && players[PlayerID].column == 0)
		{
			do
			{
				printf("%s in in the top left corner of the board. Should they move 'right' or 'down'?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				//Player wants to move right
				if (check_input(input, "right") == 0)
				{
					printf("Moving Right\n");
					players[PlayerID].column++;
					is_valid = true;
				}

				//Player wants to move down
				else if(check_input(input, "down") == 0)
				{
					printf("Moving Down\n");
					players[PlayerID].row++;
					is_valid = true;
				}

				//Unknown Input
				else
				{
					printf("Enter a valid input\n");
				}

			} while (is_valid == false);
		}

		//Player is in bottom left
		else if (players[PlayerID].row == BoardSize - 1 && players[PlayerID].column == 0)
		{
			do
			{
				printf("%s in in the bottom left corner of the board. Should they move 'right' or 'up'?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				//Player wants to move right
				if (check_input(input, "right") == 0)
				{
					printf("Moving Right\n");
					players[PlayerID].column++;
					is_valid = true;
				}

				//Player wants to move up
				else if (check_input(input , "up") == 0)
				{
					printf("Moving Up\n");
					players[PlayerID].row--;
					is_valid = true;
				}

				//Unknown Input
				else
				{
					printf("Enter a valid input\n");
				}

			} while (is_valid == false);
		}

		//Player is in top right
		else if (players[PlayerID].row == 0 && players[PlayerID].column == BoardSize - 1)
		{
			do
			{
				printf("%s is in the top right corner of the board. Should they move 'left' or 'down'?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				//Player wants to move left
				if (check_input(input, "left") == 0)
				{
					printf("Moving Left\n");
					players[PlayerID].column--;
					is_valid = true;
				}

				//Player wants to move down
				else if(check_input(input, "down") == 0)
				{
					printf("Moving Down\n");
					players[PlayerID].row ++;
					is_valid = true;
				}

				//Unknown Input
				else
				{
					printf("Enter a valid input\n");
				}

			} while (is_valid == false);
		}

		//Player is in bottom right
		else if (players[PlayerID].row == BoardSize -1 && players[PlayerID]. column == BoardSize -1)
		{
			do
			{
				printf("%s is in the bottom right corner of the board. Should they move 'left' or 'up'?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "left") == 0)
				{
					printf("Moving Left\n");
					players[PlayerID].column--;
					is_valid = true;
				}

				else if (check_input(input, "down") == 0)
				{
					printf("Moving Up\n");
					players[PlayerID]. row--;
					is_valid = true;
				}

				else
				{
					printf("Enter a valid input\n");
				}
			} while (is_valid == false);
		}

	}

	else if (players[PlayerID].row == 0 &&(players[PlayerID].column != 0 || players[PlayerID].column != BoardSize - 1))
	{
		printf("In top row but not corners\n");

	}

	else if (players[PlayerID].row == BoardSize - 1 && (players[PlayerID].column != 0 || players[PlayerID].column != BoardSize-1))
	{
		printf("In bottom row but not corners\n");
	}

	else if (players[PlayerID].column == 0 && (players[PlayerID].row != 0 || players[PlayerID].row != BoardSize - 1))
	{
		printf("In left column but not corners\n");
	}

	else if (players[PlayerID].column == BoardSize -1  && (players[PlayerID].row != 0 || players[PlayerID].row != BoardSize - 1))
	{
		printf("In right column\n");
	}

	//Player is somewhere else on the board
	else
	{
		printf("Somewhere else\n");
		do
		{
			is_valid = false;
			printf("Should %s move 'left', 'right', 'up' or 'down'?\n", players[PlayerID].Name);
			fgets(input, sizeof(input), stdin);

			if (check_input(input, "left") == 0)
			{
				printf("Moving Left\n");
				players[PlayerID].column--;
				is_valid = true;
			}

			else if (check_input(input, "right") == 0)
			{
				printf("Moving Right\n");
				players[PlayerID].column++;
				is_valid = true;
			}

			else if (check_input(input, "up") == 0)
			{
				printf("Moving Up\n");
				players[PlayerID].row--;
				is_valid = true;
			}

			else if (check_input(input, "down") == 0)
			{
				printf("Moving Down\n");
				players[PlayerID].row++;
				is_valid = true;
			}

			else
			{
				printf("Enter a valid input\n");
			}
		} while(is_valid == false);
	}
}
//Function to control when a player wants to attack
void Attack(int PlayerID)
{

}

//Function to check the input of the user to see what they want to do
int check_input(char *StringIn, char *Command)
{
	int output;
	int i;

	//Get rid of any newline characters and replace them with NULL terminators
	for (i = 0; i < strlen(StringIn); i++)
	{
		if (StringIn[i] == '\n')
		{
			StringIn[i] = '\0';
		}
	}
	output = strcmp(strlwr(StringIn), Command);

	return output;
}

//Function to get input  from the player to see what they want to do each turn
int getInput(int PlayerID)
{
	bool is_valid;
	char input[MAX_SIZE_INPUT];
	int output;

	do
	{
		is_valid = false;
		printf("Would %s like to 'move', 'attack' or 'quit'?\n", players[PlayerID].Name);
		fgets(input, sizeof(input), stdin);

		//Player wants to move
		if (check_input(input, "move") == 0)
		{
			printf("%s is Going to Move\n", players[PlayerID].Name);
			output = 1;
			is_valid = true;
			//printf("Returning 1\n");
		}

		else if (check_input(input, "attack") == 0)
		{
			printf("%s is Going to Attack\n", players[PlayerID].Name);
			output = 2;
			is_valid = true;
		}

		else if (check_input(input, "quit") == 0)
		{
			printf("%s is Quitting the Game :(\n", players[PlayerID].Name);
			output = 3;
			is_valid = true;
		}

		else
		{
			printf("Please Enter a Valid Input\n");
		}
	} while (is_valid == false);

	return output;
}

//Function to remove a player from the game if they quit or lose all their health
void removePlayer(int PlayerID)
{
	int i;
	struct Player deadPlayer[1];

	deadPlayer[0] = players[PlayerID];

	for (i = PlayerID + 1; i < Remaining_Players; i++)
	{
		players[i - 1] = players[i];
	}

	players[i] = deadPlayer[0];
	Remaining_Players--;
}

