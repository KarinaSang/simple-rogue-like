#include "dragon.h"

Dragon::Dragon(shared_ptr <Cell> t) : treasure{t} {
	info.hp = 150;
	info.atk = 20;
	info.def = 20;
	race = "Dragon";
	display = 'D';
	value = 0;
}



