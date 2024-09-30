#ifndef KING_H
#define KING_H
#include "Piece.h"
#include <string>
#include <vector>
#include <memory>

class King: public Piece{
    bool moved;
	public:
     	King(std::string n, std::string c, Position p);
		~King();
		void updateValidMoves(Board* b, Position king = Position{0, 0}, bool temporary = false) override;

		void check(Board* b, bool temporary = false) override;
		bool checkMate(Board* b) override;
		void setMoved(bool b) override;
		bool canCastle(Board* b, std::string leftright);
};

#endif
