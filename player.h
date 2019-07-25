#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "object.h"

using namespace std;

class Potion;
class Enemy;

class Player : public Object{
	//basic player info
	int hp;
	int atk;
	int def;
	string race;
	int gold = 0; //default to have zero gold
	char display = '@'; //letter representing the player

	//items
	bool suitEquipped = false;
	bool compassEquipped = false; //DO WE NEED THIS?
	vector <Potion*> tempPotion; //list of potions used for the current floor

	public:
	Player(int hp = 140, int atk = 20, int def = 20, string race = "human");

	//getter methods
	int getHp() {return hp;}
	int getAtk() {return atk;}
	int getDef() {return def;}
	string getRace() {return race;}
	bool hasSuit() {return suitEquipped;}
	virtual int getGold(){return gold;}

	//setter methods
	void addHp(int n) {hp += n;}
	void addAtk(int n) {atk += n;}
	void addDef(int n) {def += n;}
	void addGold(int n) {gold += n;}
	void suitToggle(){(suitEquipped)? suitEquipped=false : suitEquipped=true;}

	bool isDead(){return (hp == 0);}
	void removeAllPotion(); //removes effects of all temporary potions
	void move(int x, int y); // moves x blocks right, y blocks down
	void attack(Enemy &e); //attacks an enemy
	virtual void addPotion(Potion *p){tempPotion.emplace_back(p);}
};


#endif
