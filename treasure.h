#ifndef TREASURE_H
#define TREASURE_H

class Treasure{
	int value;
	bool collectable;
	bool suit = false;

	public:
	Treasure(int value, bool collectable);
	
	//getter
	int getValue(){return value;}
	bool isCollectable(){return collectable;}
	bool getSuit(){return suit;}

	//setter
	void setCollectable(){collectable = true;}
	void setSuit(){suit = true;}
};

#endif
