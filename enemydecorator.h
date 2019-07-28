#ifndef ENEMYDEC_H
#define ENEMYDEC_H
#include "enemy.h"

class EnemyDecorator : public Enemy {
	protected: 
	shared_ptr <Enemy> enemy;

	public:
	EnemyDecorator(shared_ptr <Enemy>);
//	virtual void specialAbility() = 0;
};

#endif
