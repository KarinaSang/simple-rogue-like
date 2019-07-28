#ifndef POTION_H
#define POTION_H
#include <string>
#include "characterinfo.h"

using namespace std;

class Potion{
	int hp;
	int atk;
	int def;

	public:
	//getter
	int getHp(){return hp;}
	int getAtk(){return atk;}
	int getDef(){return def;}

	Potion(int hp, int atk, int def);
	string potionInfo();

};



#endif
