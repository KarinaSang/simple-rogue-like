#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <memory>
#include <cmath>
#include <ctime>
#include "characterinfo.h"
#include "position.h"


using namespace std;

class Player;

class Enemy{
	bool hasCompass = false;
	CharacterInfo info;
	string race;
	char display;
	int value;
	Position treasure;

	public:
	Enemy(int hp, int atk, int def, string race, char display, int value, int x, int y);

	//getter methods
	virtual int getHp() {return info.hp;}
 	virtual int getAtk() {return info.atk;}
	virtual int getDef() {return info.def;}
	virtual int getValue() {return value;}
	virtual string getRace() {return race;}
	virtual char getDisplay(){return display;}
	virtual bool getCompass() {return hasCompass;}
	virtual bool isDead(){return info.hp == 0;}
	virtual Position getTreasure(){return treasure;}

	//setter methods(might not need to modify enemy's base ratio)
	virtual void addHp(int n) {
		info.hp += n;
		if(info.hp < 0)
			info.hp = 0;
	}
	virtual void addAtk(int n) {info.atk += n;}
	virtual void addDef(int n) {info.def += n;}
	virtual void setValue(int n) {value = n;}
	virtual void setCompass(){hasCompass = true;}

	virtual string specialAbility(shared_ptr<Player> p) {return "";} //CAN IMPLEMENT stealing health/gold from a player
	virtual int attack(shared_ptr<Player>);
};


#endif
