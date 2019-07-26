#ifndef TREASURE_H
#define TREASURE_H
#include <string>
#include "object.h"

class Treasure : public Object {
	int value;
	bool collectable;
	string msg;
	public:
	Treasure(int value);
	~Treasure();

	int collect(Player *p);
}

#endif
