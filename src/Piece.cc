#include "Piece.h"
#include "King.h"
#include "Square.h"
#include "Board.h"
#include "BoardView.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;
void Piece::delV(){
	validMoves.clear();
}

void Piece::delC(){
	capturingMoves.clear();
}

void Piece::delT(){
	totalMoves.clear();
}

void Piece::delTmpCheck(){
    tmpCheckingMoves.clear();
}

vector<Position> Piece::getCheckingMoves() const {
    return tmpCheckingMoves;
}

void Piece::setCheckingMoves(Position p) {
    tmpCheckingMoves.emplace_back(p);
}

Piece::Piece(string n, string c, Position p): name{n}, colour{c}, position{p}, inCheck{false}{
}
Piece::~Piece(){}
bool Piece::canMoveTo(Position p){
}
bool Piece::canMove(){
}
string Piece::getName() const{
	return name;
}
void Piece::setName(string name) {
	this->name = name;
}
string Piece::getColour() const{
	return colour;
}
void Piece::setColour(string colour) {
	this->colour = colour;
}

Position Piece::getPosition() const{
	return position;
}

void Piece::setPosition(int x, int y) {
	position.setPos(x, y);
}

vector<Position> Piece::getValidMoves() const{
	return validMoves;
}

void Piece::setValidMoves(int x, int y) {

	Position emptySquare{y, x};
	validMoves.emplace_back(emptySquare);
}

vector<Position> Piece::getCapturingMoves() const{
	return capturingMoves;
}

void Piece::setCapturingMoves(int x, int y) {

	Position emptySquare{y, x};
	capturingMoves.emplace_back(emptySquare);
}

vector<Position> Piece::getTotalMoves() const{
	return totalMoves;
}

void Piece::setTotalMoves(int x, int y) {

	Position emptySquare{y, x};
	totalMoves.emplace_back(emptySquare);
}

void Piece::setInCheck(bool b){
	inCheck = b;
}
bool Piece::getInCheck() const{
	return inCheck;
}

void Piece::delTmpV(){
	tmpValidMoves.clear();
}
void Piece::delTmpC(){
	tmpCapturingMoves.clear();
}
void Piece::setTmpCapturingMoves(int x, int y){
	Position emptySquare{y, x};
	tmpCapturingMoves.emplace_back(emptySquare);
}
void Piece::setTmpValidMoves(int x, int y){
	Position emptySquare{y, x};
        tmpValidMoves.emplace_back(emptySquare);
}
std::vector<Position> Piece::getTmpCapturingMoves() const{
	return tmpCapturingMoves;
}
std::vector<Position> Piece::getTmpValidMoves() const{
	return tmpValidMoves;
}

vector<Position> Piece::getSquareAround()
{
	return squareAround;
}

void Piece::setSquareAround()
{
	int row = this->getPosition().getY();
	int col = this->getPosition().getX();

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if (i < 0 || i > 7 || j < 0 || j > 7) {
				continue;
			}
			Position emptySquare { j, i };
			this->getSquareAround().emplace_back(emptySquare);
		}
	}
}

bool Piece::checkSquareAround(Position p)
{
	vector<Position> squareAround;
	for (int i = 0; i < squareAround.size(); i++) {
		if (p.getX() == squareAround.at(i).getX() && p.getY() == squareAround.at(i).getY()) {
			return true;
		}
	}
	return false;
}

bool Piece::checkPieceMove(Board* b, int toRow, int toCol, Piece* p, bool temporary, bool enPassant) {


	// VALID BELOW:


	// check if (toRow, toCol) is empty
	if (b->getSquare(toRow, toCol)->getPiece() == nullptr) {
		// BoardView bv{b};
		// bv.displayBoard();
		// cout << "trying to get to" << toRow << ", " << toCol << endl;
		// cout << "rook empty square" << endl;

		if (!temporary) { //if the piece is not a temporary one...
			bool returnTrue = false;
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
				if(enPassant){
					returnTrue = true;
				}
			}

			// move the piece back to the original spot
			b->movePiece(endPos, startPos);

			// update Opposite Moves back to the original
			b->updateOppositeMoves(king->getPosition(), p->getColour());

			// call check again on the original
			k->check(b);
			if(enPassant && returnTrue){
				return true;
			}
			if(enPassant && !returnTrue){
				return false;
                        }
		} else{
			p->setTmpValidMoves(toRow, toCol);
		}
		
		// return false when direction is not blocked
		return false;



	// CAPTURE BELOW:


	} else { // there is a piece on (toRow, toCol)
		// cout << "there is a piece already" << endl;

		// check if the move will put the King in check

		if (b->getSquare(toRow, toCol)->getPiece()->getColour() != p->getColour()) {

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

		// return true when direction is blocked
		return true;
	}
}

