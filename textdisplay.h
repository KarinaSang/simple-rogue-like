#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

using namespace std;

class TextDisplay{
	vector<vector<char>> theDisplay;
	const int BOARDHEIGHT = 25;
	const int BOARDWIDTH = 79;
	public:
	TextDisplay();
	char getChar(int row, int col) {return theDisplay[row][col];}
	friend istream &operator >>(istream &in, TextDisplay &td);
	friend ostream &operator<<(ostream &out, const TextDisplay &td);
};
#endif
