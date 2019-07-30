#ifndef POSITION_H
#define POSITION_H
#include <iostream>

struct Position{
	int x;
	int y;

//	Position operator=(Position p2){
//		return Position{p2.x, p2.y};
//	}

	bool operator==(Position p2){
		if(x == p2.x && y == p2.y)
			return true;
		return false;
	}
};



#endif
