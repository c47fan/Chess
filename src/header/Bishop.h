#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
#include <memory>

class Bishop: public Piece{
	public:
		void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;
		Bishop(std::string n, std::string c, Position p);

		void check(Board* b, bool temporary = false) override {}                 
		bool checkMate(Board* b) override {} 
		void setMoved(bool b) override {} 
};

#endif
