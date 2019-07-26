#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H
#include "player.h"

class PlayerDecorator : public Player{
	shared_ptr <Player> player;
	public:
	virtual void addGold(int);
	virtual void usePotion(shared_ptr <Potion> p){player->usePotion(p);}
};

#endif
