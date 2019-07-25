#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemyDecorator.h"

class Merchant : public EnemyDecorator {
	public: 
	Merchant(Enemy *enemyComponent);
	
	void isHostile();
	void specialAbility() override;
};

#endif