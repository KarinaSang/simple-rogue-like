#include "dragon.h"

Dragon::Dragon(shared_ptr <Cell> t) : Enemy{150, 20, 20, "Dragon", 'D'}, treasure{t} {
	value = 0;
}



