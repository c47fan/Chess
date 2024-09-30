#include "Player.h"
#include "King.h"
#include <algorithm>
#include <iostream>
#include <time.h>
#include <map>

using namespace std;

Player::Player(string c): colour{c}, score{0}, isComputer{false}, computerLevel{1} {}

Player::~Player(){};

string Player::getType() const{
    return type;
}

string Player::getColour() const{
    return colour;
}

float Player::getScore() const{
    return score;
}

void Player::setType(std::string t) {
    this->type = t;
}

void Player::setScore(float point) {
    this->score += point;
}

bool Player::getIsComputer() const {
    return isComputer;
}

void Player::setIsComputer(bool c) {
    this->isComputer = c;
}

int Player::getComputerLevel() const {
    return computerLevel;
}

void Player::setComputerLevel(int l) {
    this->computerLevel = l;
}

// void Player::printVec(vector<Position> positions) {
   
// }


vector<Position> pickRandomMove(vector<std::shared_ptr<Piece>> canMovePieces, string type) {
    vector<Position> positions;
    time_t timer;

    timer = time(NULL);
    srand(timer);

    // find the size of canMovePieces and generate a random number
    int sizePieces = canMovePieces.size();
    int randomPiece = rand() % sizePieces;

    // find a randomPiece in totalMoves (level 1)
    if (type == "any") {

        // add the original position
        positions.emplace_back(canMovePieces.at(randomPiece)->getPosition());

        // add the move position
        int randomMove = rand() % int(canMovePieces.at(randomPiece)->getTotalMoves().size());
        positions.emplace_back(canMovePieces.at(randomPiece)->getTotalMoves().at(randomMove));

    } else if (type == "capture") { //  find a randomPiece in capturingMoves (level 2 & level 3)

        // add the original position
        positions.emplace_back(canMovePieces.at(randomPiece)->getPosition());

        // add the move position
        int randomMove = rand() % int(canMovePieces.at(randomPiece)->getCapturingMoves().size());
        positions.emplace_back(canMovePieces.at(randomPiece)->getCapturingMoves().at(randomMove));

    } else if (type == "check") { // find a randomPiece in checkingMoves (level 2 & level 3)

        int size = canMovePieces.at(randomPiece)->getCheckingMoves().size();

        // add the original position
        positions.emplace_back(canMovePieces.at(randomPiece)->getPosition());

        // add the move position
        int randomMove = rand() % int(canMovePieces.at(randomPiece)->getCheckingMoves().size());
        positions.emplace_back(canMovePieces.at(randomPiece)->getCheckingMoves().at(randomMove));
    }

    return positions;
}



 vector<std::shared_ptr<Piece>> getAllPossibleMoves(Board *b, string colour) {
     vector<std::shared_ptr<Piece>> pieces;

    // iterate through the board and collect every friendly piece that has a non-empty total moves vector
    for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

            std::shared_ptr<Piece>p = b->getSquare(i, j)->getPiece();

            // if it's a friendly piece and has moves, add it to the pieces vector
            if (p != nullptr && p->getColour() == colour && !(p->getTotalMoves().empty())) {

                pieces.emplace_back(p);
            }
		}
	}
    return pieces;
}


 vector<std::shared_ptr<Piece>> getAllCapturingMoves(Board *b, string colour) {
     vector<std::shared_ptr<Piece>> pieces;

    // iterate through the board and collect every friendly piece that has a non-empty capturing moves vector
    for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

            std::shared_ptr<Piece>p = b->getSquare(i, j)->getPiece();

            // if it's a friendly piece and has capturing moves, add it to the pieces vector
            if (p != nullptr && p->getColour() == colour && !(p->getCapturingMoves().empty())) {

                pieces.emplace_back(p);
            }
		}
	}
    return pieces;
}



 vector<std::shared_ptr<Piece>> getAvoidCapMoves(Board *b, string colour) {

    vector<std::shared_ptr<Piece>> pieces;

    // iterate through the board to a friendly piece that has a non-empty total moves vector
    for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

            std::shared_ptr<Piece>p = b->getSquare(i, j)->getPiece();

            // if it's a friendly piece and has moves, check if it can be captured 
            if (p != nullptr && p->getColour() == colour && !(p->getTotalMoves().empty())) {

                int pX = p->getPosition().getX();
                int pY = p->getPosition().getY();

                // loop through the board and find all enemy pieces
                for (int l = 0; l < 8; ++l) {
                    for (int m = 0; m < 8; ++m) { 

                        std::shared_ptr<Piece>e = b->getSquare(l, m)->getPiece();

                        // if e is an enemy piece
                        if (e != nullptr && e->getColour() != colour) {

                            // if p position is in the enemy's capturing moves, add it to pieces
                            int sizeCapMoves = e->getCapturingMoves().size();

                            for (int n = 0; n < sizeCapMoves; n++) {
                                
                                if (pX == e->getCapturingMoves().at(n).getX() && pY == e->getCapturingMoves().at(n).getY()) {
                                    pieces.emplace_back(p);
                                    break;
                                }
                            }
                        }
                    }
                }  
            }
        }
	}
    return pieces;
}
    


