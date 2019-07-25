#ifndef BASICPLAYER_H
#define BASICPLAYER_H
#include "player.h"

class BasicPlayer : public Player{
	public:
	int getGold() override;
	void addPotion(Potion*) override;
};

#endif
