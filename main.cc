#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"

using namespace std;

int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Provide at least one input file name" << endl;
		return 1;
	}

	//game essentials
	TextDisplay td;
	shared_ptr <Player> you;


	//creating gameboard from file
	
	ifstream myfile {argv[1]};

	string line;
	int rowCount = 0;
	while(getline (myfile, line)){
		for(int i = 0; i < int(line.length()); ++i){
			td.setChar(rowCount, i, line[i]);
		}
		rowCount++;
	}

	

	string cmd;

	//setting up player race
	if(cmd == "h"){
		you = (make_shared <BasicPlayer> ());
	}
	else if(cmd == "e"){
		you = (make_shared <BasicPlayer> (140, 30, 10));
		you = make_shared <ElfDecorator> (you);
	}
	else if(cmd == "d"){
		you = (make_shared <BasicPlayer> (100, 20, 30));
		you = make_shared <DwarfDecorator> (you);
	}
	else if(cmd == "o"){
		you = (make_shared <BasicPlayer> (180, 30, 25));
		you = make_shared <OrcDecorator> (you);
	}
	
	Game game{you}; //creates the game;
	game.setDisplay(make_shared <TextDisplay> (td));
	game.init();
	cout << game;

	//command interpreter
	while(cin >> cmd){
		
		if(cmd == "q"){
			//display something
			return 0;

		}
		else if(cmd == "r"){
			
			//TODO:restart the game

		}		
		else if(cmd == "u"){
			cin >> cmd; //direction to use potion
			Position temp = game.getPos(cmd);
			game.playerConsume(temp.x, temp.y);
		}	
		else if(cmd == "a"){
			cin >> cmd; //direction to attack
			Position temp = game.getPos(cmd);
			game.playerAttack(temp.x, temp.y);
		}	
		else{ //move the player
			Position temp = game.getPos(cmd);
			game.playerMove(temp.x, temp.y, cmd);
		}
		
		//enemy attacks or moves
		for(auto e : game.getEnemy()){
			if(!game.enemyRadiusCheck(e)){
				game.generateEnemyMove(e);
			}
		}
		cout << game;
	}	
}


