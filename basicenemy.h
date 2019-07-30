#ifndef BASICENEMY_H
#define BASICENEMY_H
#include <string>
#include "enemy.h"

class BasicEnemy : public Enemy {
	public:
	BasicEnemy(int hp , int atk, int def, string race, char display, int value = 1);
	string specialAbility(shared_ptr <Player> p) override {return "";};
};

#endif
