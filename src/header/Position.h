#ifndef POSITION_H
#define POSITION_H

class Position{
	int x;
	int y;
      public:
	Position(int x, int y);
	~Position();
	//Position(Position& other); //not sure if we need copy ctr, we will be copying tho in Piece ctr
				   //also does that mean we need big 5 for this?
	int getX() const;
	int getY() const;
	void setPos(int x2, int y2);
};

#endif
