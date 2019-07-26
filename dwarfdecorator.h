#ifndef DWARFDECORATOR_H
#define DWARFDECORATOR_H
#include "playerdecorator.h"

class DwarfDecorator : public PlayerDecorator{
	public:
	void addGold(int) override;
};

#endif
