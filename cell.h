#ifndef CELL_H
#define CELL_H
#include "textdisplay.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;


class Cell{
	int row, col;
	char display;
	
	//current cell could be either a player, enemy, potion, or treasure
	shared_ptr<Player> player = nullptr;
	shared_ptr<Enemy> enemy = nullptr;
	shared_ptr<Potion> potion = nullptr;
	shared_ptr<Treasure> treasure = nullptr;
	

	public:
	Cell(int row, int col, char display);

	//getter
	shared_ptr<Player> getPlayer(){return player;}
	shared_ptr<Enemy> getEnemy(){return enemy;}
	shared_ptr<Potion> getPotion(){return potion;}
	shared_ptr<Treasure> getTreasure (){return treasure;}
	int getRow() { return row;}
	int getCol() { return col;}
	char getDisplay(){return display;}

	//setter
	void addPlayer(shared_ptr<Player> p){player = make_shared<Player>(*p);}
	void addEnemy(shared_ptr<Enemy> e){enemy = make_shared<Enemy>(*e);}
	void addPotion(shared_ptr<Potion> p){potion = make_shared<Potion>(*p);}
	void addTreasure(shared_ptr<Treasure> t){treasure = make_shared<Treasure>(*t);}

	//when a gold/potion is collected/consumed, or when a player/enemy moves/dies
	void removePlayer(){player = nullptr;}
	void removeEnemy(){enemy = nullptr;}
	void removePotion(){potion = nullptr;}
	void removeTreasure(){treasure = nullptr;}

	bool isFilled(); //check if the current cell is occupied
	bool isStairs(); //check if the current cell is the stairs
	bool isWalkable(); //check if the current cell is a door/passage/floortile

};

#endif
