#include "merchant.h"

Merchant::Merchant(Enemy *e) : EnemyDecorator(e) {}

void Merchant::isHostile() {
	//check if player attacks
	hostile = true;
}

void Merchant::specialAbility() {
	if (hp == 0) {
		//add treasure to board
	}
}
