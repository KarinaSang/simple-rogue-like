#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include "object.h"

class Enemy : public Object {
	int hp;
	int atk;
	int def;
	string race;
	
	public:
	virtual ~Enemy();

	virtual void specialAbility();
	virtual void attack(Player *p);
	void dead();
	void move(); // TODO: is this here or under game?
	void radiusCheck();
};


#endif
