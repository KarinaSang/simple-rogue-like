#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H
#include "player.h"

class PlayerDecorator : public Player{
	shared_ptr <Player> player;

	public:
	PlayerDecorator(shared_ptr <Player> p) : Player{*p}, player{p} {}
	shared_ptr<Player> getPlayer(){return player;}

	//getter
	virtual CharacterInfo getCurInfo(){ return player->getCurInfo();}
	virtual CharacterInfo getDefaultInfo(){return player->getDefaultInfo();}
	virtual string getRace(){ return player->getRace();}
	virtual bool hasSuit(){return player->hasSuit();}
	virtual int getGold(){return player->getGold();}
	virtual bool isDead(){return player->isDead();}

	//setter
	virtual void addHp(int n){player->addHp(n);}
	virtual void addAtk(int n){player->addAtk(n);}
	virtual void addDef(int n){player->addDef(n);}
	virtual void setDefaultInfo(int x, int y, int z){
		player->setDefaultInfo(x, y, z);}
	virtual void suitToggle(){player->suitToggle();}
	virtual void resetPlayer(){player->resetPlayer();}


	//other special abilities
	virtual void addGold(int n){ player->addGold(n);}
	virtual void usePotion(shared_ptr <Potion> p){player->usePotion(p);}
};

#endif
