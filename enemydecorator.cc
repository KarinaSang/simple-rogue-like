#include "enemydecorator.h"

EnemyDecorator::EnemyDecorator(shared_ptr <Enemy> enemy) :
	Enemy{*enemy}, enemy{enemy} {}

