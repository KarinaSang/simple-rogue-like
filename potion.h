#ifndef POTION_H
#define POTION_H
#include <string>
#include "object.h"

using namespace std;

class Player;

class Potion : public Object{
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

	void applyPotion(Player&);

	string potionInfo();

};



#endif
