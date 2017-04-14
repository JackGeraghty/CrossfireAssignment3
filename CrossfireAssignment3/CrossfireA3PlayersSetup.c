//Crossfire Assignment 3 Functions used when creating the players and assigning them their attributes

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "CrossfireA3Head.h"

//Function to get a number from the user within a range and can deal with bad input
void getNumInRange(int minNum, int maxNum)
{
	srand(time(NULL));
	bool is_valid = false;	//Used to ensure good input from player
	bool is_num = false;	//Bool used to ensure good input
	char input[100];
	int i;

	//Getting Number of Players
	do
	{
		//Get Input
		printf("Enter the number of players(minimum 2, maximum 6):\n");
		fgets(input, sizeof(input), stdin);

		//Check to see if the input is only numbers
		for (i = 0; i < strlen(input); i++)
		{
			if (input[i] < 48 || input[i] > 57)
			{
				//break is used to escape the loop if any of the characters are not numbers
				break;
			}

			is_valid = true;

		}

		if (is_valid == true)
		{
			//Check to see if the number is in the given range
			if (atoi(input) >= minNum && atoi(input) <= maxNum)
			{
				//is  a valid number
				is_num = true;

				//Assign that value to number of players
				Num_Players = atoi(input);
			}

			else if (atoi(input) == 1)
			{
				printf("It's hard to play a game by yourself, get some friends.\n");
			}

			else
			{
				printf("Please enter a valid number.\n");
			}
		}
	} while (is_valid == false || is_num == false);
}

//Function to get Player Info from the user
void getPlayerInfo()
{
	int i, j;
	char input[MAX_SIZE_INPUT];
	bool is_valid;
	bool is_num;
	int minNum = 1;	//Lowest Player Type
	int maxNum = 4;	//Highest Player Type

	//Get Player Type///
	for (i = 0; i < Num_Players; i++)
	{
		//Do until input is valid
		do
		{
			is_num = false;
			is_valid = true;

			//Get the user to input the player types for each player
			printf("Enter the player type for Player %d:\n", i+1);
			printf("1 - Elf\n2 - Human\n3 - Ogre\n4 - Wizard\n");
			fgets(input, sizeof(input), stdin);

			for (j = 0; i < strlen(input); j++)
			{
				if (input[j] < 48 || input[j] > 57)
				{
					break;	//Bad input
					is_valid = false;
				}

			}

			//Input is Good
			if (is_valid == true)
			{

				if ((atoi(input) <= maxNum) && (atoi(input) >= minNum))
				{
					is_num = true;
					players[i].Type = atoi(input)-1;	//Subtract 1 to match enum
				}
			}
		} while (is_valid == false || is_num == false);

	}

	char Types[][7] = {"Elf", "Human", "Ogre", "Wizard"};	//Used for printing

	//Get Player Name///
	for (i = 0; i < Num_Players; i++)
	{
		//Conditionals to print player type beside name

		//Elf
		if (players[i].Type == 0)
		{
			printf("Enter the name for Player %d(%s):\n", i+1, Types[0]);
		}

		//Human
		else if (players[i].Type == 1)
		{
			printf("Enter the name for Player %d(%s):\n", i+1, Types[1]);
		}

		//Ogre
		else if (players[i].Type == 2)
		{
			printf("Enter the name for Player %d(%s):\n", i+1, Types[2]);
		}

		//Wizard
		else if (players[i].Type == 3)
		{
			printf("Enter the name for Player %d(%s):\n", i+1, Types[3]);
		}

		//Get the user to input the player's name
		fgets(input, MAX_NAME_LEN, stdin);

		removeNewline();	//Get rid of any newline characters left by fgets

		strcpy(players[i].Name, input);	//Put the name entered into the appropriate player

	}

//Fill Player Attributes Randomly
	for (i = 0; i < Num_Players; i++)
	{
		fillPlayerAttributes(i);	//Run the function to fill attributes
	}

	removeNewline();

	printPlayers();	//Print the info about each player
}

//Function to randomly fill the attributes for each player depending on their player type
void fillPlayerAttributes(int PlayerID)
{
	players[PlayerID].Health = 100; 	//Set each players health to 100

	//Conditionals for each player type

	//Elf
	if(players[PlayerID].Type == 0)
	{
		players[PlayerID].Magic_Skills = rand() % (80 + 1 - 50) + 50;
		players[PlayerID].Strength = rand() % (50 + 1 - 1) + 50;
		players[PlayerID].Dexterity = rand() % (100 + 1 - 1) + 1;
		players[PlayerID].Smartness = rand() % (100 + 1 - 70) + 70;
		players[PlayerID].Luck = rand() % (100 + 1 - 60) + 60;
	}

	//Human
	else if (players[PlayerID].Type == 1)
	{
		//Do until the sum of the values is less than 300
		do
		{
			players[PlayerID].Magic_Skills =  rand() % 101;
			players[PlayerID].Strength = rand() % 101;
			players[PlayerID].Dexterity = rand() % 101;
			players[PlayerID].Smartness = rand() % 101;
			players[PlayerID].Luck = rand() % 101;

		} while ((players[PlayerID].Magic_Skills + players[PlayerID].Strength + players[PlayerID].Dexterity + players[PlayerID].Smartness + players[PlayerID].Luck) >= 300);

	}

	//Ogre
	else if (players[PlayerID].Type == 2)
	{
		players[PlayerID].Magic_Skills = 0;
		players[PlayerID].Strength = rand() % (100 + 1 - 80) + 80;
		players[PlayerID].Dexterity = rand() % (100 + 1 - 80) + 80;
		players[PlayerID].Smartness = rand() % (20 + 1 - 0) + 0;
		players[PlayerID].Luck = (50 - players[PlayerID].Smartness);
	}

	//Wizard
	else if (players[PlayerID].Type == 3)
	{
		players[PlayerID].Magic_Skills = rand() % (100 + 1 - 80) + 80;
		players[PlayerID].Strength = rand() % (20 + 1 - 1) + 1	;
		players[PlayerID].Dexterity = rand() % (100 + 1 - 1) + 1;
		players[PlayerID].Smartness = rand() % (100 + 1 - 90) + 90;
		players[PlayerID].Luck = rand() % (100 + 1 - 50) + 50;
	}

	else
	{
		printf("Error\n");	//print in case there is an error assigning values
	}
}

//Function to print the players information
void printPlayers()
{
	int i;

		for (i = 0; i < Num_Players; i++)
		{
			printf("||%s's Attributes||\n", players[i].Name);

			//printf("ID : %d\n", players[i].ID);
			printf("Health : %d\n", players[i].Health);
			printf("Strength : %d\n", players[i].Strength);
			printf("Dexterity : %d\n", players[i].Dexterity);
			printf("Smartness : %d\n", players[i].Smartness);
			printf("Magic Skills : %d\n", players[i].Magic_Skills);
			printf("Luck : %d\n", players[i].Luck);

			printf("\n\n");
		}
}

//Function to remove the newline character left by fgets
void removeNewline(char *StringIn)
{
	int i,j;

	for (i = 0; i < Num_Players; i++)
	{
		for (j = 0; j < strlen(players[i].Name); j++)
		{
			if (players[i].Name[j] == '\n')
			{
				players[i].Name[j] = '\0';
			}

		}
	}
}
