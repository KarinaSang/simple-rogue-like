#ifndef DRAGON_H
#define DRAGON_H
#include <memory>
#include "enemy.h"
#include "cell.h"


class Dragon : public Enemy {
	public:
	Dragon(Position);
};

#endif
