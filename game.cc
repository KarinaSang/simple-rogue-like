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
				case '\\': //stairs
					//change corresponding cell to stairs
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
	int newX = player.x+x;
	int newY = player.y+y;

	//if the player will be moving to stairs
	if(grid[newX][newY].isStairs()){
		nextFloor();
		return;
	}

	//if the player will be walking over gold
	if(grid[newX][newY].getTreasure() != nullptr){
		playerCollect(x, y);
		return;
	}

	if(grid[newX][newY].isWalkable() && !grid[newX][newY].isFilled()){
		grid[newX][newY].addPlayer(grid[player.x][player.y].getPlayer());
		grid[player.x][player.y].removePlayer();
		player.x = newX;
		player.y = newY;
	}
}




void Game::playerAttack(int x, int y){

}




void Game::playerConsume(int x, int y){
	//if targeted cell has a potion
	shared_ptr <Potion> temp = grid[player.x+x][player.y+y].getPotion();
	if(temp != nullptr){
		grid[player.x][player.y].getPlayer()->usePotion(temp);
		msg = "You just consumed a " + temp->potionInfo();
	}
	else{
		cerr << "Invalid Move!" << endl;
		//could throw an exception
	}	
}



void Game::playerCollect(int x, int y){
	shared_ptr<Treasure> temp = grid[player.x+x][player.y+y].getTreasure();
	if(temp != nullptr && temp->isCollectable()){
		grid[player.x][player.y].getPlayer()->collect(temp);
		
		msg = "You have acquired " + to_string(temp->getValue()) + " gold!";

		//move the player to where the gold is
		grid[player.x+x][player.y+y].removeTreasure();
		this->playerMove(x, y);
	}
	else{
		msg = "*Dragon Hoard* is not collectable at the moment";
		//could throw an exception
		cerr << "Invalid Move!" << endl;
	}
}


//enemy specific methods
void Game::enemyRadiusCheck(){
	
}

void Game::allEnemyMove(){
	Enemy temp;
	for(auto e : enemy) {
		temp = grid[e.x+x][e.y+y].getEnemy();
		if (temp.getDisplay() == "D") continue;
		while (true) {
			//TODO: generate number
			int x;
			int y;
			int newX = e.x+x;
			int newY = e.y+y;
			if (grid[newX][newY].isWalkable()&& !grid[newX][newY].isFilled()) {
				enemyMove(newX, newY, e);
				break;
			}
		}
	}
}

void Game::enemyMove(int x, int y, Position pos){
	grid[x][y].addEnemy(grid[pos.x][pos.y].getEnemy());
	grid[pos.x][pos.y].removeEnemy();
	pos.x = x;
  pos.y = y;
}

void Game::hoardRadiusCheck() {
	
}

ostream &operator<<(ostream &out, Game &g){
	out << *(g.td);

	shared_ptr <Player> temp = g.grid[g.player.x][g.player.y].getPlayer();

	//add the 5 lines displaying relevant info
	out << "Race: " << temp->getRace() << " ";
	out << "Gold: " << temp->getGold();
	out << "             Floor " << g.floorCount << endl;
	out << "HP: " << temp->getCurInfo().hp << endl;
	out << "Atk: " << temp->getCurInfo().atk << endl;
	out << "Def: " << temp->getCurInfo().def << endl;
	out << "Action: " << g.msg << endl;

	return out;
}
