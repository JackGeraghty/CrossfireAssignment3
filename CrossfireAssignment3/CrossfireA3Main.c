//Crossfire Assignment 3 Main C file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CrossfireA3Head.h"

//Main Function
int  main()
{
	setbuf(stdout, NULL);

	//Set number of players and slots to zero
	Num_Players = 0;
	Num_Slots = 0;

	//Print a welcome
	printf("|| Welcome to Crossfire ||\n");

	//Get number of players
	getNumInRange(2, 6);

	//Get their info
	getPlayerInfo();

	//setupBoard();

	Turn();


	return 0;
}
