#include "player.h"

Player::Player(int hp, int atk, int def, string race){
	curInfo.hp = hp;
	curInfo.atk = atk;
	curInfo.def = def;
	defaultInfo.hp = hp;
	defaultInfo.atk = atk;
	defaultInfo.def = def;
	this->race = race;
}

Player::~Player(){}

void Player::resetPlayer(){
	curInfo.atk = defaultInfo.atk;
	curInfo.def = defaultInfo.def;
}

void Player::usePotion(shared_ptr <Potion> p){ 
	curInfo.hp += p->getHp();
	if(curInfo.hp < 0) curInfo.hp = 0;
	else if(curInfo.hp > defaultInfo.hp) curInfo.hp = defaultInfo.hp;

	curInfo.atk += p->getAtk();
	if(curInfo.atk < 0) curInfo.atk = 0;

	curInfo.def += p->getDef();
	if(curInfo.def < 0) curInfo.def = 0;
}

