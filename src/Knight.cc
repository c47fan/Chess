#include "Knight.h"
#include "Board.h"
#include "Square.h"
#include <iostream>
#include <string>

using namespace std;

Knight::Knight(string n, string c, Position p) : Piece(n, c, p) {}

void Knight::updateValidMoves(Board* b, Position king, bool temporary)
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
			if (i == row - 1 && j == col) {
				//check if space moving to is out of bounds
				if (i - 1 < 0 || j - 1 < 0) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i - 1, j - 1, this, true);
					} else {
						this->checkPieceMove(b, i - 1, j - 1, this);
					}

				}
				if (i - 1 < 0 || j + 1 > 7) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i - 1, j + 1, this, true);
					} else {
						this->checkPieceMove(b, i - 1, j + 1, this);
					}

				}
			} else if (i == row && j == col + 1) {
				if (i - 1 < 0 || j + 1 > 7) {
					// cout << "out of bounds" << endl;
				} else {
				
					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i - 1, j + 1, this, true);
					} else {
						this->checkPieceMove(b, i - 1, j + 1, this);
					}

				}
				if (i + 1 > 7 || j + 1 > 7) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i + 1, j + 1, this, true);
					} else {
						this->checkPieceMove(b, i + 1, j + 1, this);
					}

				}
			} else if (i == row + 1 && j == col) {
				if (i + 1 > 7 || j + 1 > 7) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i + 1, j + 1, this, true);
					} else {
						this->checkPieceMove(b, i + 1, j + 1, this);
					}

				}
				if (i + 1 > 7 || j - 1 < 0) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i + 1, j - 1, this, true);
					} else {
						this->checkPieceMove(b, i + 1, j - 1, this);
					}

				}
			} else if (i == row && j == col - 1) {
				if (i - 1 < 0 || j - 1 < 0) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i - 1, j - 1, this, true);
					} else {
						this->checkPieceMove(b, i - 1, j - 1, this);
					}

				}
				if (i + 1 > 7 || j - 1 < 0) {
					// cout << "out of bounds" << endl;
				} else {

					// check if the space is empty or has a piece, add moves accordingly
					if (temporary) {
						this->checkPieceMove(b, i + 1, j - 1, this, true);
					} else {
						this->checkPieceMove(b, i + 1, j - 1, this);
					}
				}
			}
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
}



