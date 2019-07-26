#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H
#include "player.h"

class PlayerDecorator : public Player{
	public:
	virtual int getGold();
	virtual void usePotion(shared_ptr <Potion> p){Player::usePotion(p);}
};

#endif
