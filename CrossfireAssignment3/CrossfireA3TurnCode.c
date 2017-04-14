#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "CrossfireA3Head.h"

//Global variable to store which players turn it currently is
int PlayerID;

//Function to check if a player has died at the start of every turn, check if the game is over, as well as get what each player to do using the Turn_Choice function.
void Turn(int BoardSize)
{
	int j;

	for (PlayerID = 0; PlayerID < Remaining_Players; PlayerID++)
	{
		//Check to see if someone has died and if so remove them
		for (j = 0; j < Remaining_Players; j++)
		{

			if (players[j].Health <= 0)
			{
				printf("%s has lost all their health.\n", players[j].Name);	//Tell the user a player has died
				removePlayer(j);
			}

		}

		//Check to see if there is only one player left
		if (Remaining_Players == 1)
		{
			//Game Over
			break;	//Exit out of the for loop and return to the main function
		}

		//Get what the user wants to do for this players turn
		Turn_Choice(PlayerID);
	}
}

//Function to control what each player does every turn
void Turn_Choice()
{
	int player_choice;	//Used to see what each player wants to do

	//Print info about the current player
	printf("\n//////////\t\t%s\t\t//////////\n", players[PlayerID].Name);
	printf("Player: %s, Health: %d\n", players[PlayerID].Name, players[PlayerID].Health);
	printf("Location: (%d, %d)\n", players[PlayerID].Pos->row, players[PlayerID].Pos->column);

	//Get player choice
	player_choice = getInput(PlayerID);

	//Player wants to quit
	if (player_choice == 3)
	{
		removePlayer(PlayerID); //Remove the current player

	}

	//Player wants to move
	else if (player_choice == 1)
	{
		//print where the player is currently
		printf("%s, (%d, %d) ", players[PlayerID].Name, players[PlayerID].Pos->row, players[PlayerID].Pos->column);
		if (players[PlayerID].Pos->Type == 0)
		{
			printf("[Level Ground]\n");
		}

		else if (players[PlayerID].Pos->Type == 1)
		{
			printf("[Hill]\n");
		}

		else if (players[PlayerID].Pos->Type == 2)
		{
			printf("[City]\n");
		}

		//Run the move function
		Move(BOARD_SIZE);

		//print where they are at the end of move
		printf("%s, (%d, %d) ", players[PlayerID].Name, players[PlayerID].Pos->row, players[PlayerID].Pos->column);
		if (players[PlayerID].Pos->Type == 0)
		{
			printf("[Level Ground]\n");
		}

		else if (players[PlayerID].Pos->Type == 1)
		{
			printf("[Hill]\n");
		}

		else if (players[PlayerID].Pos->Type == 2)
		{
			printf("[City]\n");
		}

		//Modify their values based on what type of slot they land on
		modValues(PlayerID);
	}

	//Player is attacking
	else if (player_choice == 2)
	{
		Attack(PlayerID);	//Run the attack function

	}
	printf("\n//////////\t\t\t\t//////////\n");
}

