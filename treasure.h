#ifndef TREASURE_H
#define TREASURE_H

class Treasure{
	int value;
	bool collectable;

	public:
	Treasure(int value, bool collectable);
	
	//getter
	int getValue(){return value;}
	bool isCollectable(){return collectable;}


	//setter
	void setCollectable(){collectable = true;}
};

#endif
