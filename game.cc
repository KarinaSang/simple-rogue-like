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

	//regenerate textdisplay
	//...
	cin >> *td;

	this->init();
}

int Game::calculateScore(){
	return grid[player.x][player.y].getPlayer()->getGold();
}

string Game::getDir(string dir){
	if(dir == "no")
		return "North";
	else if(dir == "so")
		return "South";
	else if(dir == "ea")
		return "East";
	else if(dir == "we")
		return "West";
	else if(dir == "ne")
		return "North East";
	else if(dir == "nw")
		return "North West";
	else if(dir == "se")
		return "South East";
	else if(dir == "sw")
		return "South West";

	//direction is undefined, could throw an exception
	return "";
}


//player specific methods
void Game::playerMove(int x, int y, string dir){
	int newX = player.x+x;
	int newY = player.y+y;

	//if the player will be moving to stairs
	if(grid[newX][newY].isStairs()){
		nextFloor();
		msg = "You have entered Floor " + floorCount;
		return;
	}

	//if the player will be walking over gold
	if(grid[newX][newY].getTreasure() != nullptr){
		playerCollect(x, y, dir);
	}

	else if(grid[newX][newY].isWalkable() && !grid[newX][newY].isFilled()){
		grid[newX][newY].addPlayer(grid[player.x][player.y].getPlayer());
		grid[player.x][player.y].removePlayer();
		msg = "You moved " + getDir(dir);
		
	}

	//update player position in game
	player.x = newX;
	player.y = newY;

	//modifies display
	td->setChar(player.x, player.y, grid[player.x][player.y].getDisplay());
	td->setChar(newX, newY, '@');

}




void Game::playerAttack(int x, int y){
	shared_ptr <Enemy> temp = grid[player.x+x][player.y+y].getEnemy();
	shared_ptr <Player> p = grid[player.x][player.y].getPlayer();

	//if target cell has an enemy
	if(temp != nullptr){
		int damage = ceil((100/(100+temp->getDef()))*p->getCurInfo().atk);
		temp->addHp(-1*damage); //player deals dmg to enemy
		msg = "You dealt " + to_string(damage) + " damage to an adorable " + temp->getRace(); //update game msg

		//check if enemy is dead and remove it from the game board
		if(temp->isDead()){ //three cases, dragon, merchant, other enemies
			msg += " and you KILLED it!";
			td->setChar(player.x+x, player.y+y, '.'); //removes enemy from the display

			if(temp->getRace() == "Dragon"){
				
				//the dragon hoard is now collectable
				temp->getTreasure()->setCollectable();

			}
			else if(temp->getRace() == "Merchant"){
				
				if(mHostility == false){ //if player kills merchant for the first time
					mHostility = true;
					msg += " You have lost the trust from merchants. All merchants will be hostile to you from now on."; //set msg
				}

				shared_ptr <Treasure> tempT {new Treasure {temp->getValue(), true}}; //the merchant hoard
				grid[player.x+x][player.y+y].addTreasure(tempT);//drops a merchant hoard
			
				td->setChar(player.x+x, player.y+y, 'G'); //set textdisplay to 'G'

			}
			else{ //all other enemies

			}

			grid[player.x+x][player.y+y].removeEnemy();


		}
	}
	else{
		cerr << "Invalid Move" << endl;
		//could throw an exception
	}
			
}




void Game::playerConsume(int x, int y){
	shared_ptr <Potion> temp = grid[player.x+x][player.y+y].getPotion();

	//if target cell has a potion
	if(temp != nullptr){
		grid[player.x][player.y].getPlayer()->usePotion(temp);
		msg = "You just consumed a " + temp->potionInfo();

		//modifies display
		td->setChar(player.x, player.y, grid[player.x][player.y].getDisplay());
		td->setChar(player.x+x, player.y+y, '@');

	}
	else{
		cerr << "Invalid Move!" << endl;
		//could throw an exception
	}	
}



void Game::playerCollect(int x, int y, string dir){
	shared_ptr<Treasure> temp = grid[player.x+x][player.y+y].getTreasure();
	if(temp != nullptr && temp->isCollectable()){
		grid[player.x][player.y].getPlayer()->collect(temp);
		
		msg = "You have acquired " + to_string(temp->getValue()) + " gold!";

		//move the player to where the gold is
		grid[player.x+x][player.y+y].removeTreasure();
		this->playerMove(x, y, dir);
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
	shared_ptr <Enemy> temp;
	for(auto e : enemy) {
		temp = grid[e.x][e.y].getEnemy();
		if (temp->getDisplay() == 'D') continue;
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
