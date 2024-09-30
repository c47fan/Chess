#include "Pawn.h"
#include "Board.h"
#include "Square.h"
#include "King.h"
#include <string>
#include <iostream>

using namespace std;

Pawn::Pawn(string n, string c, Position p): Piece(n, c, p), moved{true} {

    // if it's a White pawn
    if (c == "White") {

        // if it's in the 6th row, it hasn't moved
        if (p.getY() == 6) {
            moved = false;
        }

    } else {           // if it's a Black pawn

        // if it's in the 2nd row, it hasn't moved
        if (p.getY() == 1) {
            moved = false;
        }
    }
}

void checkPawnValidMoves(Board* b, int toRow, int toCol, Piece* p, bool temporary = false) {

    if (!temporary) { //if the piece is not a temporary one...

        // check if the move will put the King in check

        // move the piece to toRow, toCol
        Position startPos = Position { p->getPosition().getX(), p->getPosition().getY() };
        Position endPos = Position { toCol, toRow };
        b->movePiece(startPos, endPos);

        // update valid moves on opposite colour
        shared_ptr<Piece> king = b->findKing(p->getColour());

        // update Opposite Capturing Moves
        b->updateOppositeMoves(king->getPosition(), p->getColour());

        // check if the King is in check using isKingInCheck on board
        shared_ptr<King> k = static_pointer_cast<King>(b->findKing(p->getColour()));
        k->check(b, true);

        // if the King isn't in check
        if (!k->getInCheck()) {

            // add the move to valid + total moves
            p->setValidMoves(toRow, toCol);
            p->setTotalMoves(toRow, toCol);
        }

        // move the piece back to the original spot
        b->movePiece(endPos, startPos);

        // update Opposite Moves back to the original
        b->updateOppositeMoves(king->getPosition(), p->getColour());

        // call check again on the original
        k->check(b);

    } else{
        p->setTmpValidMoves(toRow, toCol);
    }
}

void checkPawnCapturingMoves(Board*  b, int toRow, int toCol, Piece* p, bool temporary = false) {

    if (!temporary) { //if the piece is not a temporary one...

            // check if the move will put the King in check

            // save the piece being captured
            shared_ptr<Piece> capturedPiece = b->getSquare(toRow, toCol)->getPiece();

            // move the piece to toRow, toCol
            Position startPos = Position { p->getPosition().getX(), p->getPosition().getY() };
            Position endPos = Position { toCol, toRow };
            b->movePiece(startPos, endPos);

            // update valid moves on opposite colour
            shared_ptr<Piece> king = b->findKing(p->getColour());

            // update Opposite Capturing Moves
            b->updateOppositeMoves(king->getPosition(), p->getColour());

            // check if the King is in check using isKingInCheck on board
            shared_ptr<King> k = static_pointer_cast<King>(b->findKing(p->getColour()));
            k->check(b, true);

            // if the King isn't in check
            if (!k->getInCheck()) {

                // add the move to valid + total moves
                p->setCapturingMoves(toRow, toCol);
                p->setTotalMoves(toRow, toCol);
            }

            // move the piece back to the original spot
            b->movePiece(endPos, startPos);

            // add captured piece back to the board
            b->getSquare(toRow, toCol)->setPiece(capturedPiece);

            // update Opposite Moves back to the original
            b->updateOppositeMoves(king->getPosition(), p->getColour());

            // call check again on the original
            k->check(b);

        } else{
            p->setTmpCapturingMoves(toRow, toCol);
        }
}

void Pawn::updateValidMoves(Board* b, Position king, bool temporary){

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
    int y = this->getPosition().getY();
    int x = this->getPosition().getX();

    // modifier variables for direction
    int mod1 = 1;
    int mod2 = 2;

    // if it's a White pawn, the modifiers must be negative
    if (this->getColour() == "White") {
        mod1 *= -1;
        mod2 *= -1;
    }

    // find valid moves:

    // a pawn only has valid moves if there is no piece directly in front of it + not OOB
    if (y + mod1 >= 0 && y + mod1 <= 7 && b->getSquare(y + mod1, x)->getPiece() == nullptr) {

        // send off to check for check
        if (temporary) {
            checkPawnValidMoves(b, y + mod1, x, this, true);
        } else {
            checkPawnValidMoves(b, y + mod1, x, this);
        }

        // if it has not moved, it can also potentially move 2 squares (if there's no piece + not OOB)
        if (moved == false && y + mod2 >= 0 && y + mod2 <= 7  && b->getSquare(y + mod2, x)->getPiece() == nullptr) {
   
            // send off to check for check
            if (temporary) {
                checkPawnValidMoves(b, y + mod2, x, this, true);
            } else {
                checkPawnValidMoves(b, y + mod2, x, this);
            }
        }
    }

    // find capturing moves:
    
    // if there's a piece diagonal right/forward + not OOB
    if (y + mod1 >= 0 && y + mod1 <= 7 && x + 1 <= 7 && b->getSquare(y + mod1, x + 1)->getPiece() != nullptr) {

        // if the piece is the opposite colour, capture
        if (b->getSquare(y + mod1, x + 1)->getPiece()->getColour() != this->getColour()) {
            
            // send off to check for check
            if (temporary) {
                checkPawnCapturingMoves(b, y + mod1, x + 1, this, true);
            } else {
                checkPawnCapturingMoves(b, y + mod1, x + 1, this);
            }
        }
    }

    // if there's a piece diagonal left/forward + not OOB
    if (y + mod1 >= 0 && y + mod1 <= 7 && x - 1 >= 0 && b->getSquare(y + mod1, x - 1)->getPiece() != nullptr) {

        // if the piece is the opposite colour, capture
        if (b->getSquare(y + mod1, x - 1)->getPiece()->getColour() != this->getColour()) {
            
            // send off to check for check
            if (temporary) {
                checkPawnCapturingMoves(b, y + mod1, x - 1, this, true);
            } else {
                checkPawnCapturingMoves(b, y + mod1, x - 1, this);
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

void Pawn::setMoved(bool b) {
    moved = b;
}

bool end(){};

