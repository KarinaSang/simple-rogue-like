#ifndef ENEMYDEC_H
#define ENEMYDEC_H
#include "enemy.h"

class EnemyDecorator : public Enemy {
	protected: 
	Enemy *enemy;

	public:
	EnemyDecorator(Enemy *enemy);
	virtual ~EnemyDecorator();
	
	virtual void specialAbility() = 0;
};

#endif
