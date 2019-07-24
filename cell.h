#ifndef CELL_H
#define CELL_H
#include <vector>
#include <string>
#include <game.h>
using namespace std;

class Player;
class Enemy;
class Potion;
class Gold;

class Cell{
	int row, col;
	char display;
	Player *player;
	Enemy *enemy;
	Potion *potion;
	Gold *gold;

	public:
	bool isFilled(); //check if the current cell is occupied
	bool isStairs(); //check if the current cell is the stairs
	bool isWalkable(); //check if the current cell is a door/passage/floortile

};

#endif
