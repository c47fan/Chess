#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include <memory>
#include "Position.h"

class Piece;
class Square;

class Board{
	//Square*** gameBoard;
	std::vector<std::vector<std::shared_ptr<Square>>> gameBoard;
	std::vector<std::shared_ptr<Piece>> whiteKingAttackers; 
	std::vector<std::shared_ptr<Piece>> blackKingAttackers; 

    public:
		Board();
		~Board();
		void defaultBoard();
		bool checkWin();
		std::shared_ptr<Square> getSquare(int row, int col) const;
		void setSquare(int row, int col, std::shared_ptr<Piece> p);
		void removePiece(int row, int col);
		void addPiece(std::shared_ptr<Piece> p, int row, int col);

		void updateAllMoves(Position king);
		void updateOppositeMoves(Position king, std::string colour);
		void alertAllCheck(bool b, std::string colour);
		void clearBoard();


		std::vector<std::shared_ptr<Piece> > getWhiteKingAttackers();
		void setWhiteKingAttackers(std::shared_ptr<Piece> attacker);
		std::vector<std::shared_ptr<Piece> > getBlackKingAttackers();
		void setBlackKingAttackers(std::shared_ptr<Piece> attacker);
		void delWA();
		void delBA();

		void movePiece(Position start, Position end);
		std::shared_ptr<Piece> findKing(std::string colour);

		bool staleMate(std::string colour);
};

#endif
