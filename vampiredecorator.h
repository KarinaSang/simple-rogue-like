#ifndef VAMPIREDECORATOR_H
#define VAMPIREDECORATOR_H
#include "enemydecorator.h"

class VampireDecorator : public EnemyDecorator{
	public:
	VampireDecorator(shared_ptr <Enemy>);
	string specialAbility(shared_ptr<Player>) override;
};

#endif
