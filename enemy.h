#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <memory>
#include <cmath>
#include "characterinfo.h"

using namespace std;

class Player;

class Enemy{
	bool hasCompass = false;

	protected:
	CharacterInfo info;
	int value = 1;
	bool hostile = true;
	string race;
	char display;

	public:
	virtual ~Enemy();

	//getter methods
	int getHp() {return info.hp;}
 	int getAtk() {return info.atk;}
  int getDef() {return info.def;}
	string getRace() {return race;}
	char getDisplay(){return display;}
	bool isHostile(){return hostile;}
	bool isDead(){return info.hp == 0;}

	//setter methods(might not need to modify enemy's base ratio)
	void addHp(int n) {info.hp += n;}
	void addAtk(int n) {info.atk += n;}
	void addDef(int n) {info.def += n;}
	void setValue(int n) {value = n;}
	void toggleHostility(bool state){hostile = state;}
	void setCompass(){hasCompass = true;}

	virtual void specialAbility(shared_ptr<Player>); //CAN IMPLEMENT stealing health/gold from a player
	virtual void attack(shared_ptr<Player>);
};


#endif
