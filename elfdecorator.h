#ifndef ELFDECORATOR_H
#define ELFDECORATOR_H
#include "playerdecorator.h"

class ElfDecorator : public PlayerDecorator{
	public:
	void addPotion(Potion*) override; //negative potions have positive effect
};

#endif
