#include "Square.h"
#include <iostream>
#include "Piece.h"
using namespace std;

Square::Square(shared_ptr<Piece> p, string c): piece{p}, colour{c} {}

Square::~Square(){}

string Square::getColour() const{
	return colour;
}
shared_ptr<Piece> Square::getPiece() const{
	return piece;
}
Piece* Square::getPiece2() const{
	return piece.get();
}

void Square::setPiece(shared_ptr<Piece> p){
	piece = p;
}