vector<std::shared_ptr<Piece>> getAllCheckingMoves(Board *b, string colour) {
    vector<std::shared_ptr<Piece>> pieces;

    // iterate through the board and collect every friendly piece that has a non-empty total moves vector
    for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

            std::shared_ptr<Piece>p = b->getSquare(i, j)->getPiece();


            // if it's a friendly piece and has moves, check if they put the enemy king in check
            if (p != nullptr && p->getColour() == colour && !(p->getTotalMoves().empty())) {
                
                // clear the checking moves from the previous turn 
                if (p->getCheckingMoves().size() > 0) {
                    p->delTmpCheck();
                }

                int pX = p->getPosition().getX();
                int pY = p->getPosition().getY();

                int size = p->getTotalMoves().size();

                // cout << p->getTotalMoves().size() << endl;
                // loop through totalMoves
                for (int n = 0; n < size; n++) {

                    int moveX = p->getTotalMoves().at(n).getX();
                    int moveY = p->getTotalMoves().at(n).getY();

                    // cout << "moveX: " << moveX << endl;
                    // cout << "moveY: " << moveY << endl;

                    // move the piece temporarily to the new square
                    Position startPos = Position { pX, pY };
                    Position endPos = Position { moveX, moveY };

                    if (b->getSquare(endPos.getY(), endPos.getX())->getPiece() == nullptr) {

                        b->movePiece(startPos, endPos);

                        string oColour;
                        if (colour == "White") {
                            oColour = "Black";
                        } else {
                            oColour = "White";
                        }

                        // update valid moves on current colour
                        std::shared_ptr<Piece> king = b->findKing(colour);

                        b->updateOppositeMoves(king->getPosition(), oColour);

                        // check if the enemy King is in check using isKingInCheck on board
                        shared_ptr<King> k = static_pointer_cast<King>(b->findKing(oColour));
                        k->check(b, true);


                        // if the enemy King is in check
                        if (k->getInCheck()) {

                            // add pmove to tmpCheckingMoves of the piece
                            p->setCheckingMoves(endPos);

                            // if not already there, add to pieces
                            if (!(find(pieces.begin(), pieces.end(), p) != pieces.end())) {
                                pieces.emplace_back(p);
                            } 
                        }

                        // move the piece back to the original spot
                        b->movePiece(endPos, startPos);

                        // update valid moves back to the original
                        b->updateOppositeMoves(king->getPosition(), oColour);

                        // call check again on the original
                        k->check(b);

                    } else { // CAPTURING MOVE

                        std::shared_ptr<Piece> capturedPiece = b->getSquare(moveY, moveX)->getPiece();

                        b->movePiece(startPos, endPos);


                        string oColour;
                        if (colour == "White") {
                            oColour = "Black";
                        } else {
                            oColour = "White";
                        }

                        // update valid moves on current colour
                        std::shared_ptr<Piece> king = b->findKing(colour);

                        b->updateOppositeMoves(king->getPosition(), oColour);

                        // check if the enemy King is in check using isKingInCheck on board
                        shared_ptr<King> k = static_pointer_cast<King>(b->findKing(oColour));
                        k->check(b, true);


                        // if the enemy King is in check
                        if (k->getInCheck()) {

                            // add pmove to tmpCheckingMoves of the piece
                            p->setCheckingMoves(endPos);

                            // if not already there, add to pieces
                            if (!(find(pieces.begin(), pieces.end(), p) != pieces.end())) {
                                pieces.emplace_back(p);
                            } 
                        }

                        // move the piece back to the original spot
                        b->movePiece(endPos, startPos);

                        // add captured piece back to the board
                        b->getSquare(moveY, moveX)->setPiece(capturedPiece);

                        // update valid moves back to the original
                        b->updateOppositeMoves(king->getPosition(), oColour);

                        // call check again on the original
                        k->check(b);

                    }
                }
            }
		}
	}
    return pieces;
}


