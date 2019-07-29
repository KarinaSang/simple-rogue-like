#include "textdisplay.h"

TextDisplay::TextDisplay(){}

Position TextDisplay::randPos(){
	int n = rand()%posV.size();
	Position temp = posV[n];
	posV.erase(posV.erase(posV.begin()+n));

	return temp;

}

bool TextDisplay::floodFill(vector <Position> &v, vector<vector<bool>> &visited, int x, int y){
	
	if(visited[x][y])
		return true;
	else if(theDisplay[x][y] == '|' || theDisplay[x][y] == '-')
		return true;
	else if(theDisplay[x][y] == '@')
		return false;

	visited[x][y] = true;
	
	if(theDisplay[x][y] == '.'){ //if marked generatable before
		v.erase(find(v.begin(),v.end(), Position{x, y}));
	}
	
	if(floodFill(v, visited, x+1, y) &&
			floodFill(v, visited, x-1, y) &&
			floodFill(v, visited, x, y+1) &&
			floodFill(v, visited, x, y-1))
		return true;

	return false;	
}


void TextDisplay::generateStairs(vector <Position> tempV){
	int n = rand()%tempV.size();

	vector<vector<bool>> visited (BOARDHEIGHT, vector<bool>(BOARDWIDTH, false));

	while(!floodFill(tempV, visited, tempV[n].x, tempV[n].y)){
		n = rand()%tempV.size();
	}


	theDisplay[tempV[n].x][tempV[n].y] = '\\';
	posV.erase(find(posV.begin(), posV.end(), tempV[n]));
	++stairsCount;
	cerr << "end stair" << endl;
}

bool TextDisplay::generateDragon(int r, int c){
	vector <Position> tempDir = dir;
	int randN = rand()%tempDir.size();

	Position p = tempDir[randN];

	auto n = find(posV.begin(), posV.end(), Position{r+p.x, c+p.y});	

	while(n == posV.end()){
		tempDir.erase(tempDir.begin()+randN);

		if(tempDir.empty()){
			return false;
		}

		randN = rand()%tempDir.size();
		p = tempDir[randN];
		n = find(posV.begin(), posV.end(), Position{r+p.x, c+p.y});
	}

	theDisplay[r+p.x][c+p.y] = 'D';
	posV.erase(n);
	++enemyCount;
	return true;
}



void TextDisplay::generate(int floor){
	//generating in order....

	//player
	if(playerCount == 0){
		++playerCount;
		Position p = randPos();
		theDisplay[p.x][p.y] = '@';
	}
	//stairs
	if(stairsCount == 0){
		generateStairs(posV);
	}
	
	//potions
	while(potionCount < TOTALPOTION){
		Position p = randPos();
		theDisplay[p.x][p.y] = '0' + rand()%6;
		++potionCount;
	}

	//treasure
	//barrier suit
	if(floorNumber == floor && treasureCount == 0){
		Position p = randPos();

		while(!generateDragon(p.x, p.y)){
			p = randPos();
		}

		theDisplay[p.x][p.y] = 'B';
		++treasureCount;
	}

	while(treasureCount < TOTALTREASURE){
		Position p = randPos();
		int n = rand()%8;

		if(n >= 0 && n <= 4){ //0,1,2,3,4 -> normal gold
			theDisplay[p.x][p.y] = '6';
		}
		else if(n == 5 || n == 6){
			theDisplay[p.x][p.y] = '7';
		}
		else{ //dragon hoard
			
			while(!generateDragon(p.x, p.y)){
				p = randPos();
			}

			theDisplay[p.x][p.y] = '9';
		}
		
		++treasureCount;
	}

	//enemies
	while(enemyCount < TOTALENEMY){
		Position p = randPos();
		int n = rand()%18;

		char e = 'E';

		if(n >= 0 && n <= 2){ //vampire
			e = 'V';
		}
		else if(n >= 3 && n <= 6){ //werewolf
			e = 'W';
		}
		else if(n >= 7 && n <= 11){ //goblin
			e = 'N';
		}
		else if(n == 12 || n == 13){ //phoenix
			e = 'X';
		}
		else if(n == 14 || n == 15){ //troll
			e = 'T';
		}
		else{ //merchant
			e = 'M';
		}
		
		theDisplay[p.x][p.y] = e;
		++enemyCount;
	}

	cerr << *this << endl;
	
}



istream &operator>> (istream&in, TextDisplay &td){
	char c;
	td.theDisplay.resize(td.BOARDHEIGHT);

	for(int i = 0; i < td.BOARDHEIGHT; ++i){
		td.theDisplay[i].resize(td.BOARDWIDTH+1);

		for(int j = 0; j < td.BOARDWIDTH; ++j){
			in >> noskipws >> c;
			td.theDisplay[i][j] = c;

			//checks what the input is
			if(c == '\\'){
			       	++td.stairsCount;
			}
			else if(c == '@'){
			       	++td.playerCount;
			}
			else if(c-'0' >= 0 && c-'0' <= 5){
			       	++td.potionCount;
			}
			else if(c-'0' >= 6 && c-'0' <= 9){
			       if(c-'0' == 8){//if merchant hoard
				       td.theDisplay[i][j] = 'M';
				       ++td.enemyCount;
			       }
			       else{
				       ++td.treasureCount;
			       }
			}
			else if(c == 'B'){
			       	++td.treasureCount;
			}
			else if (c == 'V' || c == 'W' || c == 'N' || c == 'D' ||
					c == 'X' || c == 'T' || c == 'M'){
			       	++td.enemyCount;	
			}
			else if(c == '.'){ //this is available for random generation
				td.posV.emplace_back(Position{i,j});
			}
		}
		in >> noskipws >> c; //new line character
	}
	return in;
}


ostream &operator<< (ostream &out, const TextDisplay &td){
	for(int r = 0; r < td.BOARDHEIGHT; ++r){
		for(int t = 0; t < td.BOARDWIDTH; ++t){
			out << td.theDisplay[r][t];
		}
		out << endl;
	}
	return out;
}
