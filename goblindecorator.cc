#include "goblindecorator.h"

GoblinDecorator::GoblinDecorator(shared_ptr <Enemy> e): EnemyDecorator{e} {}

string GoblinDecorator::specialAbility(shared_ptr <Player> p){
	if(rand()%4 == 0 && p->getGold() != 0){ //25% chance of gold stealing
		this->setValue(this->getValue()+1);
		p->addGold(-1);
		return "Goblin stole 1 gold from you, it is worth " + to_string(this->getValue()) + " gold now. KILL IT!";
	}
	return "";
}

