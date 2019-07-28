#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"

using namespace std;

class InvalidInput{};

int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Provide at least one input file name" << endl;
		return 1;
	}

	ifstream myfile {argv[1]};

	//game essentials
	
	shared_ptr <Player> you;
	
	string cmd;
	//setting up player race
	try{
		cin >> cmd;
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
		else if(cmd == "q"){
			return 0;
		}
		else
			throw InvalidInput{};
	}
	catch(InvalidInput &e){
		cerr << "Invalid Input!" << endl;
		exit(1);
	}

	//creating gameboard from file, five floors
	Game game{you};
	game.floorplan.resize(game.TOTALFLOOR);
	

	for(int a = 0; a < game.TOTALFLOOR; ++a){
		myfile >> game.floorplan[a];
		game.floorplan[a].setFloor(a+1);
	}
	myfile.close();

	game.setDisplay(make_shared <TextDisplay> (game.floorplan[0]));


	game.init();
	cout << game;

	//command interpreter
	while(cin >> cmd){
		
		if(cmd == "q"){
			//display something
			return 0;

		}
		else if(cmd == "r"){
			you = nullptr;
			//setting up player race
			cin >> cmd;
			try{
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
				else if(cmd == "q"){
					return 0;
				}
				else
					throw InvalidInput{};
			}
			catch(InvalidInput &e){
				cerr << "Invalid Input!" << endl;
				exit(1);
			}

			game.reset(you);
			cout << game;

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
			cerr << "dir" << temp.x << temp.y << endl;
			game.playerMove(temp.x, temp.y, cmd);
		}
		
		//enemy attacks or moves
		for(auto &e : game.getEnemy()){
			if(!game.enemyRadiusCheck(e)){
				game.generateEnemyMove(e);
			}
		}

		//check the current game status
			cout << game;
		if(!game.getStatus()){
			cout << "Game over. Please enter 'q' to quit or 'r' to restart" << endl;
			cin >> cmd;
			
			if(cmd == "q") return 0;
			else if(cmd == "r"){ //restarting the game
				you = nullptr;
				//setting up player race
				cin >> cmd;
				try{
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
					else if(cmd == "q"){
						return 0;
					}
					else
						throw InvalidInput{};
				}
				catch(InvalidInput &e){
					cerr << "Invalid Input!" << endl;
					exit(1);
				}

				game.reset(you);
				cout << game;

			}
			else return 1;
		}		
			
	}	
}


