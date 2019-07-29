#ifndef DRAGON_H
#define DRAGON_H
#include <memory>
#include "enemy.h"
#include "cell.h"


class Dragon : public Enemy {
	public:
	Dragon(int x, int y);
	Position getTreasure(){ return Enemy::getTreasure();}
};

#endif
