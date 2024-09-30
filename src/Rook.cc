#include "Rook.h"
#include "Board.h"
#include "BoardView.h"
#include "Square.h"
#include <iostream>
#include <string>
#include <vector>
#include "King.h"

using namespace std;

Rook::Rook(string n, string c, Position p)
	: Piece(n, c, p)
	  , moved { false }
{
	if(c == "White"){
		if(p.getY() != 7 || (p.getX() != 7 && p.getX() != 0)){
			moved = true;
		}
	} else{
		if(p.getY() != 0 || (p.getX() != 7 && p.getX() != 0)){
                        moved = true;
                }
	}
}

bool Rook::getMoved() const{
	return moved;
}

void Rook::updateValidMoves(Board* b, Position king, bool temporary)
{

	// clear previous valid and capturing moves
	if (!temporary) {
		this->delV();
		this->delC();
		this->delT();
	} else{
		this->delTmpV();
		this->delTmpC();
	}

	// get the coordinates
	int row = this->getPosition().getY();
	int col = this->getPosition().getX();

	// check movement in the same row, increasing col direction
	for (int i = col + 1; i <= 7; i++) {
		// cout << "col++" << endl;

		// check if the space is empty or has a piece, add moves accordingly
		bool blocked = false;
		if (temporary) {
			blocked = this->checkPieceMove(b, row, i, this, true);
		} else {
			blocked = this->checkPieceMove(b, row, i, this);
		}
		// path blocked, further moves are invalid
		if (blocked == true) {
			break;
		}
	}

	// check movement in the same row, decreasing col direction
	for (int i = col - 1; i >= 0; i--) {
		// cout << "col--" << endl;

		// check if the space is empty or has a piece, add moves accordingly
		bool blocked = false;
		if (temporary) {
			blocked = this->checkPieceMove(b, row, i, this, true);
		} else {
			blocked = this->checkPieceMove(b, row, i, this);
		}
		// path blocked, further moves are invalid
		if (blocked == true) {
			break;
		}
	}

	// check movement in the same col, increasing row direction
	for (int i = row + 1; i <= 7; i++) {
		// cout << "row++" << endl;

		// check if the space is empty or has a piece, add moves accordingly
		bool blocked = false;
		if(temporary){
			blocked = this->checkPieceMove(b, i, col, this, true);
		} else{
			blocked = this->checkPieceMove(b, i, col, this);
		}
		// path blocked, further moves are invalid
		if (blocked == true) {
			break;
		}
	}

	// check movement in the same col, decreasing row direction
	for (int i = row - 1; i >= 0; i--) {
		// cout << "row--" << endl;

		// check if the space is empty or has a piece, add moves accordingly
		bool blocked = false;
		if(temporary){
			blocked = this->checkPieceMove(b, i, col, this, true);
		} else{
			blocked = this->checkPieceMove(b, i, col, this);
		}
		// path blocked, further moves are invalid
		if (blocked == true) {
			break;
		}
	}

	// if inCheck is true for the piece's team's king
	if (this->getInCheck()) {

		// set correct attackers for this piece
		vector<shared_ptr<Piece>> attackers;

		if (this->getColour() == "White") {
			attackers = b->getWhiteKingAttackers();
		} else {
			attackers = b->getBlackKingAttackers();
		}
		
		this->saveTheKingMethod(attackers, king);
	}

	//cout << "rook valid moves size: " << this->getValidMoves().size() << endl;
}

void Rook::setMoved(bool b) {
    moved = b;
}
