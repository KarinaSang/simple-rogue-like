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
	Potion(int hp, int atk, int def, bool effect);

	//getter
	int getHp(){return hp;}
	int getAtk(){return atk;}
	int getDef(){return def;}

	//setter
	void setHp(int n);
	void setAtk(int n);
	void setDef(int n);

	string potionInfo();

};



#endif