bool Piece::checkPieceMove2(Board* b, int toRow, int toCol, shared_ptr<Piece> p, bool temporary, bool enPassant) {


	// VALID BELOW:


	// check if (toRow, toCol) is empty
	if (b->getSquare(toRow, toCol)->getPiece() == nullptr) {
		// BoardView bv{b};
		// bv.displayBoard();
		// cout << "trying to get to" << toRow << ", " << toCol << endl;
		// cout << "rook empty square" << endl;

		if (!temporary) { //if the piece is not a temporary one...
			bool returnTrue = false;
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
				if(enPassant){
					returnTrue = true;
				}
			}

			// move the piece back to the original spot
			b->movePiece(endPos, startPos);

			// update Opposite Moves back to the original
			b->updateOppositeMoves(king->getPosition(), p->getColour());

			// call check again on the original
			k->check(b);
			if(enPassant && returnTrue){
				return true;
			}
			if(enPassant && !returnTrue){
				return false;
                        }
		} else{
			p->setTmpValidMoves(toRow, toCol);
		}
		
		// return false when direction is not blocked
		return false;



	// CAPTURE BELOW:


	} else { // there is a piece on (toRow, toCol)
		// cout << "there is a piece already" << endl;

		// check if the move will put the King in check

		if (b->getSquare(toRow, toCol)->getPiece()->getColour() != p->getColour()) {

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

		// return true when direction is blocked
		return true;
	}
}

void Piece::saveTheKingMethod(vector<shared_ptr<Piece>> &attackers, Position king) {

	// if there is more than one attacker, piece cannot help the king
	int attackersSize = attackers.size();

	if (attackersSize > 1) {

		// there are no valid moves
		this->delV();
		this->delC();
		// this->delT();
		//cerr << "Multiple attackers, cannot defend" << endl;

	} else { // there is only one attacker
		// check if the piece can capture the attacker

		vector<Position> cMoves = this->getCapturingMoves();

		// delete existing capturing moves
		this->delC();

		shared_ptr<Piece> attacker = attackers.at(0);
		int cMovesSize = cMoves.size();
		for (int i = 0; i < cMovesSize; i++) {

			// if a capturing move is the same square as the attacker, add to saveTheKing
			if (cMoves.at(i).getX() == attacker->getPosition().getX() && cMoves.at(i).getY() == attacker->getPosition().getY()) {
				this->setCapturingMoves(cMoves.at(i).getY(), cMoves.at(i).getX());
			}
		}

		// if the attacker is a queen, rook, or bishop
		if (attacker->getName() == "Queen" || attacker->getName() == "Rook" || attacker->getName() == "Bishop") {

			vector<Position> saveTheKing;
			vector<Position> attackMoves = attacker->getTotalMoves();
			int steps = 0;
			int attackMovesSize = attackMoves.size();
			for (int i = 0; i < attackMovesSize; i++) {
				// finding how many steps away the attacker is from the king
				if (attackMoves.at(i).getX() == king.getX() && attackMoves.at(i).getY() == king.getY()) {
					steps = i;
					break;
				}
			}

			// cout << "steps: " << steps << endl;
			vector<Position> path;
			for (int k = steps - 1; k >= 0; k--) {
				// add positions to path
				path.emplace_back(attackMoves[k]);

				// position has reached the attacker
				if (this->checkSquareAround(attackMoves[k])) {
					break;
				}
			}

			// compare path with valid moves of the piece
			vector<Position> validMoves = this->getValidMoves();
			int validMovesSize = validMoves.size();
			int pathSize = path.size();
			for (int i = 0; i < validMovesSize; i++) {
				for (int j = 0; j < pathSize; j++) {

					// if the position belongs to both valid moves and is in the attacker's path, piece can block
					if (validMoves.at(i).getX() == path.at(j).getX() && validMoves.at(i).getY() == path.at(j).getY()) {
						saveTheKing.emplace_back(validMoves.at(i));
					}
				}
			}

			// replace validMoves with saveTheKing
			this->delV();
			// cout << "we are at the replace" << endl;
			int sizeSaveTheKing = saveTheKing.size();
			for (int i = 0; i < sizeSaveTheKing; i++) {
				this->setValidMoves(saveTheKing.at(i).getY(), saveTheKing.at(i).getX());
			}
		}
	}
}

bool Piece::checkTotalMoves(Position p) {
	int size = getTotalMoves().size();

	// check if the position is in totalMoves
	for (int i = 0; i < size; i++) {
		if (p.getX() == totalMoves.at(i).getX() && p.getY() == totalMoves.at(i).getY()) {
			return true;
		}
	}
	return false;
}




