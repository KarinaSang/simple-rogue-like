#include "elfdecorator.h"

void ElfDecorator::addPotion(Potion &p){
	p.setEffect(true);
	PlayerDecorator::addPotion(p);
}
