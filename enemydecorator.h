#ifndef ENEMYDEC_H
#define ENEMYDEC_H
#include "enemy.h"

class EnemyDecorator : public Enemy {
	protected: 
	shared_ptr <Enemy> enemy;

	public:
	EnemyDecorator(shared_ptr <Enemy> enemy) : enemy{enemy} {}
	virtual ~EnemyDecorator();
	
	virtual void specialAbility() = 0;
};

#endif
