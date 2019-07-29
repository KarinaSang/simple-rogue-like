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
class Cell;

class Enemy{
	bool hasCompass = false;


	CharacterInfo info;
	int value = 1;
	string race;
	char display;
	Position treasure;

	public:
	Enemy(int hp, int atk, int def, string race, char display, int x = 0, int y = 0);
	//getter methods
	virtual int getHp() {return info.hp;}
 	int getAtk() {return info.atk;}
	int getDef() {return info.def;}
	int getValue() {return value;}
	string getRace() {return race;}
	char getDisplay(){return display;}
	bool getCompass() {return hasCompass;}
	bool isDead(){return info.hp == 0;}
	virtual Position getTreasure(){return treasure;}

	//setter methods(might not need to modify enemy's base ratio)
	void addHp(int n) {
		info.hp += n;
		if(info.hp < 0)
			info.hp = 0;
	}
	void addAtk(int n) {info.atk += n;}
	void addDef(int n) {info.def += n;}
	void setValue(int n) {value = n;}
	void setCompass(){hasCompass = true;}

	int randNum();
//	virtual void specialAbility(shared_ptr<Player>); //CAN IMPLEMENT stealing health/gold from a player
	virtual int attack(shared_ptr<Player>);
};


#endif