//Function to control the movement of each player
void Move(int BoardSize)
{
	bool is_valid = false;
	char input[MAX_SIZE_INPUT];


	//Player is in one of the four corners
	if (((players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column == 0))
			||((players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column == BoardSize - 1))
			||((players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column == 0))
			||((players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column == BoardSize - 1)))
	{
		//Player is in top left
		if ((players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column == 0))
		{
			do
			{
				printf("%s is in the top left corner of the board. Should they move 'right', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "right") == 0)
				{
					//Player wants to move right
					is_valid = moveDir( 3);
				}

				else if (check_input(input, "down") == 0)
				{
					//Player wants to move down
					is_valid = moveDir( 1);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}

			} while (is_valid == false);

		}

		//Player is in the top right corner of the board
		else if ((players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column == BoardSize - 1))
		{
			do
			{
				printf("%s is in the top right corner of the board. Should they move 'left', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "left") == 0)
				{
					//Move left
					is_valid = moveDir( 4);
				}

				else if (check_input(input, "down") == 0)
				{
					//Move Down
					is_valid = moveDir( 1);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}
			} while (is_valid == false);
		}

		//Player is in bottom left corner
		else if ((players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column == 0))
		{
			do
			{
				printf("%s is in the bottom left corner. Should they move 'right', 'up', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "right") == 0)
				{
					//Move Right
					is_valid = moveDir( 3);
				}

				else if (check_input(input, "up") == 0)
				{
					//Move up
					is_valid = moveDir( 2);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}
			} while (is_valid == false);
		}

		//Player is in bottom right corner
		else if ((players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column == BoardSize - 1))
		{
			do
			{
				printf("%s is in the bottom right corner. Should they move 'left', 'up', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if(check_input(input, "left") == 0)
				{
					//Move left
					is_valid = moveDir( 4);
				}

				else if (check_input(input, "up") == 0)
				{
					//Move up
					is_valid = moveDir( 2);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}
			} while (is_valid == false);
		}
	}

	//Player is on the edges of the board but not the corners
	else if (( (players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column != 0 || players[PlayerID].Pos->column != BoardSize - 1) )
			||( (players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column != 0 || players[PlayerID].Pos->column != BoardSize - 1) )
			||( (players[PlayerID].Pos->column == 0) && (players[PlayerID].Pos->row != 0 || players[PlayerID].Pos->row != BoardSize - 1) )
			||( (players[PlayerID].Pos->column == BoardSize - 1) && (players[PlayerID].Pos->row != 0 || players[PlayerID].Pos->row != BoardSize - 1) )	)
	{
		//Player is in row one
		if (( (players[PlayerID].Pos->row == 0) && (players[PlayerID].Pos->column != 0 || players[PlayerID].Pos->column != BoardSize - 1) ) )
		{
			do
			{
				printf("%s is in the top row but not in one of the corners. Should they move 'left' , 'right', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "left") == 0)
				{
					//Move left
					is_valid = moveDir( 4);
				}

				else if (check_input(input, "right") == 0)
				{
					//Move right
					is_valid = moveDir( 3);
				}

				else if (check_input(input, "down") == 0)
				{
					//Move down
					is_valid = moveDir( 1);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}

			} while (is_valid == false);
		}

		//Player is in last row
		else if (( (players[PlayerID].Pos->row == BoardSize - 1) && (players[PlayerID].Pos->column != 0 || players[PlayerID].Pos->column != BoardSize - 1) ))
		{
			do
			{
				printf("%s is in the bottom row but not in one of the corners. Should they move 'left', 'right', 'up', or 'back' to return to the turn menu ?\n",players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "left") == 0)
				{
					//Move left
					is_valid = moveDir( 4);
				}

				else if (check_input(input, "right") == 0)
				{
					//Move right
					is_valid = moveDir( 3);
				}

				else if (check_input(input, "up") == 0)
				{
					//Move up
					is_valid = moveDir( 2);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}
			} while (is_valid == false);
		}

		//Player is in left column
		else if (( (players[PlayerID].Pos->column == 0) && (players[PlayerID].Pos->row != 0 || players[PlayerID].Pos->row != BoardSize - 1) ))
		{
			do
			{
				printf("%s is in the left most column but not in one of the corners. Should they move 'right', 'up', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if (check_input(input, "right") == 0)
				{
					//Moving right
					is_valid = moveDir( 3);
				}

				else if (check_input(input, "up") == 0)
				{
					//Moving up
					is_valid = moveDir( 2);
				}

				else if (check_input(input, "down") == 0)
				{
					//Moving down
					is_valid = moveDir( 1);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}
			} while (is_valid == false);
		}

		//Player is in the right most column
		else if(( (players[PlayerID].Pos->column == BoardSize - 1) && (players[PlayerID].Pos->row != 0 || players[PlayerID].Pos->row != BoardSize - 1) ))
		{
			do
			{
				printf("%s is in the right most column but not in one of the corners. Should they move 'left', 'up', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
				fgets(input, sizeof(input), stdin);

				if ((check_input(input, "left") == 0))
				{
					//Moving left
					is_valid = moveDir( 4);

				}

				else if ((check_input(input, "up") == 0))
				{
					//Moving up
					is_valid = moveDir( 2);
				}

				else if ((check_input(input, "down") == 0))
				{
					//Moving down
					is_valid = moveDir( 1);
				}

				else if (check_input(input, "back") == 0)
				{
					Turn_Choice(PlayerID);
					is_valid = true;
				}

				else
				{
					printf("Please enter a valid input.\n");
				}

			} while (is_valid == false);
		}
	}

	//Player is in the middle area of the board
	else if ((players[PlayerID].Pos->row != 0)
			&& (players[PlayerID].Pos->row != BoardSize - 1)
			&& (players[PlayerID].Pos->column != 0)
			&& (players[PlayerID].Pos->column != 0))
	{
		do
		{
			printf("%s is in the middle section of the board. Should they move 'left', 'right', 'up', 'down', or 'back' to return to the turn menu ?\n", players[PlayerID].Name);
			fgets(input, sizeof(input), stdin);

			if ((check_input(input, "left") == 0))
			{
				//Moving left
				is_valid = moveDir(4);
			}

			else if ((check_input(input, "right") == 0))
			{
				//Moving right
				is_valid = moveDir(3);
			}

			else if ((check_input(input, "up") == 0))
			{
				//Moving up
				is_valid = moveDir(2);
			}

			else if ((check_input(input, "down") == 0))
			{
				//Moving down
				is_valid = moveDir(1);
			}

			else if (check_input(input, "back") == 0)
			{
				Turn_Choice(PlayerID);
				is_valid = true;
			}
			else
			{
				printf("Please enter a valid input.\n");
			}
		} while (is_valid == false);
	}

	//print an error if something went wrong
	else
	{
		printf("Problem moving player.\n");
	}

	//print the players health and location
	printf("Player: %s, Health: %d\n", players[PlayerID].Name, players[PlayerID].Health);
	printf("Location: (%d, %d)\n", players[PlayerID].Pos->row, players[PlayerID].Pos->column);
}

//Function used by Move to move the player into a different position
int moveDir(int dir)
{
	//Down
	if (dir == 1)
	{
		printf("%s is moving down.\n", players[PlayerID].Name);
		players[PlayerID].Pos = Board[players[PlayerID].Pos->row][players[PlayerID].Pos->column].down;
	}

	//Up
	else if (dir == 2)
	{
		printf("%s is moving up.\n", players[PlayerID].Name);
		players[PlayerID].Pos = Board[players[PlayerID].Pos->row][players[PlayerID].Pos->column].up;
	}

	//Right
	else if (dir == 3)
	{
		printf("%s is moving right.\n", players[PlayerID].Name);
		players[PlayerID].Pos = Board[players[PlayerID].Pos->row][players[PlayerID].Pos->column].right;
	}

	//Left
	else if (dir == 4)
	{
		printf("%s is moving left.\n", players[PlayerID].Name);
		players[PlayerID].Pos = Board[players[PlayerID].Pos->row][players[PlayerID].Pos->column].left;
	}

	return 1;

}
//Function to control when a player wants to attack
void Attack()
{

	bool is_valid = false;
	char input[20];

	//Get input until a command is recognised
	do
	{
		printf("Should %s perform a 'close' attack, a 'ranged' attack , a 'magic' attack or go 'back' to the turn menu  ?\n", players[PlayerID].Name);
		fgets(input, sizeof(input), stdin);

		//Player wants to attempt a close range attack
		if (check_input(input, "close") == 0)
		{
			close_range();
			is_valid = true;
		}

		//Player wants to attempt a long range attack
		else if (check_input(input, "ranged") == 0)
		{
			long_range();
			is_valid = true;
		}

		else if (check_input(input, "magic") == 0)
		{
			if ((players[PlayerID].Smartness + players[PlayerID].Magic_Skills) > 150)	//Player can only perform magic is they have a combined smartness and magic skill of 150+
			{
				magic_attack(PlayerID);
				is_valid = true;
			}

			//Tell them if they can't perform a magic attack
			else
			{
				printf("%s is not able to perform a magic attack.\n", players[PlayerID].Name);
			}
		}


		//Entering back will return the player to the turn_choice function
		else if (check_input(input, "back") == 0)
		{
			Turn_Choice(PlayerID);
			is_valid = true;
		}
		else
		{
			printf("Please enter a valid input.\n");
		}


	} while (is_valid == false);
}

//Function to control short range attacks
void close_range()
{
	struct Slot *currSlot = players[PlayerID].Pos;	//Store the current position of the player
	struct Slot *foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct Slot));	//Stores the slots that are found at the req. distance
	struct Player * *Targets = malloc(Remaining_Players * Remaining_Players * sizeof(struct Player));	//Stores the players that can be attacked
	bool explored[BOARD_SIZE][BOARD_SIZE];	//Bool array used to see what slots have been traversed while looking for slots
	int count = 0;
	int Num_Targets = 0;	//The number of players that can be attacked
	char input[20];
	bool is_valid = false;
	bool is_member = false;
	int i, j;
	int target;	//The id of the player who is being attacked

	//Setup bool array
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			explored[i][j] = false;
		}
	}


	if (currSlot != NULL)
	{

		//Find all eligible slots
		findSlots(1, 0, currSlot, foundSlots, &count, explored);


		//Check to see if there's someone in the same slot
		for (i = 0 ; i < Remaining_Players ; i++)
		{
			if ((players[i].Pos == players[PlayerID].Pos) && (i != PlayerID))
			{
				Targets[Num_Targets] = &players[i];	//Assign the player pointed to by i to the Targets array
				Num_Targets++;	//Increase the number of targets
			}
		}

		//Check to see if there's a player in any of those slots
		for (i = 0; i < count; i++)
		{
			for (j = 0; j < Remaining_Players; j++)
			{
				if ((j != PlayerID) && (players[j].Pos->row == foundSlots[i].row) && (players[j].Pos->column == foundSlots[i].column))
				{
					Targets[Num_Targets] = &players[j];	//Assign the player pointed to by i to the Targets array
					Num_Targets++;	//Increase the number of targets
				}
			}
		}

		//If there's a target let the player know and see who they want to attack
		if (Num_Targets > 0)
		{
			printf("Number of Targets: %d\n", Num_Targets);

			//Print the potential targets info
			for (i = 0; i < Num_Targets; i++)
			{
				printf("Player: %s ",Targets[i]->Name);
				if (Targets[i]->Type == 0)
				{
					printf("(Elf)\n");
				}

				else if (Targets[i]->Type == 1)
				{
					printf("(Human)");
				}

				else if (Targets[i]->Type == 2)
				{
					printf("(Ogre)");
				}

				else if (Targets[i]->Type == 3)
				{
					printf("(Wizard)");
				}

				printf("ID: %d\n", i);
			}

			//Do until the user enters a valid person to attack
			do
			{
				printf("Enter the ID of the player to attack: \n");
				fgets(input, sizeof(input), stdin);

				//Check to make sure it's a number
				for (i = 0; i < strlen(input); i++)
				{
					if (input[i] < 48 || input[i] > 57)
					{
						//Break out of the loop and force the user to input again. Input is contains non numeric characters
						break;
						is_valid = false;
						printf("Not a number\n");
					}
				}

				//Now check to see that it's a valid number referring to a member of the Targets array
				if (atoi(input) >= 0 && atoi(input) < Remaining_Players)
				{
					for (i = 0; i < Num_Targets; i++)
					{
						if ((atoi(input) == i))
						{

							is_member = true;	//Player entered a valid target id
							target = atoi(input);
						}
						else
						{
							printf("Please enter a valid ID\n");
							is_valid = false;
						}
					}
				}

				//If it's a member then attack that person
				if (is_member == true)
				{
					//Player wants to attack the entered player id
					//Check the conditions for a close attack
					if (Targets[target]->Strength <= 70)	//Attacked player takes damage
					{
						Targets[target]->Health -= floor(0.5 * players[PlayerID].Strength);	//Decrease the players health

						//Print the the amount of damage they took
						printf("%s received %.0lf points of damage from %s.\n", Targets[target]->Name, floor(0.5 * players[PlayerID].Strength), players[PlayerID].Name);

						//print their info again
						if (Targets[target]->Health < 0)	//if their health went below zero just print 0
						{
							printf("\nPlayer: %s, Health: %d\n", Targets[target]->Name, 0);
						}
						else
						{
							printf("\nPlayer: %s, Health: %d\n", Targets[target]->Name, Targets[target]->Health);
						}
						is_valid = true;
					}

					else
					{
						//Attacker is going to take damage from the attack
						players[PlayerID].Health -= floor(0.3 * Targets[target]->Strength);	//Decrease the attackers health
						printf("%s is really strong.\n", Targets[target]->Name);

						//Print the the amount of damage they took
						printf("%s received %.0lf points of damage from %s.\n", players[PlayerID].Name, floor(0.3 * Targets[target]->Strength), Targets[target]->Name);

						//print their info again
						if (Targets[target]->Health < 0)
						{
							printf("\nPlayer: %s, Health: %d\n", players[PlayerID].Name, 0);	//if their health went below zero just print 0
						}
						else
						{
							printf("\nPlayer: %s, Health: %d\n", players[PlayerID].Name, players[PlayerID].Health);
						}
						is_valid = true;
					}

				}
			} while (is_valid == false);
		}

		//If there is no targets then tell them and run the attack function again
		else
		{
			printf("No targets within range.\n");
			Attack();
		}

	}while (is_valid == false);
}

//Function which controls long range attacks
void long_range()
{
	//Very similar to close range except it finds slots at a range of 2 - 4 inclusive instead of just 1

	struct Slot *currSlot = players[PlayerID].Pos;	//Store the current position of the player
	struct Slot *foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct Slot));	//Stores the slots found at the req. distance
	struct Player * *Targets = malloc((Remaining_Players * Remaining_Players )* sizeof(struct Player));	//Stores the players that can be attacked
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count = 0;
	int Num_Targets = 0;
	char input[20];
	bool is_valid = true;
	bool is_member = false;
	int i, j;
	int target;


	//Set up the bool array

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			explored[i][j] = false;
		}
	}

	if (currSlot != NULL)
	{

		//Find all eligible slots
		findSlots(2, 0, currSlot, foundSlots, &count, explored);
		findSlots(3, 0, currSlot, foundSlots, &count, explored);
		findSlots(4, 0, currSlot, foundSlots, &count, explored);

		//Check to see if there's a player in any of those slots
		for (i = 0; i < count; i++)
		{
			for (j = 0; j < Remaining_Players; j++)
			{
				if ((j != PlayerID) && (players[j].Pos->row == foundSlots[i].row) && (players[j].Pos->column == foundSlots[i].column))
				{
					Targets[Num_Targets] = &players[j];
					Num_Targets++;
				}
			}
		}

		//If there's a target let the player know and see who they want to attack
		if (Num_Targets > 0)
		{
			printf("Number of Targets: %d\n", Num_Targets);

			for (i = 0; i < Num_Targets; i++)
			{
				printf("Player: %s ", Targets[i]->Name);
				if (Targets[i]->Type == 0)
				{
					printf("(Elf)");
				}

				else if (Targets[i]->Type == 1)
				{
					printf("(Human)");
				}

				else if (Targets[i]->Type == 2)
				{
					printf("(Ogre)");
				}

				else if (Targets[i]->Type == 3)
				{
					printf("(Wizard)");
				}
				printf("ID: %d\n", i );
			}

			do
			{
				printf("Enter the ID of the player to attack: \n");
				fgets(input, sizeof(input), stdin);

				//Check to make sure it's a number

				for (i = 0; i < strlen(input); i++)
				{
					if (input[i] < 48 || input[i] > 57)
					{
						//Break out of the loop and force the user to input again. Input is contains non numeric characters
						is_valid = false;
						break;


					}
				}

				//Now check to see that it's a valid number referring to a member of the Targets array
				if (atoi(input) >= 0 && atoi(input) < Remaining_Players)
				{
					for (i = 0; i < Num_Targets; i++)
					{
						if ((atoi(input) == i))
						{

							is_member = true;	//Player entered a valid target id
							target = atoi(input);
						}
						else
						{
							is_valid = false;
						}
					}
				}

				if (is_member == true)
				{
					//Player wants to attack the entered player id
					//Check the conditions for a ranged attack
					if (Targets[target]->Dexterity >= players[PlayerID].Dexterity)	//Attacked player is able to dodge attack
					{
						printf("%s is more dexterous than %s.\n", Targets[target]->Name, players[PlayerID].Name);
						printf("%s dodged the attack from %s\n", Targets[target]->Name, players[PlayerID].Name);
						is_valid = true;
					}

					else
					{
						//Target is going to take damage from the attack
						Targets[target]->Health -= floor(0.3 * players[PlayerID].Strength);
						printf("%s received %.0lf points of damage from %s.\n", Targets[target]->Name, floor(0.3 * players[PlayerID].Strength), players[PlayerID].Name);

						//Print their info again
						if (Targets[target]->Health < 0)	//if health falls below 0 just print 0
						{
							printf("\nName %s, Health: %d\n", Targets[target]->Name, 0);
						}
						else
						{
							printf("\nName %s, Health: %d\n", Targets[target]->Name, Targets[target]->Health);
						}
						is_valid = true;
					}

				}
			} while (is_valid == false);
		}

		//If no targets go back into the attack function
		else
		{
			printf("No targets within range.\n");
			Attack();
		}


	}
}

