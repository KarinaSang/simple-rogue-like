#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "position.h"

using namespace std;

class TextDisplay{
	vector<vector<char>> theDisplay;
	vector <Position> posV; //store positions available for random generation

	vector <Position> dir {{0, 1}, {1, 0}, {0,-1}, {-1,0},
		{1,1}, {-1,1}, {1,-1}, {-1,-1}}; //list of directions

	const int BOARDWIDTH = 79;
	const int BOARDHEIGHT = 25;
	const int TOTALENEMY = 20;
	const int TOTALPOTION = 10;
	const int TOTALTREASURE = 10;

	int enemyCount = 0;
	int potionCount = 0;
	int treasureCount = 0;
	int stairsCount = 0;
	int playerCount = 0;
	int floorNumber = 0;
	
	friend class Game;

	public:

	TextDisplay();
	Position randPos(); //randomly generate a position
	void generate(int floor);
	void generateStairs(vector<Position>);
	bool floodFill(vector<Position>&, vector<vector<bool>>&, int, int);
	bool generateDragon(int, int);
	
	//getter
	char getChar(int row, int col) {return theDisplay[row][col];}
	int getFloor(){return floorNumber;}

	//setter
	void setChar(int row, int col, char c){theDisplay[row][col] = c;}
	void setFloor(int n){ floorNumber = n;}

	friend istream &operator >>(istream &in, TextDisplay &td);
	friend ostream &operator<<(ostream &out, const TextDisplay &td);
};

#endif
