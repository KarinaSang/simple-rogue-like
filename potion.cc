#include "potion.h"

using namespace std;

Potion::Potion(int hp, int atk, int def) :
	hp{hp}, atk{atk}, def{def} {}


string Potion::potionInfo(){
	if(hp > 0)
		return "Restore Health Potion";
	else if(atk > 0)
		return "Boost Attack Potion";
	else if(def > 0)
		return "Boost Defence Potion";
	else if(hp < 0)
		return "Poison Health Potion";
	else if(atk < 0)
		return "Wound Attack Potion";
	else if(def < 0)
		return "Wound Defence Potion";
	else
		return "Neutral Potion";
}

	

