/*
 * CrossfireA3Head.h
 *
 *  Created on: 29 Mar 2017
 *      Author: jgera
 */

#ifndef CROSSFIREA3HEAD_H_
#define CROSSFIREA3HEAD_H_
#define MAX_NAME_LEN 25	//Max length of a player name
#define MAX_PLAYERS 6	//Max number of players
#define MAX_SIZE_INPUT 100 	//Max number for generic input


//Function Prototypes
void getNumInRange(int minNum, int maxNum);
void getPlayerInfo();
void fillPlayerAttributes(int PlayerID);
void printPlayers();
void removeNewline();
enum PlayerType {ELF, HUMAN, OGRE, WIZARD};
enum SlotType {LEVEL_GROUND, HILL, CITY};

//Slot Struct
typedef struct{
	int row;
	int column;
	enum SlotType Type;
}Slot;

//Player Struct
typedef struct {
	char Name[MAX_NAME_LEN];
	enum PlayerType Type;
	int Health;
	int Smartness;
	int Strength;
	int Magic_Skills;
	int Luck;
	int Dexterity;
	Slot *location;

}Player;



//Global Variables
int Num_Players;	//Number of players
int Remaining_Players; 	//Remaining number of players, used to see when game is over or player leaves game
int Num_Slots;		// Number of Slots
Player players[MAX_PLAYERS];
#endif /* CROSSFIREA3HEAD_H_ */
