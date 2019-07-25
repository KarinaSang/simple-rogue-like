#ifndef CELL_H
#define CELL_H
#include <vector>
#include <string>
using namespace std;


class Cell{
	int row, col;
	char display;
	Object *obj = nullptr; //could be either a player, enemy, potion, or treasure

	public:
	Cell(int row, int col, char display);

	void addObject(Object *obj);
	void removeObject(); //when a gold/potion is collected/consumed, or when a player/enemy moves/dies
	bool isFilled(); //check if the current cell is occupied
	bool isStairs(); //check if the current cell is the stairs
	bool isWalkable(); //check if the current cell is a door/passage/floortile

};

#endif