//Function to control the magic attacks
void magic_attack()
{

	bool is_valid = true;
	bool is_member = false;
	char input[20];
	int i;
	int target;
	struct Player * *Targets = malloc(Remaining_Players * Remaining_Players * sizeof(struct Player));	//used to store the attackable players


	//Store every player as a target except for the current target
	for (i = 0; i < Remaining_Players; i++)
	{
		if (i != PlayerID)
		{
			Targets[i] = &players[i];
		}
	}


	//Do until the user enters a valid player to attack
	do
	{
		for (i = 0; i < Remaining_Players; i++)
		{
			if (i != PlayerID)
			{
				printf("Player: %s, ID: %d ", players[i].Name, i);

				if (players[i].Type == 0)
				{
					printf("(Elf)\n");
				}

				else if (players[i].Type == 1)
				{
					printf("(Human)\n");
				}

				else if (players[i].Type == 2)
				{
					printf("(Ogre)\n");
				}

				else if (players[i].Type == 3)
				{
					printf("(Wizard)\n");
				}
			}
		}
		printf("Enter the ID of the player to attack: \n");
		fgets(input, sizeof(input), stdin);

		for (i = 0; i < strlen(input); i++)
		{
			if (input[i] < 48 || input[i] > 57)
			{
				is_valid = false;
				break;
			}
		}

		target = atoi(input);
		//Check to see if it's valid ID
		if ((target >= 0 || target < Remaining_Players) && target != PlayerID)
		{
			for (i = 0; i < Remaining_Players; i++)
			{
				if ((atoi(input) == i))
				{

					is_member = true;	//Player entered a valid target id
					target = atoi(input);
				}
				else
				{
					printf("Please enter a valid ID\n");
					is_valid = false;
				}
			}
		}

		if (is_member == true)
		{
			//Attack the target player
			Targets[target]->Health -=  floor((0.5 * players[PlayerID].Magic_Skills) + (0.2 * players[PlayerID].Smartness));

			printf("%s received %.0lf points of magic damage from %s\n", Targets[target]->Name, floor((0.5 * players[PlayerID].Magic_Skills) + (0.2 * players[PlayerID].Smartness)), players[PlayerID].Name);

			//print their info again
			if (Targets[target]->Health < 0)	//print zero if their health is less than 0
			{
				printf("\nPlayer: %s, Health: %d\n", Targets[target]->Name, 0);
			}
			else
			{
				printf("\nPlayer: %s, Health: %d\n", Targets[target]->Name, Targets[target]->Health);
			}
			is_valid = true;
		}

	} while (is_valid == false);

}

