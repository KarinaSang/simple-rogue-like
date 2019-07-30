#ifndef ENEMYDEC_H
#define ENEMYDEC_H
#include "enemy.h"

class EnemyDecorator : public Enemy {
	protected: 
	shared_ptr <Enemy> e;

	public:
	EnemyDecorator(shared_ptr <Enemy>);
	
	//getter methods
	virtual int getHp() {return e->getHp();}
 	virtual int getAtk() {return e->getAtk();}
	virtual int getDef() {return e->getDef();}
	virtual int getValue() {return e->getValue();}
	virtual string getRace() {return e->getRace();}
	virtual char getDisplay(){return e->getDisplay();}
	virtual bool getCompass() {return e->getCompass();}
	virtual bool isDead(){return e->isDead();}
	virtual Position getTreasure(){return e->getTreasure();}

	//setter methods(might not need to modify enemy's base ratio)
	virtual void addHp(int n) {e->addHp(n);}
	virtual void addAtk(int n) {e->addAtk(n);}
	virtual void addDef(int n) {e->addDef(n);}
	virtual void setValue(int n) {e->setValue(n);}
	virtual void setCompass(){e->setCompass();}

	virtual void specialAbility(shared_ptr<Player> p){e->specialAbility(p);} //CAN IMPLEMENT stealing health/gold from a player
	virtual int attack(shared_ptr<Player> p){return e->attack(p);}

};

#endif
