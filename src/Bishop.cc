#include "Bishop.h"
#include "Board.h"
#include "BoardView.h"
#include "Square.h"
#include <string>
#include <iostream>
#include <vector>
#include "King.h"

using namespace std;

Bishop::Bishop(string n, string c, Position p): Piece(n, c, p) {}

void Bishop::updateValidMoves(Board* b, Position king, bool temporary){

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

    int i, j;

    // check movement in the decrease row + increase col diagonal (northeast)
    for (i = row - 1, j = col + 1; i >= 0 && j <= 7; i--, j++) {
        // cout << "northeast" << endl;

        // check if the space is empty or has a piece, add moves accordingly
        bool blocked = false;
        if(temporary) {
            blocked = this->checkPieceMove(b, i, j, this, true);
        } else {
            blocked = this->checkPieceMove(b, i, j, this);
        }
        

        // path blocked, further moves are invalid
        if (blocked == true) {
            break;
        }
    }

    // check movement in the increase row + increase col diagonal (southeast)
    for (i = row + 1, j = col + 1; i <= 7 && j <= 7; i++, j++) {
        // cout << "southeast" << endl;

        // check if the space is empty or has a piece, add moves accordingly
        bool blocked = false;
        if(temporary) {
            blocked = this->checkPieceMove(b, i, j, this, true);
        } else {
            blocked = this->checkPieceMove(b, i, j, this);
        }

        // path blocked, further moves are invalid
        if (blocked == true) {
            break;
        }
    }

    // check movement in the increase row + decrease col diagonal (southwest)
    for (i = row + 1, j = col - 1; i <= 7 && j >= 0; i++, j--) {
        // cout << "southwest" << endl;

        // check if the space is empty or has a piece, add moves accordingly
        bool blocked = false;
        if(temporary) {
            blocked = this->checkPieceMove(b, i, j, this, true);
        } else {
            blocked = this->checkPieceMove(b, i, j, this);
        }

        // path blocked, further moves are invalid
        if (blocked == true) {
            break;
        }
    }

    // check movement in the decrease row + decrease col diagonal (northwest)
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        // cout << "northwest" << endl;

        // check if the space is empty or has a piece, add moves accordingly
        bool blocked = false;
        if(temporary) {
            blocked = this->checkPieceMove(b, i, j, this, true);
        } else {
            blocked = this->checkPieceMove(b, i, j, this);
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
}
