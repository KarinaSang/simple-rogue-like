#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H
#include "player.h"

class PlayerDecorator : public Player{
	shared_ptr <Player> player;
	public:
	PlayerDecorator(shared_ptr <Player> p) : Player{*p}, player{p} {}
	shared_ptr<Player> getPlayer(){return player;}
	virtual void addGold(int);
	virtual void usePotion(shared_ptr <Potion> p){player->usePotion(p);}
};

#endif
