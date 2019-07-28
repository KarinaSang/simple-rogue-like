#include "dragon.h"

Dragon::Dragon(Position t) : Enemy{150, 20, 20, "Dragon", 'D'}{
	treasure = t;
	value = 0;
}



