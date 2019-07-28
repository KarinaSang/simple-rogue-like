#include "game.h"
#include "enemy.h"
#include "basicenemy.h"
#include "dragon.h"
#include "merchant.h"

Game::Game(shared_ptr <Player> p): curP{p} {
	srand(time(0));
	suitFloor = rand()%5+1;
}


void Game::init(){	
//	td->generate(suitFloor); //RANDOM GENERATION OF THE BOARD
	grid.clear();
	grid.resize(BOARDHEIGHT);

	for(int i = 0; i < BOARDHEIGHT; ++i){
		for(int j = 0; j < BOARDWIDTH; ++j){
			char curChar = td->getChar(i, j);

			grid[i].emplace_back(Cell {i, j, '.'});

			//check what the current cell is
			switch(curChar){
				case '|':
				case '-':
				case '+':
				case ' ':
				case '#':
				case '.':
				case 'B':{
						 grid[i][j].setDisplay(curChar);
						 break;
					 }
				case '9':{
						break;
					 }
				case '@':{ //player
					grid[i][j].addPlayer(curP);
					player.x = i;
					player.y = j;
					break;
				}
				case '\\':{ //stairs
					stairs.x = i;
					stairs.y = j;
					grid[i][j].setDisplay(curChar);
					td->setChar(i, j, '.');		
					break;
				}
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
							if(td->getChar(i+a, j+b) == '9'
									|| td->getChar(i+a, j+b) == 'B'){ //found dragon hoard/barrier suit
								shared_ptr <Treasure> t = make_shared<Treasure> (6, false); //dragon hoard

								if(td->getChar(i+a, j+b) == 'B'){
									t->setSuit();
								}

								grid[i+a][j+b].addTreasure(t); //add treasure to cell

								if(td->getChar(i+a, j+b) == '9'){
									td->setChar(i+a, j+b, 'G'); //set textdisplay back to G
								}

								shared_ptr<Enemy> d = make_shared<Dragon>(Position {i+a, j+b}); //create dragon guarding dragon hoard
								grid[i][j].addEnemy(d);
								enemy.emplace_back(Position {i,j});

								cerr << d->getTreasure().x << d->getTreasure().y << endl;
							}
						}
					}

			  		break;
				}
				case '0':{ 
					shared_ptr<Potion> rh = make_shared<Potion>(10, 0, 0);
					grid[i][j].addPotion(rh);
					td->setChar(i, j, 'P');
					break;
				}
				case '1': {
					shared_ptr<Potion> ba = make_shared<Potion>(0, 5, 0);
					grid[i][j].addPotion(ba);
					td->setChar(i, j, 'P');	
					break;
				}
				case '2': {
					shared_ptr<Potion> bd = make_shared<Potion>(0, 0, 5);
					grid[i][j].addPotion(bd);
					td->setChar(i, j, 'P');
					break;
				}
				case '3': {
					shared_ptr<Potion> ph = make_shared<Potion>(-10, 0, 0);
					grid[i][j].addPotion(ph);
					td->setChar(i, j, 'P');
					break;
				}
				case '4': {
					shared_ptr<Potion> wa = make_shared<Potion>(0, -5, 0);
					grid[i][j].addPotion(wa);
					td->setChar(i, j, 'P');	
					break;
				}
				case '5': {
					shared_ptr<Potion> wd = make_shared<Potion>(0, 0, -5);
					grid[i][j].addPotion(wd);
					td->setChar(i, j, 'P');
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

	//generate the enemy that holds the Compass
	srand(time(0));
	int n = (rand() % td->enemyCount);
	Position pos{enemy[n]};

	while(td->getChar(pos.x, pos.y) == 'D'){
		n = (rand()% td->enemyCount);
		pos = enemy[n];
	}

	grid[pos.x][pos.y].getEnemy()->setCompass();
}


void Game::reset (shared_ptr <Player> p){
	gameStatus = true; //game is being run again

	td = make_shared <TextDisplay> (floorplan[0]);
	msg = "You have spawned!";
	floorCount = 1;
	suitEquipped = false;
	mHostility = false;

	srand(time(nullptr));
	suitFloor = rand()%5+1;

	curP = p;
	enemy.clear();
	carriedPotions.clear();

	init();

}



void Game::nextFloor(){
	if(floorCount == TOTALFLOOR){ //finished all floors
		gameStatus = false;
		return;
	}

	++floorCount;
	td = make_shared <TextDisplay> (floorplan[floorCount-1]);
	enemy.clear();

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
		grid[newX][newY].addPlayer(curP);
		grid[player.x][player.y].removePlayer();
		msg = "You moved " + getDir(dir);
		
		//modifies display
		td->setChar(player.x, player.y, grid[player.x][player.y].getDisplay());
		td->setChar(newX, newY, '@');
		
		//update player position in game
		player.x = newX;
		player.y = newY;
	}
}




