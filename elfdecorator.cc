#include "elfdecorator.h"

void ElfDecorator::usePotion(shared_ptr <Potion> p){
	shared_ptr<Player> temp = PlayerDecorator::getPlayer();

	temp->addHp(abs(p->getHp()));
	temp->addAtk(abs(p->getAtk()));
	temp->addDef(abs(p->getDef()));
}
