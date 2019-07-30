#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemydecorator.h"
#include "cell.h"

class Merchant : public EnemyDecorator {
	public: 
	Merchant(shared_ptr <Enemy>);
};

#endif
