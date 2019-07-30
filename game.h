#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include "cell.h"
#include "textdisplay.h"
#include "position.h"

using namespace std;

class InvalidMove{ //exception handling
};

class Game{
	vector <vector <Cell>> grid; //current floor

	shared_ptr <TextDisplay> td; //textdisplay of the game
	string msg = "You have spawned! "; //current action msg
	bool gameStatus = true;	

	int floorCount = 1; //starting with floor one
	bool mHostility = false; //merchant hostility towards player
	int suitFloor = 0; //where barrier suit could be located

	Position player;
	shared_ptr <Player> curP;
	Position stairs; //position of the compass
	vector <Position> enemy; //stores the position of generated enemies
	vector <shared_ptr<Potion>> carriedPotions; //potions not yet used

	

	public:
	Game(shared_ptr<Player>);
	~Game() = default;
	
	vector <TextDisplay> floorplan; //the floor plan
	const int BOARDWIDTH = 79;
	const int BOARDHEIGHT = 25;
	const int TOTALENEMY = 20;
	const int TOTALPOTION = 10;
	const int TOTALTREASURE = 10;
	const int TOTALFLOOR = 5;

	bool getStatus() {return gameStatus;}

	//setter
	void setDisplay(shared_ptr <TextDisplay> temp){td = temp;}
	void init();
	void reset(shared_ptr <Player> p); //take in a new player
	void nextFloor(); //go to next floor
	int calculateScore(); //calculate current score
	string getDir(string); //returns full name of any direction
	Position getPos(string); // returns position associated with direction

	//player associated functions
	vector<Position> &getEnemy(){return enemy;}


	void playerMove(int x, int y, string dir);
	void playerAttack(int x, int y); //attacks something in certain direction
	void playerConsume(int x, int y); //consumes something(potion) in certain direction
	void playerCollect(int row, int col, string dir); //collects gold at current spot

	//enemy associated functions
	bool enemyRadiusCheck(Position); //checks for the list of enemies, if there is player around them
  	//if a player is found, then the enemy will attack the player, else the enemy moves
	void generateEnemyMove(Position &e); // loop for all enemies
	void enemyMove(int x, int y, Position p); // moves specific enemy

	//hoard associated functions
	bool radiusHoardCheck(shared_ptr<Enemy> d); // checks if player is in range of hoard


	friend ostream &operator << (ostream &out, Game &g); 
};


#endif
