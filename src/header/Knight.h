#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <memory>

class Knight: public Piece{
      public:
	void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;
	Knight(std::string n, std::string c, Position p);
		
	void check(Board* b, bool temporary = false) override {}                               
	bool checkMate(Board* b) override {} 
	void setMoved(bool b) override {} 
};

#endif
