#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H
#include "player.h"

class PlayerDecorator : public Player{
	public:
	virtual int getGold();
	virtual void addPotion(Potion*);
};

#endif
