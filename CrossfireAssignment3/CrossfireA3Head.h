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

enum PlayerType {ELF, HUMAN, OGRE, WIZARD};
enum SlotType {LEVEL_GROUND, HILL, CITY};


//Slot Struct
struct Slot{
	int row;
	int column;
	enum SlotType Type;
	struct Slot *left;
	struct Slot *right;
	struct Slot *up;
	struct Slot *down;
};

//Player Struct
struct Player{
	char Name[MAX_NAME_LEN];
	enum PlayerType Type;
	int Health;
	int Smartness;
	int Strength;
	int Magic_Skills;
	int Luck;
	int Dexterity;
	int row, column;
	int slot_type;
	int has_quit;

};

struct Player players[6];

//Function Prototypes

//Player Functions
void getNumInRange(int minNum, int maxNum);
void getPlayerInfo();
void fillPlayerAttributes(int PlayerID);
void printPlayers();

//Turn Functions
void Turn();
void Move(int PlayerID, int BoardSize);
void Attack(int PlayerID);
int check_input(char *StringIn, char *Command);
int getInput(int PlayerID);
void removePlayer(int PlayerID);
int moveDir(int PlayerID, int dir);
void modValues(int PlayerID);

//Board Functions
void createBoard(int Size, struct Slot **upLeft, struct Slot **upRight, struct Slot **downLeft, struct Slot **downRight);
void fillPlayers(int Size);

void removeNewline();



//Global Variables
int Num_Players;	//Number of players
int Remaining_Players; 	//Remaining number of players, used to see when game is over or player leaves game
int Num_Slots;		//Number of Slots
int slot_Types[7][7];

#endif /* CROSSFIREA3HEAD_H_ */
