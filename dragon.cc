#include "dragon.h"

Dragon::Dragon(Enemy *e) : EnemyDecorator(e) {}

void Dragon::specialAbility() {
	if (hp == 0) {
		hoard->collectable = true;
	}
}


