#ifndef DRAGON_H
#define DRAGON_H
#include <memory>
#include "enemydecorator.h"
#include "cell.h"


class Dragon : public EnemyDecorator {
	public:
	Dragon(shared_ptr <Enemy>);
};

#endif
