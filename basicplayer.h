#ifndef BASICPLAYER_H
#define BASICPLAYER_H
#include "player.h"

class BasicPlayer : public Player{
	public:
	BasicPlayer(int hp = 140, int atk = 11000, int def = 20, string race = "human");
	CharacterInfo getCurInfo () override{ return Player::getCurInfo();}		
	void addGold(int) override;
	void usePotion(shared_ptr <Potion>) override;
};

#endif
