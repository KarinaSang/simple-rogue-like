#include "treasure.h"

Treasure::Treasure(int value, bool collectable) : value{value},
	collectable{value > 3 ? false : true} {}

int Treasure::collect() {
	if (collectable == true) {
	}
}
