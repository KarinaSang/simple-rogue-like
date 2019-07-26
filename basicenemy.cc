#include "basicenemy.h"

BasicEnemy::BasicEnemy(int hp, int atk, int def, int value, bool hostile, string race, string display) :
	info.hp{hp}, info.atk{atk}, info.def{def}, value{value}, hostile{hostile}, race{race}, display{display} {}
