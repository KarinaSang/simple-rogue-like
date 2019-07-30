#include "elfdecorator.h"
#include <iostream>

void ElfDecorator::usePotion(shared_ptr <Potion> p){
	this->addHp(abs(p->getHp()));
	this->addAtk(abs(p->getAtk()));
	this->addDef(abs(p->getDef()));
}
