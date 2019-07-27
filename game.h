#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "cell.h"
#include "textdisplay.h"
#include "position.h"

using namespace std;

class Game{
	vector <vector <Cell>> grid; //current floor

	unique_ptr <TextDisplay> td; //textdisplay of the game
	string msg = ""; //current action msg	

	const int BOARDWIDTH = 79;
	const int BOARDHEIGHT = 25;
	const int TOTALENEMY = 20;
	const int TOTALPOTION = 10;
	const int TOTALTREASURE = 10;

	int floorCount = 1; //starting with floor one
	int enemyCount = 0;
	int potionCount = 0;
	int treasureCount = 0;
	bool suitEquipped = false;
	bool mHostility = false; //merchant hostility towards player

	Position player;
	Position compass; //position of the compass
	vector <Position> enemy; //stores the position of generated enemies
	vector <shared_ptr<Potion>> carriedPotions; //potions not yet used

	

	public:
	Game();
	~Game() = default;
	void init();
	void nextFloor(); //go to next floor
	int calculateScore(); //calculate current score
	string getDir(string); //returns full name of any direction

	//player associated functions
	void playerMove(int x, int y, string dir);
	void playerAttack(int x, int y); //attacks something in certain direction
	void playerConsume(int x, int y); //consumes something(potion) in certain direction
	void playerCollect(int row, int col, string dir); //collects gold at current spot

	//enemy associated functions
	void enemyRadiusCheck(); //checks for the list of enemies, if there is player around them
  	//if a player is found, then the enemy will attack the player, else the enemy moves
	void allEnemyMove(); // loop for all enemies
	void enemyMove(int x, int y, Position p); // moves specific enemy

	//hoard associated functions
	void hoardRadiusCheck(); // checks if player is in range of hoard


	friend ostream &operator << (ostream &out, Game &g); 
};


#endif
