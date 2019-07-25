#ifndef OBJECT_H
#define OBJECT_H

class Object{
	int row = 0;
	int col = 0;

	public:
	Object();
	
	int getRow(){return row;}
	int getCol(){return col;}
	void setRow(int n){ row = n;}
	void setCol(int n){ col = n;}
};






#endif
