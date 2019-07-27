#ifndef ELFDECORATOR_H
#define ELFDECORATOR_H
#include <cmath>
#include "playerdecorator.h"

class ElfDecorator : public PlayerDecorator{
	public:
	ElfDecorator(shared_ptr<Player>p) : PlayerDecorator{p}{}
	void usePotion(shared_ptr <Potion>) override; //negative potions have positive effect
};

#endif
