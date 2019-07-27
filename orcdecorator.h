#ifndef ORCDECORATOR_H
#define ORCDECORATOR_H
#include "playerdecorator.h"

class OrcDecorator : public PlayerDecorator{
	public:
	OrcDecorator(shared_ptr<Player>p) : PlayerDecorator{p}{}
	void addGold(int) override;
};

#endif
