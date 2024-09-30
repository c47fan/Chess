#include "King.h"
#include "Board.h"
#include "BoardView.h"
#include "Square.h"
#include "Rook.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

King::King(string n, string c, Position p) : Piece(n, c, p), moved { false } {
	if(c == "White"){
		if(p.getX() != 4 || p.getY() != 7){
			moved = true;
		}
	} else{
		if(p.getX() != 4 || p.getY() != 0){
			moved = true;
		}
	}
}

King::~King(){}

bool isInVec(Piece* p, Position pos1){
	int size = p->getTotalMoves().size();
	for(int i = 0; i < size; i++){
		if(p->getTotalMoves().at(i).getX() == pos1.getX() && p->getTotalMoves().at(i).getY() == pos1.getY()){
			return true;
		}
	}
	return false;
}

// update the validMoves vector
void King::updateValidMoves(Board* b, Position king, bool temporary)
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

	int row = this->getPosition().getY();
	int col = this->getPosition().getX();

	for (int i = row - 1; i <= row + 1; i++) {

		for (int j = col - 1; j <= col + 1; j++) {

			// ignore square piece is currently on
			if (!(i == row && j == col)) {

				// check if (i, j) is OOB
				if (i < 0 || i > 7 || j < 0 || j > 7) {
					// cout << "out of bounds" << endl;
					continue;
				}

				if (temporary) {
					this->checkPieceMove(b, i, j, this, true);
				} else {
					this->checkPieceMove(b, i, j, this);
				}
			}
		}
	}
}

bool King::canCastle(Board* b, string leftright){
	if(this->getColour() == "White" && !this->getInCheck()){
		if(leftright == "Right"){
			std::shared_ptr<Piece> p =  b->getSquare(7, 7)->getPiece();
			if(p != nullptr && p->getName() == "Rook" && p->getColour() == this->getColour()){
				std::shared_ptr<Rook> r = static_pointer_cast<Rook>(p);
				if(!moved && !r->getMoved()){
					Position right1{5, 7};
					if(b->getSquare(7, 5)->getPiece() == nullptr){
						if(isInVec(this, right1)){
							this->checkPieceMove(b, 7, 6, this); 
							Position right2{6, 7};
							if(isInVec(this, right2)){
								return true;
							}
						}
					}
				}
			}
		} else{
			std::shared_ptr<Piece> p =  b->getSquare(7, 0)->getPiece();
			if(p != nullptr && p->getName() == "Rook" && p->getColour() == this->getColour()){
				std::shared_ptr<Rook> r = static_pointer_cast<Rook>(p);
				if(!moved && !r->getMoved()){
					Position left1{3, 7};
					if(b->getSquare(7, 3)->getPiece() == nullptr && b->getSquare(7, 1)->getPiece() == nullptr){
						if(isInVec(this, left1)){
							this->checkPieceMove(b, 7, 2, this);	
							Position left2{2, 7};
							if(isInVec(this, left2)){
								return true;
							}
						}
					}
				}
			}
		}
	}
	if(this->getColour() == "Black" && !this->getInCheck()){
		if(leftright == "Right"){
			std::shared_ptr<Piece> p =  b->getSquare(0, 7)->getPiece();
			if(p != nullptr && p->getName() == "Rook" && p->getColour() == this->getColour()){
				std::shared_ptr<Rook> r = static_pointer_cast<Rook>(p);
				if(!moved && !r->getMoved()){
					Position right1{5, 0};
					if(b->getSquare(0, 5)->getPiece() == nullptr){
						if(isInVec(this, right1)){
							this->checkPieceMove(b, 0, 6, this);
							Position right2{6, 0};
							if(isInVec(this, right2)){
								return true;
							}
						}
					}
				}
			}
		} else{
			shared_ptr<Piece> p = b->getSquare(0, 0)->getPiece();
			if(p != nullptr && p->getName() == "Rook" && p->getColour() == this->getColour()){
				std::shared_ptr<Rook> r = static_pointer_cast<Rook>(p);
				if(!moved && !r->getMoved()){
					Position left1{3, 0};
					if(b->getSquare(0, 3)->getPiece() == nullptr && b->getSquare(0, 1)->getPiece() == nullptr ){
						if(isInVec(this, left1)){
							this->checkPieceMove(b, 0, 2, this);
							Position left2{2, 0};
							if(isInVec(this, left2)){
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}


void King::check(Board* b, bool temporary) {

	// reseting inCheck to false
	b->alertAllCheck(false, this->getColour());

	// delete current white and black attackers
	if (this->getColour() == "White") {
		b->delWA();
	} else {
		b->delBA();
	}

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){

			// create the piece for the current square
			shared_ptr<Piece> p = b->getSquare(i, j)->getPiece();

			// if the square is not empty and the piece is of the opposite colour
			if(p != nullptr && p->getColour() != this->getColour()){

				vector<Position> cMoves;

				if(!temporary){
					// obtaining the capturing moves of the piece
					cMoves = p->getCapturingMoves();
				} else{
					cMoves = p->getTmpCapturingMoves();
				}

				int size = cMoves.size();

				for(int h = 0; h < size; h++){
					// cout << size << endl;
					// cout << p->getName() << ", " << p->getColour()  << endl;

					// if the current capturing move can capture the king
					if(cMoves[h].getX() == this->getPosition().getX() && cMoves[h].getY() == this->getPosition().getY()){

						// add the piece to the list of attackers checking the king
						if (this->getColour() == "White") {

							b->setWhiteKingAttackers(p);
							// cout << "white getAttackers size: " << b->getWhiteKingAttackers().size() << endl;

						} else {

							b->setBlackKingAttackers(p);
							// cout << "black getAttackers size: " << b->getBlackKingAttackers().size() << endl;
						}

						// setting inCheck for all pieces on the same team to true
						b->alertAllCheck(true, this->getColour());
					}
				}
			}
		}
	}
}

bool King::checkMate(Board* b) {

	// if no check, no checkmate
	if (!(this->getInCheck())) {

		return false;

	} else {

		// if the King King can move, return false
		if (!(this->getValidMoves().empty()) || !(this->getCapturingMoves().empty())) {

			// cout << "king can move" << endl;

			return false;

		} else {		// otherwise, check the number of attackers

			vector<shared_ptr<Piece>> attackers;
			if (this->getColour() == "White") {
				attackers = b->getWhiteKingAttackers();
			} else {
				attackers = b->getBlackKingAttackers();
			}

			// if there is more than 1 attacker, CHECKMATE
			if (attackers.size() > 1) {

				return true;

			} else {			// otherwise, if there is 1 attacker

				bool canAnyoneHelp = false;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {

						shared_ptr<Piece> p = b->getSquare(i,j)->getPiece();

						// find a friendly piece
						if (p != nullptr && p->getColour() == this->getColour()) {

							if (!(p->getValidMoves().empty()) || !(p->getCapturingMoves().empty())) {

								canAnyoneHelp = true;
								break;
							}
						}
					}
				}

				// check if any friendly piece has valid moves or captures to SAVE THE KING
				if (canAnyoneHelp) {

					return false;

				} else {		// otherwise, nothing can be done, the king is dead :(

					return true;
				}
			}
		}

	}



}

void King::setMoved(bool b) {
	moved = b;
}



