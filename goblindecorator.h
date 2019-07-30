#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemydecorator.h"

class GoblinDecorator : public EnemyDecorator{
	public:
	GoblinDecorator(shared_ptr <Enemy>);
	string specialAbility(shared_ptr<Player>) override;
};

#endif
