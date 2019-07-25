#include "player.h"
#include "enemy.h"

Player::Player (int hp, int atk, int def, string race):
	hp{hp}, maxhp{hp}, atk{atk}, def{def}, race{race} {
		msg = "You are born as " + race;
	}


void Player::removeAllPotion(){
	while(!tempPotion.empty()){
		this->atk -= tempPotion.back().getAtk();
		this->def -= tempPotion.back().getDef();
		tempPotion.pop_back();
	}
}

void Player::move(int x, int y){
	msg = "You just made a move";

	this->setRow(this->getRow() + x);
	this->setCol(this->getCol() + y);
}

void Player::attack(Enemy &e){
	msg = "You dealt " + this->atk + " damage to " + e.getRace();

}

void Player::addPotion(Potion &p){
	msg = "You consumed a " + p.potionInfo();

	this->hp += p.getHp();
	if(this->hp < 0) this->hp = 0;
	else if(this->hp > this->maxhp) this->hp = this->maxhp;

	this->atk += p.getAtk();
	if(this->atk < 0) this->atk = 0;

	this->def += p.getDef();
	if(this->def < 0) this->def = 0;

	tempPotion.emplace_back(p);	
}
