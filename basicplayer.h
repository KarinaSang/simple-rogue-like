#ifndef BASICPLAYER_H
#define BASICPLAYER_H
#include "player.h"

class BasicPlayer : public Player{
	public:
	BasicPlayer(int hp = 140, int atk = 11000, int def = 20, string race = "Human");
	CharacterInfo getCurInfo () override{ return Player::getCurInfo();}		
	string getRace() override{return Player::getRace();}
	void addGold(int) override;
	void usePotion(shared_ptr <Potion>) override;
};

#endif
