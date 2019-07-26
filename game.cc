#include "game.h"

Game::Game() {}


void Game::init(){
	
	for(int i = 0; i < BOARDHEIGHT; ++i){
		for(int j = 0; j < BOARDWIDTH; ++j){
			char curChar = td->getChar(i, j);

			grid[i][j] = Cell {i, j, curChar};

			//check what the current cell is
			switch(curChar){
				case '|':
				case '-':
				case '+':
				case '#':
				case '.':{
						break;
					 }
				case '@': //player
					
					break;
				case 'V': //vampire
					//create an enemy = new Vampire
					//grid[i][j].addEnemy(...);
					//enemies.emplace_back(...); //push it to the list of enemies in game
					break;
				case 'W': //werewolf
					//create an enemy = new Werewolf
					//grid[i][j].addEnemy(...);
					//enemies.emplace_back(...); //push it to the list of enemies in game
					break;

				case 'N': //goblin
					//create an enemy = new Goblin
					//grid[i][j].addEnemy(...);
					//enemies.emplace_back(...); //push it to the list of enemies in game
					break;
				case 'X': //Phoenix
					//create an enemy = new Phoenix
					//grid[i][j].addEnemy(...);
					//enemies.emplace_back(...); //push it to the list of enemies in game
					break;
				case 'T': //troll
					//create an enemy = new Troll
					//grid[i][j].addEnemy(...);
					//enemies.emplace_back(...); //push it to the list of enemies in game
					break;
				case 'M': //merchant
					break;
				case 'D': //dragon
					//search for position of dragon hoard
					break;
				case 'P': //potion
					//do potion generation
					break;
				case '6': //normal gold
					//change textdisplay back to G
					break;
				case '7': //small hoard
					//change textdisplay back to G
					break;
				case '9': //dragon hoard
					//change textdisplay back to G
					break;
				case 'C': //compass
					break;
				case 'B': //barrier suit
					break;
			
			}
		}
	}
}

void Game::nextFloor(){
	++floorCount;
	this->init();
}

int Game::calculateScore(){
	return grid[player.x][player.y].getPlayer()->getGold();
}


//player specific methods
void Game::playerMove(int x, int y){

}


void Game::playerAttack(int x, int y){

}

void Game::playerConsume(int x, int y){

}

void Game::playerCollect(int x, int y){

}


//enemy specific methods
void Game::enemyRadiusCheck(){

}


void Game::enemyMove(int x, int y){

}

ostream &operator<<(ostream &out, const Game &g){
	out << *(g.td);

	//add the 5 lines displaying relevant info
	out << "Race: " << g.player->getRace() << " ";
	out << "Gold: " << g.player->getGold();
	out << "             Floor " << g.floorCount << endl;
	out << "HP: " << g.player->getCurInfo().hp << endl;
	out << "Atk: " << g.player->getCurInfo().atk << endl;
	out << "Def: " << g.player->getCurInfo().def << endl;
	out << "Action: " << g.msg << endl;

	return out;
}
