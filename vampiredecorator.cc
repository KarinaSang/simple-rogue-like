#include "vampiredecorator.h"

VampireDecorator::VampireDecorator(shared_ptr <Enemy> e): EnemyDecorator{e} {}

string VampireDecorator::specialAbility(shared_ptr <Player> p){
	if(rand()%4 == 0){ //25%chance of health stealing
		int n = p->getCurInfo().hp*0.05;
		this->addHp(n);
		return "Vampire stole " + to_string(n) + " hp from you! Its current hp is " + to_string(this->getHp()) + ".";
	}
	return "";
}

