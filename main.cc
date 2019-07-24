#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//other includes

using namespace std;

int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Provide at least one input file name" << endl;
		return 1;
	}

	const int BOARDWIDTH = 79;
	const int BOARDHEIGHT = 30;


	//creating gameboard from file
	
	ifstream myfile {argv[1]};

	string line;
	while(getline (myfile, line)){

	}




	string cmd;

	//setting up player race
	cin >> cmd;

	if(cmd == "h"){

	}
	else if(cmd == "e"){
		
	}
	else if(cmd == "d"){

	}
	else if(cmd == "o"){

	}


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


