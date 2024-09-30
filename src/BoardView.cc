#include "BoardView.h"
#include <iostream>
#include <sstream>
#include "Square.h"
#include "Piece.h"
#include "Board.h"

using namespace std;

void graphicalSquare(shared_ptr<Xwindow> window, int row, int col, string colour){
	if(colour == "White"){
		window->fillRectangle(col, row, 20, 20, Xwindow::White);
	} else{
		window->fillRectangle(col, row, 20, 20, Xwindow::Cyan);
	}
}

void printSquare(shared_ptr<Square> s, shared_ptr<Xwindow> window = nullptr, int row = 0, int col = 0, bool graphical = false, bool movePrint = false){
	if(s->getPiece() == nullptr){
		if(graphical){
			graphicalSquare(window, row, col, s->getColour());
		} else{
			if(s->getColour() == "White"){
				cout << " ";
			} else{
				cout << "+";
			}
		}
	} else{
		if(s->getPiece()->getName() == "Pawn"){
			if(graphical){
				graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "P");
				} else{
					window->drawString(col + 8, row + 13, "p");
				}
			} else{
				if(s->getPiece()->getColour() == "White"){
					cout << "P";
				} else{
					cout << "p";
				}
			}
		} else if(s->getPiece()->getName() == "Knight"){
			if(graphical){
				graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "N");
				} else{
					window->drawString(col + 8, row + 13, "n");
				}
			} else{
				if(s->getPiece()->getColour() == "White"){
					cout << "N";
				} else{
					cout << "n";
				}
			}
		} else if(s->getPiece()->getName() == "Bishop"){
			if(graphical){
					graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "B");
				} else{
					window->drawString(col + 8, row + 13, "b");
				}
			}else{
				if(s->getPiece()->getColour() == "White"){
					cout << "B";
				} else{
					cout << "b";
				}
			}
		} else if(s->getPiece()->getName() == "Rook"){
			if(graphical){
					graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "R");
				} else{
					window->drawString(col + 8, row + 13, "r");
				}
			} else{
				if(s->getPiece()->getColour() == "White"){
					cout << "R";
				} else{
					cout << "r";
				}
			}
		} else if(s->getPiece()->getName() == "Queen"){
			if(graphical){
					graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "Q");
				} else{
					window->drawString(col + 8, row + 13, "q");
				}
			} else{
				if(s->getPiece()->getColour() == "White"){
					cout << "Q";
				} else{
					cout << "q";
				}
			}
		} else if(s->getPiece()->getName() == "King"){
			if(graphical){
					graphicalSquare(window, row, col, s->getColour());
				if(s->getPiece()->getColour() == "White"){
					window->drawString(col + 8, row + 13, "K");
				} else{
					window->drawString(col + 8, row + 13, "k");
				}
			} else{
				if(s->getPiece()->getColour() == "White"){
					cout << "K";
				} else{
					cout << "k";
				}
			}
		} else{
			if(graphical){
				graphicalSquare(window, row, col, s->getColour());
			} else{
				if(s->getColour() == "White"){
					cout << " ";
				} else{
					cout << "+";
				}
			}
		}
	}
}

BoardView::BoardView(Board* b): board{b} {
	window = make_shared<Xwindow> (220, 220);
}


void BoardView::displayBoard(){
	int row = 1;
	cout << endl;
	cout << "    a b c d e f g h" << endl; //printing the column "names"}
	cout << "    _ _ _ _ _ _ _ _" << endl; //printing the column "names"}
	//cout << endl;
	for(int i = 0; i < 8; i++){
		cout << row << "  |"; //printing the row number
		row++;
		for(int j = 0; j < 8; j++){
			printSquare(board->getSquare(i, j));
			cout << "|";
		}
		cout << endl;
	}
cout << "    \u203E \u203E \u203E \u203E \u203E \u203E \u203E \u203E" << endl;
}

BoardView::~BoardView(){
	window = nullptr;
	board = nullptr;
}

void BoardView::displayGraphics() const{	
	window->drawString(38, 20, "a");
	window->drawString(58, 20, "b");
	window->drawString(78, 20, "c");
	window->drawString(98, 20, "d");
	window->drawString(118, 20, "e");
	window->drawString(138, 20, "f");
	window->drawString(158, 20, "g");
	window->drawString(178, 20, "h");
	window->fillRectangle(30, 29, 161, 1);
	window->fillRectangle(29, 29, 1, 162);
	int row = 30;
	for(int i = 0; i < 8; i++){
		stringstream ss;
		ss << i + 1;
		window->drawString(15, row + 13, ss.str());	
		int col = 30;
		for(int j = 0; j < 8; j++){
			printSquare(board->getSquare(i, j), window, row, col, true);
			col += 20;
		}
		row += 20;
	}
	window->fillRectangle(190, 30, 1, 161);
	window->fillRectangle(30, 190, 161, 1);
}

void BoardView::updateGraphics(Position from, Position to, bool two) const{
	int row1 = from.getY();
	int col1 = from.getX();
	printSquare(board->getSquare(row1, col1), window, row1*20+30, col1*20+30, true, true);
	printSquare(board->getSquare(row1, col1), window, row1*20+30, col1*20+30, true, true);

	if (two) {

		int row2 = to.getY();
		int col2 = to.getX();
		printSquare(board->getSquare(row2, col2), window, row2*20+30, col2*20+30, true, true);
		printSquare(board->getSquare(row2, col2), window, row2*20+30, col2*20+30, true, true);
	}
}
