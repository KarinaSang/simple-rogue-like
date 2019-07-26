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
	Game game;
	TextDisplay td;
	Player player;

	//creating gameboard from file
	
	ifstream myfile {argv[1]};

	string line;
	while(getline (myfile, line)){

	}
	

	string cmd;

	//setting up player race
	cin >> cmd;

	if(cmd == "h"){
		player {};
	}
	else if(cmd == "e"){
		player{140, 30, 10};
	}
	else if(cmd == "d"){
		player{100, 20, 30};
	}
	else if(cmd == "o"){
		player{180, 30, 25};
	}

	game{make_shared<Player> player};


	//command interpreter
	while(cin >> cmd){
		
		if(cmd == "q"){
			//quit the game

		}
		else if(cmd == "r"){
			//restart the game

		}		
		else if(cmd == "u"){
			cin >> cmd; //direction to use potion
			//use potion...
		}	
		else if(cmd == "a"){
			cin >> cmd; //direction to attack
			//attack...

		}	
		else{
			//move the player
		}			
	}	
}


