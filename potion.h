#ifndef POTION_H
#define POTION_H
#include <string>
#include "characterinfo.h"

using namespace std;

class Potion{
	int hp;
	int atk;
	int def;
	bool effect;

	public:
	//getter
	int getHp(){return hp;}
	int getAtk(){return atk;}
	int getDef(){return def;}
	bool getEffect(){return effect;}

	//setter
	void setHp(int n){hp = n;}
	void setAtk(int n){atk = n;}
	void setDef(int n){atk = n;}
	void setEffect(bool e){effect = e;}

	Potion(int hp, int atk, int def, bool effect);
	string potionInfo();

};



#endif
