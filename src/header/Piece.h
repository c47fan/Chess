#ifndef PIECE_H
#define PIECE_H
#include "Position.h"
#include <string>
#include <vector>
#include <memory>

class Board;

class Piece{

	private:
		std::string name;
		std::string colour;
		Position position;
		bool inCheck;
		
		std::vector<Position> validMoves;
		std::vector<Position> capturingMoves;
		std::vector<Position> totalMoves;
		std::vector<Position> tmpValidMoves;
        std::vector<Position> tmpCapturingMoves;
		std::vector<Position> tmpCheckingMoves;
		std::vector<Position> squareAround;

    public:
		Piece(std::string n, std::string c, Position p);
		virtual ~Piece();
		void virtual updateValidMoves(Board* b, Position king, bool temporary = false) = 0;
		bool canMoveTo(Position p);
		bool canMove();

		std::string getName() const;
		std::string getColour() const;
		Position getPosition() const;
		bool getInCheck() const;
		std::vector<Position> getValidMoves() const;
		std::vector<Position> getCapturingMoves() const;
		std::vector<Position> getTotalMoves() const;
		std::vector<Position> getTmpCapturingMoves() const;
		std::vector<Position> getTmpValidMoves() const;
		std::vector<Position> getSquareAround();
		std::vector<Position> getCheckingMoves() const;
		
		void setName(std::string name);
		void setColour(std::string colour);
		void setPosition(int x, int y);
		void setInCheck(bool b);
		void setValidMoves(int x, int y);
		void setCapturingMoves(int x, int y);
		void setTotalMoves(int x, int y);
		void setTmpCapturingMoves(int x, int y);
		void setTmpValidMoves(int x, int y);
		void setSquareAround();
		void setCheckingMoves(Position p);

		void virtual check(Board* b, bool temporary = false) = 0;
		bool virtual checkMate(Board* b) = 0;
		void virtual setMoved(bool b) = 0;

		void delV();
		void delC();
		void delT();
		void delTmpV();
		void delTmpC();
		void delTmpCheck();

		bool checkSquareAround(Position p);
		bool checkPieceMove(Board*  b, int toRow, int toCol, Piece* p, bool temporary = false, bool enPassant = false);
		bool checkPieceMove2(Board*  b, int toRow, int toCol, std::shared_ptr<Piece> p, bool temporary = false, bool enPassant = false);
		void saveTheKingMethod(std::vector<std::shared_ptr<Piece>> &attackers, Position king);

		bool checkTotalMoves(Position p);
};

#endif
