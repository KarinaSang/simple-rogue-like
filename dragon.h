#ifndef DRAGON_H
#define DRAGON_H
#include "enemyDecorator.h"

class Dragon : public EnemyDecorator {
	public:
	Dragon(Enemy *e);

	void specialAbility() override;
}

#endif
