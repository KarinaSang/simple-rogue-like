#ifndef POTION_H
#define POTION_H
#include <string>
#include "characterinfo.h"

using namespace std;

class Potion{
	int hp = 0;
	int atk = 0;
	int def = 0;
	bool effect = true; //true for positive, false for negative

	public:
	//getter
	int getHp(){return hp;}
	int getAtk(){return atk;}
	int getDef(){return def;}

	//setter
	void setHp(int n);
	void setAtk(int n);
	void setDef(int n);
	void setEffect(bool e){effect = e;}

	string potionInfo();

};



#endif