vector<Position> Player::computerLevel1(Board *b) {

    // get all pieces that can move
    vector<std::shared_ptr<Piece>> canMovePieces = getAllPossibleMoves(b, this->getColour());

    // pick a random piece and random move 
    vector<Position> randomMove = pickRandomMove(canMovePieces, "any");

    return randomMove;
   
}


vector<Position> Player::computerLevel2(Board *b) {

    // get all pieces that can check the enemy king
    vector<std::shared_ptr<Piece>> canCheckPieces = getAllCheckingMoves(b, this->getColour());

    // get all pieces that can capture 
    vector<std::shared_ptr<Piece>> canMovePieces = getAllCapturingMoves(b, this->getColour());

    vector<Position> randomMove;
    
    // if there are pieces that can check
    if (!canCheckPieces.empty()) {
        
        randomMove = pickRandomMove(canCheckPieces, "check");

        return randomMove;

    } else if (!canMovePieces.empty()) { // if there are pieces that can capture

        randomMove = pickRandomMove(canMovePieces, "capture");

        return randomMove;

    } else { // there are no pieces that can check and capture, default to computer 1
        vector<Position> computer1Move = computerLevel1(b);

        return computer1Move;
    }

}


vector<Position> Player::computerLevel3(Board *b) {
    
    // get all pieces that can avoid capture and capture the enemy at the same time
    vector<std::shared_ptr<Piece>> checkPieces = getAllCheckingMoves(b, this->getColour());
    vector<std::shared_ptr<Piece>> capPieces = getAllCapturingMoves(b, this->getColour());
    vector<std::shared_ptr<Piece>> avoidCapPieces = getAvoidCapMoves(b, this->getColour());
    vector<std::shared_ptr<Piece>> bothPieces;

    int sizeCanAvoid = avoidCapPieces.size();
    int sizeCanCap = capPieces.size();

    // find the intersection of capPieces and avoidCapPieces
    for (int i = 0; i < sizeCanAvoid; i++) {
        for (int j = 0; j < sizeCanCap; j++) {

            if (avoidCapPieces.at(i)->getPosition().getX() == capPieces.at(j)->getPosition().getX() 
                && avoidCapPieces.at(i)->getPosition().getY() == capPieces.at(j)->getPosition().getY()) {
            
                bothPieces.emplace_back(avoidCapPieces.at(i));
            }
        }
    }

    vector<Position> randomMove;

    // if there are pieces that can check the enemy king
    if (!checkPieces.empty()) {

        randomMove = pickRandomMove(checkPieces, "check"); 

    } else if (!bothPieces.empty()) {   // if there are pieces that can avoid and capture, pick a random capturing move

        randomMove = pickRandomMove(bothPieces, "capture");

    } else if (sizeCanAvoid != 0) { // if there are pieces that can avoid, pick a random move

        randomMove = pickRandomMove(avoidCapPieces, "any");

    } else { // default to computer 2 

        randomMove = computerLevel2(b);
    }

    return randomMove;
}
