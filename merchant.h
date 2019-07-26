#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
#include "cell.h"

class Merchant : public Enemy {
	shared_ptr <Cell> treasure;

	public: 
	Merchant(shared_ptr <Cell>);
	shared_ptr <Cell> getTreasure(){return treasure;}
};

#endif
