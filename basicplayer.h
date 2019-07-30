#ifndef BASICPLAYER_H
#define BASICPLAYER_H
#include "player.h"

class BasicPlayer : public Player{
	public:
	BasicPlayer(int hp = 140, int atk = 20, int def = 20, string race = "Human");
};

#endif
