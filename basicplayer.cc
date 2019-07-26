#include "basicplayer.h"

BasicPlayer::BasicPlayer(int hp, int atk, int def, string race){
		race = race;
		curInfo.hp = hp;
		defaultInfo.hp = hp;
		curInfo.atk = atk;
		defaultInfo.atk = atk;
		curInfo.def = def;
		defaultInfo.def = def;
}

void BasicPlayer::addGold(int n){
	Player::addGold(n); 
}

void BasicPlayer::usePotion(shared_ptr <Potion> p){
	Player::usePotion(p);
}
