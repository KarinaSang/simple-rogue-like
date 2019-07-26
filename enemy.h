#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include "object.h"

class Enemy : public Object {
	int hp;
	int atk;
	int def;
	int value;
	bool hostile;
	string race;
	string display;
	
	public:
	virtual ~Enemy();

	//getter methods
	int getHp() {return hp;}
  int getAtk() {return atk;}
  int getDef() {return def;}
  string getRace() {return race;}

	//setter methods
  void addHp(int n) {hp += n;}
  void addAtk(int n) {atk += n;}
  void addDef(int n) {def += n;}	

	virtual void specialAbility();
	virtual void attack(Player *p);
	bool dead();
	void move(int x, int y);
	void radiusCheck();
};


#endif
