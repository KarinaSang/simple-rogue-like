#include "player.h"
#include "enemy.h"

Player::Player (int hp, int atk, int def, string race):
	hp{hp}, atk{atk}, def{def}, race{race} {}


void Player::removeAllPotion(){
	for(auto p : this->tempPotion);
}

void Player::move(int x, int y){
	this->setRow(this->getRow() + x);
	this->setCol(this->getCol() + y);
}

void Player::attack(Enemy &e){

}


