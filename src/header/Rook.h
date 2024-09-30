#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
#include <memory>

class Rook: public Piece{
	bool moved;

	public:
		Rook(std::string n, std::string c, Position p);
		void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;
		
		void check(Board* b, bool temporary = false) override {}
		bool checkMate(Board* b) override {}
		void setMoved(bool b);
		bool getMoved() const;
};

#endif
