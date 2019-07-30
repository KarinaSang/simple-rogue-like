#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"

using namespace std;

class InvalidInput{};

shared_ptr <Player> createPlayer(string cmd){
		shared_ptr <Player> you;

		if(cmd == "h"){
			you = (make_shared <BasicPlayer> ());
		}
		else if(cmd == "e"){
			you = (make_shared <BasicPlayer> (140, 30, 10, "Elf"));
			you = make_shared <ElfDecorator> (you);
		}
		else if(cmd == "d"){
			you = (make_shared <BasicPlayer> (100, 20, 30, "Dwarf"));
			you = make_shared <DwarfDecorator> (you);
		}
		else if(cmd == "o"){
			you = (make_shared <BasicPlayer> (180, 30, 25, "Orc"));
			you = make_shared <OrcDecorator> (you);
		}
		else
			throw InvalidInput{};

		return you;
}


int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Provide at least one input file name" << endl;
		return 1;
	}

	ifstream myfile {argv[1]};

	//game essentials
	cout << "Ready for an adventure?" << endl;
	
	shared_ptr <Player> you;
	string cmd;
	cout << "Please enter your race ^ ^" << endl;
	
	//setting up player race
	cin >> cmd;

	if(cmd == "q"){
		return 0;
	}
	else{
		try{
			you = createPlayer(cmd);
		}catch (InvalidInput &e){
			cerr << "Invalid Input!" << endl;
			return 1;
		}
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
	
		if(!game.getStatus()){ //if game is over
			cout << "Please enter q to quit or r to restart." << endl;
			cin >> cmd;
			
			while(cmd != "q" && cmd != "r"){
				cerr << "Invalid Input!" << endl;
				cin >> cmd;
			}
		}	

		try{

			if(cmd == "q"){
				cout << "If heroes run and hide, who will stay and fight? See you next time." << endl;
				return 0;
			}
			else if(cmd == "next"){
				game.nextFloor();
				
				if(game.getFloorCount() <= 5){
					cout << game;
				}
				else{
					cout << "Congradulations on completing all level! We will make the game harder next time so you die!" << endl;
					cout << "Your final score is " + to_string(you->getScore()) << endl;
					cout << "Please press any key to continue." << endl;
				}

			}	

			else if(cmd == "r"){
				you = nullptr;
				
				//setting up player race
				cout << "Please enter your race ^ ^" << endl;
				cin >> cmd;
				you = createPlayer(cmd);

				game.reset(you);
				cout << game;

			}
			else{

				if(cmd == "u"){
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

				if(game.getStatus()){
				
					//enemy attacks or moves
					for(auto &e : game.getEnemy()){
						if(!game.enemyRadiusCheck(e)){
							game.generateEnemyMove(e);
						}
					}

					if(you->isDead()){
						game.setMsg2("HAHAHAHAHHAHAHA You died >:)");
						cout << game;
						cout << "Your final score is " + to_string(you->getScore()) << endl;
						cout << "Please press any key to continue." << endl;
					}
					else{
						cout << game; //print the game board
					}
					game.setMsg2(" ");
				}

				if(game.getFloorCount() > 5){
					cout << "Congradulations on completing all level! We will make the game harder next time so you die!" << endl;
					cout << "Your final score is " + to_string(you->getScore()) << endl;
					cout << "Please press any key to continue." << endl;
				}

			}

		} catch(InvalidInput &e){
			cerr << "Seems like you are purposefully crashing the game, good-bye!" << endl;
			return 1;
		} catch(InvalidMove &e){
			cout << game;
			game.setMsg("");
			game.setMsg2("");
		}
			
	}	
}


