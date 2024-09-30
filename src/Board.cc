#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "Square.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Board::Board()
{
	vector<vector<shared_ptr<Square>>> gb (8, vector<shared_ptr<Square>>(8)); //initializing 2d vector of Square smart pointers

	int row = 0;
	for (int i = 0; i < 8; ++i) { //setting all the pointers to null
		row++;
		for (int j = 0; j < 8; ++j) {
			if (row % 2 == 0) {
				if (j % 2 == 0) {
					gb[i][j] = make_shared<Square> ( nullptr, "Black" );
				} else {
					gb[i][j] = make_shared<Square> ( nullptr, "White" );
				}
			} else {
				if (j % 2 == 0) {
					gb[i][j] = make_shared<Square> ( nullptr, "White" );
				} else {
					gb[i][j] = make_shared<Square> ( nullptr, "Black" );
				}
			}
		}
		this->gameBoard = gb;
	}
} //constructor, maybe by default is empty, but then you set it up automatically for a normal game?
// since we have to implement set as well, which would not want a preset board

void Board::defaultBoard()
{

	for (int i = 0; i < 8; i++) {
		Position pos1 { i, 1 };
		Position pos2 { i, 6 };
		shared_ptr<Pawn> pawnB = make_shared<Pawn> ( "Pawn", "Black", pos1 );
		shared_ptr<Pawn> pawnW = make_shared<Pawn> ("Pawn", "White", pos2);
		this->setSquare(1, i, pawnB);
		this->setSquare(6, i, pawnW);
		Position pos3 { i, 0 };
		Position pos4 { i, 7 };
		if (i == 0 || i == 7) {
			shared_ptr<Rook> rookB = make_shared<Rook> ("Rook", "Black", pos3);
			shared_ptr<Rook> rookW = make_shared<Rook> ("Rook", "White", pos4);
			this->setSquare(0, i, rookB);
			this->setSquare(7, i, rookW);
		}
		if (i == 1 || i == 6) {
			shared_ptr<Knight> knightB = make_shared<Knight> ("Knight", "Black", pos3);
			shared_ptr<Knight> knightW = make_shared<Knight> ("Knight", "White", pos4);
			this->setSquare(0, i, knightB);
			this->setSquare(7, i, knightW);
		}
		if (i == 2 || i == 5) {
			shared_ptr<Bishop> bishopB = make_shared<Bishop> ("Bishop", "Black", pos3);
			shared_ptr<Bishop> bishopW = make_shared<Bishop> ("Bishop", "White", pos4);
			this->setSquare(0, i, bishopB);
			this->setSquare(7, i, bishopW);
		}
		if (i == 3) {
			shared_ptr<Queen> queenB = make_shared<Queen> ("Queen", "Black", pos3);
			shared_ptr<Queen> queenW = make_shared<Queen> ("Queen", "White", pos4);
			this->setSquare(0, i, queenB);
			this->setSquare(7, i, queenW);
		}
		if (i == 4) {
			shared_ptr<King> kingB = make_shared<King> ("King", "Black", pos3);
			shared_ptr<King> kingW = make_shared<King> ("King", "White", pos4);
			this->setSquare(0, i, kingB);
			this->setSquare(7, i, kingW);
		}
	}
}

void Board::setSquare(int row, int col, std::shared_ptr<Piece>  p)
{
	removePiece(row, col);
	gameBoard[row][col]->setPiece(p);
}

void Board::removePiece(int row, int col)
{
	/*
	if(gameBoard[row][col]->getPiece() != nullptr){
		delete gameBoard[row][col]->getPiece();
	}*/
	gameBoard[row][col]->setPiece(nullptr);
}

void Board::addPiece(std::shared_ptr<Piece>  p, int row, int col)
{
	gameBoard[row][col]->setPiece(p);
}

Board::~Board()
{ //destructor
	
}


shared_ptr<Square> Board::getSquare(int row, int col) const
{
	return gameBoard[row][col];
}

bool Board::checkWin()
{
}

void Board::updateAllMoves(Position king)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::shared_ptr<Piece>  p = gameBoard[i][j]->getPiece();
			if (p != nullptr) {

				p->updateValidMoves(this, king, false);
			}
		}
	}
}

void Board::updateOppositeMoves(Position king, std::string colour) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::shared_ptr<Piece>  p = gameBoard[i][j]->getPiece();
			if (p != nullptr && p->getColour() != colour) {

				p->updateValidMoves(this, king, true);
			}
		}
	}
}

void Board::alertAllCheck(bool b, string colour)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::shared_ptr<Piece>  p = gameBoard[i][j]->getPiece();
			if (p != nullptr && p->getColour() == colour) {
				p->setInCheck(b);
			}
		}
	}
}

vector<std::shared_ptr<Piece> > Board::getWhiteKingAttackers() {
	return whiteKingAttackers;
}

void Board::setWhiteKingAttackers(std::shared_ptr<Piece>  attacker) {

	whiteKingAttackers.emplace_back(attacker);
}

vector<std::shared_ptr<Piece> > Board::getBlackKingAttackers() {
	return blackKingAttackers;
}

void Board::setBlackKingAttackers(std::shared_ptr<Piece>  attacker) {

	blackKingAttackers.emplace_back(attacker);
}

void Board::delWA(){
	whiteKingAttackers.clear();
}

void Board::delBA(){
	blackKingAttackers.clear();
}


void Board::movePiece(Position start, Position end) {

	// set the end square's piece pointer to the piece currently in start square
	gameBoard[end.getY()][end.getX()]->setPiece(gameBoard[start.getY()][start.getX()]->getPiece());

	// set start square's piece to pointer to nullptr
	gameBoard[start.getY()][start.getX()]->setPiece(nullptr);

	// change piece's position to end
	gameBoard[end.getY()][end.getX()]->getPiece()->setPosition(end.getX(), end.getY());
}


std::shared_ptr<Piece>  Board::findKing(string colour) {

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){

			std::shared_ptr<Piece> p = this->getSquare(i, j)->getPiece();

			if (p != nullptr && p->getName() == "King" && p->getColour() == colour) {
				return p;
			}
		}
	}
}


void Board::clearBoard() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			//delete gameBoard[i][j]->getPiece();
			gameBoard[i][j]->setPiece(nullptr);
		}
	}
}

bool Board::staleMate(string colour) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::shared_ptr<Piece> p = this->getSquare(i, j)->getPiece();

			if (p != nullptr && p->getColour() == colour && !p->getTotalMoves().empty()) {
				return false;
			}
		}
	}
	return true;
}
