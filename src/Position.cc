#include "Position.h"

Position::Position(int x, int y): x{x}, y{y} {}
Position::~Position(){}
int Position::getX() const{
	return x;
}
int Position::getY() const{
	return y;
}
void Position::setPos(int x2, int y2){
	x = x2;
	y = y2;
}
