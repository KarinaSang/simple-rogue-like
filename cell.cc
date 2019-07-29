#include "cell.h"

Cell::Cell (int row, int col, char display) : row{row}, col{col}, display{display}{}


bool Cell::isFilled(){
	if(player ==nullptr && enemy ==nullptr && potion==nullptr && treasure==nullptr){
		return false;
	}
	return true;
}


bool Cell::isStairs(){
	if(display == '\\')
		return true;
	return false;
}

bool Cell::isWalkable(){
	if(display == '.' || display == '+' || display == '#'){
		return true;
	}
	return false;
}
