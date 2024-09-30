#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
#include <memory>

class Pawn: public Piece{
	bool moved;
    
	public:
        	Pawn(std::string n, std::string c, Position p);
		~Pawn(){}
		void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;

		void check(Board* b, bool temporary = false) override {}         
		bool checkMate(Board* b) override {}  
		void setMoved(bool b) override;
};

#endif
