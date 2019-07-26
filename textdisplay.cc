#include "textdisplay.h"

TextDisplay::TextDisplay(){}

istream &operator>> (istream&in, TextDisplay &td){
	for(int i = 0; i < td.BOARDHEIGHT; ++i){
		for(int j = 0; j < td.BOARDWIDTH; ++j){
			in >> td.theDisplay[i][j];
		}
	}
	return in;
}


ostream &operator<< (ostream &out, const TextDisplay &td){
	for(int i = 0; i < td.BOARDHEIGHT; ++i){
		for(int j = 0; j < td.BOARDWIDTH; ++j){
			out << td.theDisplay[i][j];
		}
	}
	return out;
}
