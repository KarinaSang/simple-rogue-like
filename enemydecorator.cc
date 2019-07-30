#include "enemydecorator.h"

EnemyDecorator::EnemyDecorator(shared_ptr <Enemy> e) :
	Enemy{*e}, e{e} {}