//Function used to find slots at a predefined distance
void findSlots(int reqDist, int currDist, struct Slot * currSlot, struct Slot * foundSlots, int *count, bool explored[BOARD_SIZE][BOARD_SIZE])
{
	//The base case: the current slot is at the required distance from the starting slot
	if (currDist == reqDist)
	{
		//the current slot was not explored
		if ((explored[currSlot->row][currSlot->column] == false))
		{
			//The next available position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else
	{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if (currSlot->up != NULL)
		{
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist + 1, currSlot->up, foundSlots, count, explored);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if (currSlot->right != NULL)
		{
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist + 1, currSlot->right, foundSlots, count, explored);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if (currSlot->down != NULL)
		{
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist + 1, currSlot->down, foundSlots, count, explored);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if (currSlot->left != NULL)
		{
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist + 1, currSlot->left, foundSlots, count, explored);
		}
	}
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
int getInput()
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
			output = 1;
			is_valid = true;
		}

		else if (check_input(input, "attack") == 0)
		{
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
void removePlayer(int PlayerToRemove)
{
	int i;
	struct Player deadPlayer[1];


	if (PlayerToRemove <= 1 && Remaining_Players != 2)
	{
		PlayerID--;
	}

	deadPlayer[0] = players[PlayerToRemove];

	for (i = PlayerToRemove; i < Remaining_Players; i++)
	{
		players[i] = players[i + 1];
	}

	players[Remaining_Players - 1] = deadPlayer[0];
	Remaining_Players--;
}

//Function to modify the players attributes based on what type of slot they are in
void modValues()
{
	//Assign the player the slot type of their current slot
	players[PlayerID].Pos->Type = Board[players[PlayerID].Pos->row][players[PlayerID].Pos->column].Type;

	//Modify their value based on that slot

	//Hill
	if (players[PlayerID].Pos->Type == 1)
	{
		//Low Dexterity
		if (players[PlayerID].Dexterity < 50 )
		{
			//If dexterity is greater than 10 subtract 10
			if (players[PlayerID].Dexterity > 10)
			{
				players[PlayerID].Strength -= 10;
				printf("%s's dexterity fails them on this hill.\nLose 10 Strength points(Strength %d)\n",players[PlayerID].Name, players[PlayerID].Strength);
			}

			//Otherwise check to see if their strength falls below 0
			else
			{
				players[PlayerID].Strength = 0;
				printf("%s is like Captain America... before he got pumped full of drugs! (Strength 0)\n",players[PlayerID].Name);
			}
		}

		//High Dexterity
		else if (players[PlayerID].Dexterity>= 60)
		{
			//Add 10 if less than 90
			if (players[PlayerID].Strength < 90)
			{
				players[PlayerID].Strength += 10;
				printf("%s's dexterity gives them the upper hand on this hill.\nGain 10 Strength points!(Strength %d)\n",players[PlayerID].Name,  players[PlayerID].Strength);
			}

			//Otherwise make it 100
			else
			{
				players[PlayerID].Strength = 100;
				printf("%s is as strong as Strong! (Strength maxed)\n",players[PlayerID].Name);
			}
		}
	}

	//City
	else if (players[PlayerID].Pos->Type== 2)
	{
		//High Smartness
		if (players[PlayerID].Smartness > 60)
		{
			//Add 10 if less than 90
			if (players[PlayerID].Magic_Skills < 90)
			{
				players[PlayerID].Magic_Skills += 10;
				printf("%s's intelligence is of benefit to them here in the city.\nGain 10 Magic Skill points!(Magic Skills: %d)\n",players[PlayerID].Name,  players[PlayerID].Magic_Skills);

			}

			//Otherwise make it 100
			else
			{
				players[PlayerID].Magic_Skills = 100;
				printf("%s is like Gandalf, or Dumbledore! You can't be any more magical!! (Magic Skills maxed)\n",players[PlayerID].Name);
			}

		}

		//Low Smartness
		else if (players[PlayerID].Smartness <= 50)
		{
			//Subtract 10 if greater than 10
			if (players[PlayerID].Smartness > 10)
			{
				players[PlayerID].Dexterity -= 10;
				printf("%s's intelligence fails them in the city and you find yourself lost\nLose 10 Dexterity points!(Dexterity %d)\n",players[PlayerID].Name,  players[PlayerID].Dexterity);
			}

			//Otherwise make it 0
			else
			{
				players[PlayerID].Dexterity = 0;
				printf("Could %s's Dexterity BE any lower!? (Dexterity 0)\n",players[PlayerID].Name);
			}
		}
	}
}

//Function to check to see if the game is over
int checkGameState()
{
	int return_value = 0;
	if (Remaining_Players == 1)
	{
		return_value = 1;
	}

	return return_value;
}
