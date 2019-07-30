#ifndef TROLL_H
#define TROLL_H
#include "enemydecorator.h"

class TrollDecorator : public EnemyDecorator{
	public:
	TrollDecorator(shared_ptr <Enemy>);
	string specialAbility(shared_ptr<Player>) override;
};

#endif
