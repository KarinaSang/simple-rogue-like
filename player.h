#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <memory>
#include "potion.h"
#include "treasure.h" 
#include "characterinfo.h"

using namespace std;

class Player{
	int gold = 0; //default to have zero gold
	char display = '@'; //letter representing the player

	//items
	bool suitEquipped = false;

	string race;
	CharacterInfo curInfo;
	CharacterInfo defaultInfo;

	public:
	Player(int hp, int atk, int def, string race);

	//getter methods
	virtual CharacterInfo getCurInfo(){return curInfo;}
	CharacterInfo getDefaultInfo() {return defaultInfo;}
	virtual string getRace() {return race;}
	bool hasSuit() {return suitEquipped;}
	int getGold(){return gold;}

	//setter methods
	void addHp(int n){
		curInfo.hp += n;
		if(curInfo.hp < 0) curInfo.hp = 0;
		else if(curInfo.hp > defaultInfo.hp) curInfo.hp = defaultInfo.hp;
	}
	void addAtk(int n){curInfo.atk += n;}
	void addDef(int n){curInfo.def += n;}
	virtual	void addGold(int n){gold += n;}
	void suitToggle(){(suitEquipped)? suitEquipped=false : suitEquipped=true;}

	bool isDead(){return (curInfo.hp == 0);}
	void resetPlayer(); //removes effects of all temporary potions
	virtual void usePotion(shared_ptr <Potion>);
};


#endif
