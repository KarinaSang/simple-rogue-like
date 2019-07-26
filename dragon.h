#ifndef DRAGON_H
#define DRAGON_H
#include "enemyDecorator.h"

class Dragon : public EnemyDecorator {
	Treasure *hoard; gt

	public:
	Dragon(Enemy *e);

	void specialAbility() override;
}

#endif