void Game::playerAttack(int x, int y){
	shared_ptr <Enemy> temp = grid[player.x+x][player.y+y].getEnemy();

	//if target cell has an enemy
	if(temp != nullptr){
		int damage = ceil((100.0/(100+temp->getDef()))*curP->getCurInfo().atk);
		temp->addHp(-1*damage); //player deals dmg to enemy
		msg = "You dealt " + to_string(damage) + " damage to an adorable " + temp->getRace(); //update game msg
		msg += " Enemy's current hp is " + temp->getHp();

		//check if enemy is dead and remove it from the game board
		if(temp->isDead()){ //three cases, dragon, merchant, other enemies
			msg += " and you KILLED it!";
			td->setChar(player.x+x, player.y+y, '.'); //removes enemy from the display

			if(temp->getRace() == "Dragon"){
				Position tempT = temp->getTreasure();
				
				cerr << "dragon hoard " << tempT.x << tempT.y << endl;

				//the dragon hoard/barrier suit is now collectable
				grid[tempT.x][tempT.y].getTreasure()->setCollectable();
				msg += " The dragon hoard is now collectable!";

				if(temp->getCompass()){
						msg+= " Dragon dropped a Compass!";
						shared_ptr <Treasure> t = make_shared <Treasure> (0, true);
						t->setCompass();
						td->setChar(player.x+x, player.y+y, 'C'); //change the display
						grid[player.x+x][player.y+y].addTreasure(t); //add compass to associated cell
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
				curP->addGold(temp->getValue());

				//check if enemy has the compass
				if(temp->getCompass()){
					msg += " " + temp->getRace() + " dropped a Compass!";
					shared_ptr <Treasure> t = make_shared <Treasure> (0, true);
					t->setCompass();
					td->setChar(player.x+x, player.y+y, 'C'); //change the display
					grid[player.x+x][player.y+y].addTreasure(t); //add compass to associated cell	
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
		curP->usePotion(temp);
		msg = "You just consumed a " + temp->potionInfo();

		//modifies display
		td->setChar(player.x, player.y, '.');
		td->setChar(player.x+x, player.y+y, '@');
		
		//remove
		grid[player.x+x][player.y+y].removePotion();

		if(curP->isDead()){
			gameStatus = false;
		}
	}
	else{
		cerr << "Invalid Move!" << endl;
		//could throw an exception
	}	
}



void Game::playerCollect(int x, int y, string dir){
	shared_ptr<Treasure> temp = grid[player.x+x][player.y+y].getTreasure();

	if(temp != nullptr && temp->isCollectable()){ //could be gold, barrier suit, or compass

		if(temp->isSuit()){
			curP->suitToggle();
			msg = "You are now equipped with the Barrier Suit";
		}
		else if(temp->isCompass()){
			td->setChar(stairs.x, stairs.y, '\\');
			msg = "You have acquired a Compass! Stairs to the next floor are now showing.";
		}
		else{	
			curP->addGold(temp->getValue());
			msg = "You have acquired " + to_string(temp->getValue()) + " gold!";
		}

		//move the player to where the gold is
		grid[player.x+x][player.y+y].removeTreasure();
		this->playerMove(x, y, dir);
	}
	else{
		msg = "The treasure is not collectable at the moment";
		//could throw an exception
		cerr << "Invalid Move!" << endl;
	}
}


//enemy specific methods
bool Game::enemyRadiusCheck(Position e){

	shared_ptr <Enemy> temp = grid[e.x][e.y].getEnemy();

	if(temp == nullptr) return false;

	//check if the dragon should be hostile
	if (temp->getDisplay() == 'D' && !radiusHoardCheck(temp)) {
		return false;
	}

	//check if merchant should attack
	if(temp->getDisplay() == 'M' && !mHostility){
		return false;
	}

	//check if player is around enemy
	if(abs(player.x-e.x)<= 1 && abs(player.y-e.y) <= 1){
		int n = temp->attack(curP); //enemy attacks
	
		if(n == 0)
			msg += temp->getRace() + " missed!";
		else
			msg += temp->getRace() + " dealt " + to_string(n) + " damage to you.";
		
		//if player is dead
		if(curP->isDead()){
			gameStatus = false;
		}

		return true;
	}

	return false;
}

void Game::generateEnemyMove(Position &e){
	shared_ptr <Enemy> temp = grid[e.x][e.y].getEnemy();

	if(temp == nullptr) return;

	if (temp->getDisplay() == 'D') return;

	while(true){	
		int x = temp->randNum();
		int y = temp->randNum();

		while (x == 0 && y == 0){ //enemy must move
			y = temp->randNum();
			x = temp->randNum();
		}

		int newX = e.x+x;
		int newY = e.y+y;

		if (grid[newX][newY].getDisplay() == '.' && !grid[newX][newY].isFilled()) {
			enemyMove(newX, newY, e);
			e.x = newX;
			e.y = newY;
			break;
		}
	}

}

void Game::enemyMove(int x, int y, Position pos){
	shared_ptr <Enemy> temp = grid[pos.x][pos.y].getEnemy();
	if(temp != nullptr){
		grid[x][y].addEnemy(temp);

		//display
		td->setChar(pos.x, pos.y, '.');
		td->setChar(x, y, temp->getDisplay());

		grid[pos.x][pos.y].removeEnemy();
	}

}

bool Game::radiusHoardCheck(shared_ptr<Enemy> d) {
	int row = d->getTreasure().x;
	int col = d->getTreasure().y;

	if(abs(player.x-row) <= 1 && abs(player.y-col) <= 1)
		return true;

	return false;
}

ostream &operator<<(ostream &out, Game &g){
	out << *(g.td) <<endl;

	//add the 5 lines displaying relevant info
	out << "Race: " << g.curP->getRace() << " ";
	out << "Gold: " << g.curP->getGold();
	out << "             Floor " << g.floorCount << endl;
	out << "HP: " << g.curP->getCurInfo().hp << endl;
	out << "Atk: " << g.curP->getCurInfo().atk << endl;
	out << "Def: " << g.curP->getCurInfo().def << endl;
	out << "Action: " << g.msg << endl;

	return out;
}
