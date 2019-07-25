#ifndef TREASURE_H
#define TREASURE_H
#include "object.h"

class Treasure : public Object {
	int value;
	bool collectable;

	public:
	Treasure(int value);
	~Treasure();

	int collect();
}

#endif
