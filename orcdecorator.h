#ifndef ORCDECORATOR_H
#define ORCDECORATOR_H
#include "playerdecorator.h"

class OrcDecorator : public PlayerDecorator{
	public:
	int getGold() override;
};

#endif
