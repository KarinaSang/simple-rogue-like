#include "enemy.h"
#include "player.h"

Enemy::Enemy(int hp, int atk, int def, string race, char display, int value):
	race{race}, display{display}, value{value}{
		info.hp = hp;
		info.atk = atk;
		info.def = def;
	}

Enemy::~Enemy(){}

int Enemy::attack(shared_ptr <Player> p){
	//implement 50%of missing the attack
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

