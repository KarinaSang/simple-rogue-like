#include "game.h"
#include "enemy.h"
#include "basicenemy.h"
#include "dragon.h"
#include "merchant.h"

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
				case '.':
				case '9':
				case 'B':{
						break;
					 }
				case '@': //player
					
					break;
				case '\\': //stairs
					//change corresponding cell to stairs
					break;
				case 'V':{ //vampire
					shared_ptr<Enemy> v = make_shared<BasicEnemy>(50, 25, 25, "Vampire", 'V');
					grid[i][j].addEnemy(v);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'W':{ //werewolf
					shared_ptr<Enemy> w = make_shared<BasicEnemy>(120, 30, 5, "Werewolf", 'W');
					grid[i][j].addEnemy(w);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'N':{ //goblin
					shared_ptr<Enemy> n = make_shared<BasicEnemy>(70, 5, 10, "Globlin", 'N');
					grid[i][j].addEnemy(n);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'X':{ //Phoenix
					shared_ptr<Enemy> x = make_shared<BasicEnemy>(50, 35, 20, "Phoenix", 'X');
					grid[i][j].addEnemy(x);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'T':{ //troll
					shared_ptr<Enemy> t = make_shared<BasicEnemy>(120, 25, 15, "Troll", 'T');
					grid[i][j].addEnemy(t);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'M':{ //merchant
					shared_ptr<Enemy> m = make_shared<Merchant>();
					grid[i][j].addEnemy(m);
					enemy.emplace_back(Position {i,j});
					break;
				}
				case 'D':{ //dragon
					//search for position of dragon hoard
					for(int a = -1; a <= 1; a++){
						for(int b = -1; b <= 1; b++){
							if(td->getChar(i+a, j+b) == '9' ||
									td->getChar(i+a, j+b) == 'B'){ //found dragon hoard/barrier suit
								shared_ptr <Treasure> t = make_shared<Treasure> (6, false); //dragon hoard

								if(td->getChar(i+a, j+b) == 'B'){
									t->setSuit();
								}

								grid[i+a][j+b].addTreasure(t); //add treasure to cell

								if(td->getChar(i+a, j+b) == '9'){
									td->setChar(i+a, j+b, 'G'); //set textdisplay back to G
								}

								shared_ptr<Enemy> d = make_shared<Dragon>(make_shared <Cell>(grid[i+a][j+b])); //create dragon guarding dragon hoard
								grid[i][j].addEnemy(d);
								enemy.emplace_back(Position {i,j});
								break;
							}
						}
					}

			  		break;
				}
				case '0':{ 
					shared_ptr<Potion> rh = make_shared<Potion>(10, 0, 0, true);
					grid[i][j].addPotion(p);
					break;
				}
				case '1': {
					shared_ptr<Potion> ba = make_shared<Potion>(0, 5, 0, true);
					grid[i][j].addPotion(p);
					break;
				}
				case '2': {
					shared_ptr<Potion> bd = make_shared<Potion>(0, 0, 5, true);
					grid[i][j].addPotion(p);
					break;
				}
				case '3': {
					shared_ptr<Potion> ph = make_shared<Potion>(10, 0, 0, false);
					grid[i][j].addPotion(ph);
					break;
				}
				case '4': {
					shared_ptr<Potion> wa = make_shared<Potion>(0, 5, 0, false);
					grid[i][j].addPotion(wa);
					break;
				}
				case '5': {
					shared_ptr<Potion> wd = make_shared<Potion>(0, 0, 5, false);
					grid[i][j].addPotion(wd);
					break;
				}
				case '6': {//normal gold
					//change textdisplay back to G
					shared_ptr<Treasure> tr = make_shared<Treasure>(1, true);
					grid[i][j].addTreasure(tr);
					td->setChar(i, j, 'G');
					break;
				}
				case '7': {//small hoard
					//change textdisplay back to G
					shared_ptr<Treasure> tr2 = make_shared<Treasure>(2, true);
					grid[i][j].addTreasure(tr2);
					td->setChar(i, j, 'G');
					break;
				}
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

Position Game::getPos(string dir) {
	if (dir == "no") return Position {-1, 0};
	else if (dir == "so") return Position {1, 0};
	else if (dir == "ea") return Position {0, 1};
	else if (dir == "we") return Position {0, -1};
	else if (dir == "ne") return Position {-1, 1};
	else if (dir == "nw") return Position {-1, -1};
	else if (dir == "se") return Position {1, 1};
	else if (dir == "sw") return Position {1, -1};
	else {
		//TODO: COULD THROW AN EXCEPTION
		return Position {0,0};
	}
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
				temp->getTreasure()->getTreasure()->setCollectable();
				msg += " The dragon hoard is now collectable!";

				if(temp->getCompass()){
						msg+= " You picked up a Compass too!";
						td->setChar(compass.x, compass.y, '\\');
				}
			}
			else if(temp->getRace() == "Merchant"){
				
				if(mHostility == false){ //if player kills merchant for the first time
					mHostility = true;
					msg += " You have lost the trust from merchants. All merchants will be hostile to you from now on."; //set msg
				}

				shared_ptr <Treasure> tempT = make_shared <Treasure> (temp->getValue(), true); //the merchant hoard
				grid[player.x+x][player.y+y].addTreasure(tempT);//drops a merchant hoard
			
				td->setChar(player.x+x, player.y+y, 'G'); //set textdisplay to 'G'

			}
			else{ //all other enemies
				msg += " You gained 1 gold~";
				p->addGold(temp->getValue());

				//check if enemy has the compass
				if(temp->getCompass()){
					msg += " You picked up a Compass!";
				
					td->setChar(compass.x, compass.y, '\\');//displays the stairs	
				}	
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
				temp->attack(p);
				break;
			}

			//check if player is south of enemy
			if (((e.x+so.x) == player.x) && ((e.y+so.y) == player.y)) {
				temp->attack(p);
				break;
			}

			//check if player is east of enemy
			if (((e.x+ea.x) == player.x) && ((e.y+ea.y) == player.y)) {
				temp->attack(p);
				break;
			}	
		
			//check if player is west of enemy
			if (((e.x+we.x) == player.x) && ((e.y+we.y) == player.y)) {
				temp->attack(p);
				break;
			}
			//check if player is north east of enemy
			if (((e.x+ne.x) == player.x) && ((e.y+ne.y) == player.y)) {
				temp->attack(p);
				break;
			}

			//check if player is north west of enemy
			if (((e.x+nw.x) == player.x) && ((e.y+nw.y) == player.y)) {
				temp->attack(p);
				break;
			}

			//check if player is south east of enemy
			if (((e.x+se.x) == player.x) && ((e.y+se.y) == player.y)) {
				temp->attack(p);
				break;
			}

			//check if player is south west of enemy
			if (((e.x+sw.x) == player.x) && ((e.y+sw.y) == player.y)) {
				temp->attack(p);
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

bool Game::radiusHoardCheck(shared_ptr<Enemy> d) {
	Position no{-1, 0};
	Position so{1, 0};   
	Position ea{0, 1};
	Position we{0, -1};
	Position ne{-1, 1};
	Position nw{-1, -1};
	Position se{1, 1};  
	Position sw{1, -1};
	int row = d->getTreasure()->getRow();
	int col = d->getTreasure()->getCol();
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
