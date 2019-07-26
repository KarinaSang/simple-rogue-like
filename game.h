#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "cell.h"
#include "textdisplay.h"

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

	shared_ptr <Player> player;
	vector <shared_ptr<Enemy>> enemies;
	vector <shared_ptr<Potion>> carriedPotions; //potions not yet used

	

	public:
	Game(shared_ptr <Player>);
	~Game() = default;
	void init();
	void nextFloor(); //go to next floor
	int calculateScore(); //calculate current score

	//player associated functions
	void move(int x, int y);
	void attack(int x, int y); //attacks something in certain direction
	void consume(int x, int y); //consumes something(potion) in certain direction
	void collect(int row, int col); //collects gold at current spot
	friend ostream &operator << (ostream &out, const Game &g); 
};


#endif
