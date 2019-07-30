#include "trolldecorator.h"

TrollDecorator::TrollDecorator(shared_ptr <Enemy> e): EnemyDecorator{e} {}

string TrollDecorator::specialAbility(shared_ptr <Player> p){
	if(rand()%4 == 0){ //25% chance of health regen
		int n = this->getHp()*0.1;
		this->addHp(n);
		return "Troll regenerated " + to_string(n) + " hp, unlucky! Its current hp is " + to_string(getHp()) + "." ;
	}
	return "";
}

