#ifndef DRAGON_H
#define DRAGON_H
#include <memory>
#include "enemy.h"
#include "cell.h"


class Dragon : public Enemy {
	shared_ptr <Cell> treasure; //the treasure this dragon is guarding

	public:
	Dragon(shared_ptr <Cell> treasure);
	shared_ptr<Cell> getTreasure(){return treasure;}
};

#endif
