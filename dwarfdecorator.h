#ifndef DWARFDECORATOR_H
#define DWARFDECORATOR_H
#include "playerdecorator.h"

class DwarfDecorator : public PlayerDecorator{
	public:
	DwarfDecorator(shared_ptr <Player> p): PlayerDecorator{p}{}
	void addGold(int) override;
};

#endif
