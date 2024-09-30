#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include <memory>

class Piece;

class Square{
	std::shared_ptr<Piece> piece;
	std::string colour;
      public:
	Square(std::shared_ptr<Piece> p, std::string c);
	~Square();
	std::string getColour() const;
	std::shared_ptr<Piece> getPiece() const;
	Piece* getPiece2() const;
	void setPiece(std::shared_ptr<Piece> p);
};

#endif
