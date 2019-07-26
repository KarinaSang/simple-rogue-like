#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <memory>
#include "characterinfo.h"

using namespace std;

class Player;

class Enemy{
	CharacterInfo info;
	int value;
	bool hostile;
	string race;
	char display;
	
	public:
	virtual ~Enemy();

	//getter methods
	int getHp() {return info.hp;}
  int getAtk() {return info.atk;}
  int getDef() {return info.def;}
  string getRace() {return race;}

	//setter methods(might not need to modify enemy's base ratio)
  void addHp(int n) {info.hp += n;}
  void addAtk(int n) {info.atk += n;}
  void addDef(int n) {info.def += n;}	

	virtual void specialAbility();
	virtual void attack(Player *p);
	bool dead();
	void move(int x, int y);
	void radiusCheck();
};


#endif
