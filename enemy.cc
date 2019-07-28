#include "enemy.h"
#include "player.h"

Enemy::Enemy(int hp, int atk, int def, string race, char display):
	race{race}, display{display}{
		info.hp = hp;
		info.atk = atk;
		info.def = def;
	}


int Enemy::attack(shared_ptr <Player> p){
	//implement 50%of missing the attack
	srand(time(0));
	int randNum = rand() % 2;

	if(randNum == 0){	
		int damage = ceil((100.0/(100+p->getCurInfo().def))*info.atk);

		if(p->hasSuit()){ //if player has barrier suit
			damage /= 2;
		}

		//attacks player and deals dmg
		p->addHp(-1 * damage);
		return damage;
	}

	//else it is a miss
	return 0;
}

shared_ptr <Cell> Enemy::getTreasure(){
	return nullptr;
}

int Enemy::randNum() {
	srand(time(0));
	int n = (rand() % 3);
	if (n == 0) return -1;
	if (n == 1) return 0;
	return 1;
}
