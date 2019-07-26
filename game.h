#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class Cell;
class Player;
class Enemy;
class Potion;

class Game{
	vector <vector <Cell>> grid; //current floor

	//could have a text display here
	

	const int BOARDWIDTH = 79;
	const int BOARDHEIGHT = 30;
	const int TOTALENEMY = 20;
	const int TOTALPOTION = 10;
	const int TOTALTREASURE = 10;

	int floorCount = 1; //starting with floor one
	int enemyCount = 0;
	int potionCount = 0;
	int treasureCount = 0;
	bool suitEquipped = false;
	int score = 0;

	unique_ptr <Player> player;
	vector <unique_ptr<Enemy>> enemies;
	vector <unique_ptr<Potion>> carriedPotions; //potions not yet used

	

	public:
	Game(unique_ptr <Player>);
	~Game();
	void init();
	void nextFloor(); //go to next floor
	int calculateScore(); //calculate current score

	friend ostream &operator << (ostream &out, const Game &g); 
};


#endif
