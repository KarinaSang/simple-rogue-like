#include "enemy.h"


bool Enemy::dead() {
	return info.hp == 0;
}
