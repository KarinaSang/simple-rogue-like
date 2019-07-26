#include "potion.h"

using namespace std;

void Potion::setHp(int n){
	if(this->effect)
		this->hp = n;
	else
		this->hp = -1*n;
}

void Potion::setAtk(int n){
	if(this->effect)
		this->atk = n;
	else
		this->atk = -1*n;
}

void Potion::setDef(int n){
	if(this->effect)
		this->def = n;
	else
		this->def = -1*n;
}

string Potion::potionInfo(){
	if(effect){ //positive potion
		if(hp != 0)
			return "Restore Health Potion";
		else if(atk != 0)
			return "Boost Attack Potion";
		else if(def != 0)
			return "Boost Defence Potion";
	}

	//negative potion
	if(hp != 0)
		return "Poison Health Potion";
	else if(atk != 0)
		return "Wound Attack Potion";
	else if(def != 0)
		return "Wound Defence Potion";
	else
		return "Neutral Potion";
}

	

