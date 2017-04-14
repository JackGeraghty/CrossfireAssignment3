/*
 * CrossfireA3Head.h
 *
 *  Created on: 29 Mar 2017
 *      Author: jgera
 */

#ifndef CROSSFIREA3HEAD_H_
#define CROSSFIREA3HEAD_H_
#include <stdbool.h>
#define MAX_NAME_LEN 25	//Max length of a player name
#define MAX_PLAYERS 6	//Max number of players
#define MAX_SIZE_INPUT 100 	//Max number for generic input
#define BOARD_SIZE 7

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
	struct Slot *Pos;
	int slot_type;
	int has_quit;
};


//Function Prototypes

//Player Functions
void getNumInRange(int minNum, int maxNum);
void getPlayerInfo();
void fillPlayerAttributes(int PlayerID);
void printPlayers();

//Turn Functions
void Turn();
void Move(int BoardSize);
void Attack();
int check_input(char *StringIn, char *Command);
int getInput();
void removePlayer();
int moveDir(int dir);
void modValues();
int checkGameState();
void close_range();
void long_range();
void magic_attack();
void findSlots(int reqDist, int currDist,  struct Slot * currSlot, struct Slot * foundSlots, int * count,  bool explored[BOARD_SIZE][BOARD_SIZE]);
void Turn_Choice();


//Board Functions
void createBoard(int Size, struct Slot **upLeft, struct Slot **upRight, struct Slot **downLeft, struct Slot **downRight);
void fillPlayers(int Size);

void removeNewline();

//Global Variables
int Num_Players;	//Number of players
int Remaining_Players; 	//Remaining number of players, used to see when game is over or player leaves game
struct Slot **Board;
struct Player players[6];
struct Slot *upLeft;
struct Slot *upRight;
struct Slot *downRight;
struct Slot *downLeft;


#endif /* CROSSFIREA3HEAD_H_ */
