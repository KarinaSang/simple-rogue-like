#ifndef TREASURE_H
#define TREASURE_H

class Treasure{
	int value;
	bool collectable;
	bool suit = false;
	bool compass = false;

	public:
	Treasure(int value, bool collectable);
	
	//getter
	int getValue(){return value;}
	bool isCollectable(){return collectable;}
	bool isSuit(){return suit;}
	bool isCompass(){return compass;}

	//setter
	void setCollectable(){collectable = true;}
	void setSuit(){suit = true;}
	void setCompass(){compass = true;}
};

#endif
