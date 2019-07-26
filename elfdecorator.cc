#include "elfdecorator.h"

void ElfDecorator::usePotion(shared_ptr <Potion> p){
	curInfo.hp += abs(p->getHp());
	if(curInfo.hp > defaultInfo.hp) curInfo.hp = defaultInfo.hp;

	curInfo.atk += abs(p->getAtk());
	curInfo.def += abs(p->getDef());
}
