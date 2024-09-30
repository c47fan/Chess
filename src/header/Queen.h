#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"
#include <memory>

class Queen: public Piece{
    public:
		void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;
		Queen(std::string n, std::string c, Position p);
		
		void check(Board* b, bool temporary = false) override {}                       
		bool checkMate(Board* b) override {} 
		void setMoved(bool b) override {} 
};

#endif
