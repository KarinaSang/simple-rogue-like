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

string getDir(string dir){
	if(dir == "ea"){
		return "East";
	}
	//...
}

Position Game::getPost(string dir) {
	if (dir == "no") return Position pos{-1, 0};
	if (dir == "so") return Position pos{1, 0};
	if (dir == "ea") return Position pos{0, 1};
	if (dir == "we") return Position pos{0, -1};
	if (dir == "ne") return Position pos{-1, 1};
	if (dir == "nw") return Position pos{-1, -1};
	if (dir == "se") return Position pos{1, 1};
	if (dir == "sw") return Position pos{1, -1};
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

	//modifies display
	td->setChar(player.x, player.y, grid[player.x][player.y].getDisplay());
	td->setChar(newX, newY, '@');

}




void Game::playerAttack(int x, int y){

}




void Game::playerConsume(int x, int y){
	//if targeted cell has a potion
	shared_ptr <Potion> temp = grid[player.x+x][player.y+y].getPotion();
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
	Position no{-1, 0};
	Position so{1, 0};
	Position ea{0, 1};
	Position we{0, -1};
	Position ne{-1, 1};
	Position nw{-1, -1};
	Position se{1, 1};
	Position sw{1, -1};
	shared_ptr<Player> p = grid[player.x][player.y].getPlayer();
	shared_ptr <Enemy> temp;
	for (auto e : enemy) {
		bool check = true;
		temp = grid[e.x][e.y].getEnemy();
		if (temp->getDisplay() == 'D') {
			if (radiusHoardCheck(temp)) check = true;
			else check = false;
		}
		if (check == true) {
			//check if player is north of enemy
			if (((e.x+no.x) == player.x) && ((e.y+no.y) == player.y)) {
				attack(p);
				break;
			}

			//check if player is south of enemy
			if (((e.x+so.x) == player.x) && ((e.y+so.y) == player.y)) {
				attack(p);
				break;
			}

			//check if player is east of enemy
			if (((e.x+ea.x) == player.x) && ((e.y+ea.y) == player.y)) {
				attack(p);
				break;
			}	
		
			//check if player is west of enemy
			if (((e.x+we.x) == player.x) && ((e.y+we.y) == player.y)) {
				attack(p);
				break;
			}
			//check if player is north east of enemy
			if (((e.x+ne.x) == player.x) && ((e.y+ne.y) == player.y)) {
				attack(p);
				break;
			}

			//check if player is north west of enemy
			if (((e.x+nw.x) == player.x) && ((e.y+nw.y) == player.y)) {
				attack(p);
				break;
			}

			//check if player is south east of enemy
			if (((e.x+se.x) == player.x) && ((e.y+se.y) == player.y)) {
				attack(p);
				break;
			}

			//check if player is south west of enemy
			if (((e.x+sw.x) == player.x) && ((e.y+sw.y) == player.y)) {
				attack(p);
				break;
			}
		}
	}
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
				e.x = newX;
				e.y = newY;
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

bool Game::hoardRadiusCheck(shared_ptr<Enemy> d) {
	Position no{-1, 0};
	Position so{1, 0};   
	Position ea{0, 1};
	Position we{0, -1};
	Position ne{-1, 1};
	Position nw{-1, -1};
	Position se{1, 1};  
	Position sw{1, -1};
	int row = temp.getTreasure().getRow();
	int col = temp.getTreasure().getCol();
	//check if player is north of hoard
	if (((row+no.x) == player.x) && ((col+no.y) == player.y)) 
		return true;
	//check if player is south of hoard
	if (((row+so.x) == player.x) && ((col+so.y) == player.y)) 
		return true;
	//check if player is east of hoard
	if (((row+ea.x) == player.x) && ((col+ea.y) == player.y))
		return true;
	//check if player is west of hoard
	if (((row+we.x) == player.x) && ((col+we.y) == player.y))
		return true;
	//check if player is north east of hoard
	if (((row+ne.x) == player.x) && ((col+ne.y) == player.y))
		return true;
	//check if player is north west of hoard
	if (((row+nw.x) == player.x) && ((col+nw.y) == player.y)) 
		return true;
	//check if player is south east of hoard
	if (((row+se.x) == player.x) && ((col+se.y) == player.y)) 
		return true;
	//check if player is south west of hoard
	if (((row+sw.x) == player.x) && ((col+sw.y) == player.y)) 
		return true;
	return false;
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
