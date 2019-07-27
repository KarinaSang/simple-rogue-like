#include "enemy.h"
#include "player.h"

void Enemy::attack(shared_ptr <Player> p){
	//implement 50%of missing the attack
	
	int damage = ceil((100/(100+p->getCurInfo().def))*info.atk);

	if(p->hasSuit()){ //if player has barrier suit
		damage /= 2;
	}

	//attacks player and deals dmg
	p->addHp(-1 * damage);
}

int Enemy::randNum() {
	srand(time(nullptr));
	int n = (rand() % 3);
	if (n == 0) return -1;
	if (n == 1) return 0;
	return 1;
}
