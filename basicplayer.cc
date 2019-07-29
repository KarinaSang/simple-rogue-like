#include "basicplayer.h"

BasicPlayer::BasicPlayer(int hp, int atk, int def, string race): Player{hp, atk, def, race} {}

void BasicPlayer::addGold(int n){
	Player::addGold(n); 
}

void BasicPlayer::usePotion(shared_ptr <Potion> p){
	Player::usePotion(p);
}
