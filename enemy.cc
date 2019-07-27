#include "enemy.h"
#include "player.h"

int Enemy::attack(shared_ptr <Player> p){
	//implement 50%of missing the attack
	srand(time(nullptr));
	int randNum = rand() % 2;

	if(randNum == 0){	
		int damage = ceil((100/(100+p->getCurInfo().def))*info.atk);

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

int Enemy::randNum() {
	srand(time(nullptr));
	int n = (rand() % 3);
	if (n == 0) return -1;
	if (n == 1) return 0;
	return 1;
}
