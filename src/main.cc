#include "Bishop.h"
#include "Board.h"
#include "BoardView.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Position.h"
#include "Queen.h"
#include "Rook.h"
#include "Square.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

// checks that the type of player input was valid
bool isValidPlayer(string p)
{
	if (p == "human" || p == "computer1" || p == "computer2" || p == "computer3" || p == "computer4") {
		return true;
	} else {
		return false;
	}
}

// prints the available commands for the main command interpreter
void printCommands()
{

	cout << "------------------------------------------" << endl;
	cout << "game <white player> <black player>" << endl;
	cout << "resign" << endl;
	cout << "move <origin square> <destination square>" << endl;
	cout << "setup" << endl;
	cout << "------------------------------------------" << endl;
}

// prints the commands for setup mode
void printSetupCommands()
{

	cout << "------------------------------------------" << endl;
	cout << "+ <piece> <square>" << endl;
	cout << "- <square>" << endl;
	cout << "= <colour>" << endl;
	cout << "done" << endl;
	cout << "------------------------------------------" << endl;
}

// checks if the given square is valid
bool isValidSquare(string s)
{

	// the square must be 2 characters long
	if (s.size() != 2) {
		return false;
	}

	// the first character of the square must be a letter from a-h inclusive
	if (!('a' <= s[0] && s[0] <= 'h')) {
		return false;
	}

	// the second character of the square must be a number from 1-8 inclusive
	if (!('1' <= s[1] && s[1] <= '8')) {
		return false;
	}

	return true;
}

// checks if the given piece is valid
bool isValidPiece(string s)
{

	// the piece must be one of rnbkqpRNBKQP
	if (s == "p" || s == "P") {
		return true;

	} else if (s == "r" || s == "R") {
		return true;

	} else if (s == "n" || s == "N") {
		return true;

	} else if (s == "b" || s == "B") {
		return true;

	} else if (s == "k" || s == "K") {
		return true;

	} else if (s == "q" || s == "Q") {
		return true;

	} else {
		return false;
	}
}

// converts a string location to coordinations
Position convertCoords(string c)
{

	Position p = Position { 0, 0 };

	// find column -- a[97]
	int x = int(char(c[0]) - 'a');

	// find row
	int y = int(c[1] - '1');

	p.setPos(x, y);

	return p;
}

// make Piece depending on string
shared_ptr<Piece> makePiece(string input, Position coords)
{

	if (input == "p") {
		return make_shared<Pawn> ( "Pawn", "Black", coords );

	} else if (input == "P") {
		return make_shared<Pawn> ( "Pawn", "White", coords );

	} else if (input == "r") {
		return make_shared<Rook> ( "Rook", "Black", coords );

	} else if (input == "R") {
		return make_shared<Rook> ( "Rook", "White", coords );

	} else if (input == "n") {
		return make_shared<Knight> ( "Knight", "Black", coords );

	} else if (input == "N") {
		return make_shared<Knight> ( "Knight", "White", coords );

	} else if (input == "b") {
		return make_shared<Bishop> ( "Bishop", "Black", coords );

	} else if (input == "B") {
		return make_shared<Bishop> ( "Bishop", "White", coords );

	} else if (input == "q") {
		return make_shared<Queen> ( "Queen", "Black", coords );

	} else if (input == "Q") {
		return make_shared<Queen> ( "Queen", "White", coords );

	} else if (input == "k") {
		return make_shared<King> ( "King", "Black", coords );

	} else if (input == "K") {
		return make_shared<King> ( "King", "White", coords );
	}
}

// get a piece's display name
string getDisplayName(string piece, string colour)
{

	if (piece == "Knight") {
		if (colour == "Black") {
			return "n";
		} else {
			return "N";
		}
	}

	if (colour == "Black") {
		return string(1, tolower(piece[0]));
	} else {
		return string(1, piece[0]);
	}
}

void setPieceCount(map<string, int> &numPieces, int count) {

	numPieces["p"] = count;
	numPieces["P"] = count;
	numPieces["r"] = count;
	numPieces["R"] = count;
	numPieces["n"] = count;
	numPieces["N"] = count;
	numPieces["b"] = count;
	numPieces["B"] = count;
	numPieces["k"] = count;
	numPieces["K"] = count;
	numPieces["q"] = count;
	numPieces["Q"] = count;
}



int main()
{
	// create an empty board
	Board b {};
	BoardView bv { &b };

	// create players
	Player p1 = Player { "White" };
	Player p2 = Player { "Black" };

	// create a new game
	Game g = Game{&b, &p1, &p2};

	// create map for number of pieces in setup mode, initialize to 0
	map<string, int> numPieces;
	setPieceCount(numPieces, 0);

	// std::cout << "super lame main function :)" << std::endl;
	cout << "Welcome to chess! Enter <c> for a list of commands." << endl;

	// string variables
	string command;

	// setup mode indicator
	bool setupUsed = false;

	bool movedPawnTwice = false;

	Position pawnShadow{0, 0};

	// read in all values from input until Ctrl-D
	while (cin >> command) {

		// if Ctrl-D is pressed, break out of the loop
		if (cin.eof()) {
			break;
		}

		// c command
		if (command == "c") {

			printCommands();

		} else if (command == "game") { // game command

			// create and read in players
			string player1;
			string player2;
			cin >> player1;
			cin >> player2;

			// if player1 or player2 isn't valid, tell the user and don't do anything
			// **FOR LATER:** add computer[1-4] to this
			if (!(isValidPlayer(player1) && isValidPlayer(player2))) {

				cout << "Invalid player(s), please try again." << endl;

			} else { // otherwise, assign player types

				g.getPlayer("White")->setType(player1);
				g.getPlayer("Black")->setType(player2);

				g.setInProgress(true);

				// clear the board if set
				if (!setupUsed) {

					b.clearBoard();
					b.defaultBoard(); // set the default piece configuration

					// update moves from last turn
					b.updateAllMoves(b.findKing(g.getTurn())->getPosition());

				} else { // use the board edited in setup

					setupUsed = false;

					// find the non-turn king
					string kColour;
					if (g.getTurn() == "White") {
						kColour = "Black";
					} else {
						kColour = "White";
					}

					// update moves from last turn
					b.updateAllMoves(b.findKing(g.getTurn())->getPosition());

					// update the King in question
					shared_ptr<King> ck = static_pointer_cast<King>(b.findKing(g.getTurn()));
					ck->updateValidMoves(&b, ck->getPosition(), false);

					// if there is a stalemate, end the game and update score
					if (!(ck->getInCheck()) && b.staleMate(g.getTurn())) {
						cout << "Stalemate!" << endl;

						g.endGame("SARAH!TOMMY!CATHY!");
						setPieceCount(numPieces, 0);

						continue;
					}

					// if this move causes the opposite king to be in checkmate
					if (ck->checkMate(&b)) {
						cout << "Checkmate! " << kColour << " wins!" << endl;

						g.endGame(kColour);
						setPieceCount(numPieces, 0);

						continue;
					}
				}

				// setup computers if necessary:

				// set player 1 computer settings if necessary
				if (player1[0] == 'c') {

					p1.setIsComputer(true);
					p1.setComputerLevel(int(player1[8] - '0'));
				}

				// set player 2 computer settings if necessary
				if (player2[0] == 'c') {

					p2.setIsComputer(true);
					p2.setComputerLevel(int(player2[8] - '0'));
				}

				bv.displayBoard();
				bv.displayGraphics();
				cout << "The game has started." << endl;
				cout << "It is " << g.getTurn() << "'s turn." << endl;

				// if the currnt king is in check, say so
				if (b.findKing(g.getTurn())->getInCheck()) {
					cout << g.getTurn() << " king is in check! " << endl;
				}
			}

		} else if (command == "resign") { // resign command

			if (g.getInProgress()) {

				// give a point to the non-current-turn player
				if (g.getTurn() == "White") {
					cout << "White has resigned, Black wins!" << endl;
					g.endGame("Black");
					setPieceCount(numPieces, 0);

				} else {
					cout << "Black has resigned, White wins!" << endl;
					g.endGame("White");
					setPieceCount(numPieces, 0);
				}

			} else {
				cout << "Resign not available when game is not in progress" << endl;
			}


		} else if (command == "move") { // move command

			// create
			string from;
			string to;

			//it's a human's turn, read input
			if (!(g.getPlayer(g.getTurn())->getIsComputer())) {

				cin >> from;
				cin >> to;
			} else {
				from = "a1";
				to = "a2";
			}

			// if both squares are valid (not equal and on the board)
			if (from != to && isValidSquare(from) && isValidSquare(to) && g.getInProgress()) {

				b.updateAllMoves(b.findKing(g.getTurn())->getPosition());

				Position orig{0, 0};
				Position move{0, 0};

				// if it's a human
				if (!(g.getPlayer(g.getTurn())->getIsComputer())) {

					orig = convertCoords(from);
					move = convertCoords(to);

				} else {		// otherwise, it's a computer

					vector<Position> computerMove;
					int compLevel = g.getPlayer(g.getTurn())->getComputerLevel();

					// if level 1
					if (compLevel == 1) {
						computerMove = g.getPlayer(g.getTurn())->computerLevel1(&b);

					} else if (compLevel == 2) {
						computerMove = g.getPlayer(g.getTurn())->computerLevel2(&b);

					} else if (compLevel == 3) {
						computerMove = g.getPlayer(g.getTurn())->computerLevel3(&b);

					}

					orig = computerMove.at(0);
					move = computerMove.at(1);
				}

				//cout << "origX: " << orig.getX() << endl;


				shared_ptr<Piece> p = b.getSquare(orig.getY(), orig.getX())->getPiece();

				if (p == nullptr) {
					cout << "There is no piece at " << from << "." << endl;
				} else if(p->getColour() != g.getTurn()){
					cout << "You cannot move your opponents pieces." << endl;
				} else {
					int moveToRow = move.getY();
					int moveToCol = move.getX();
					int origRow = orig.getY();
					int origCol = orig.getX();
					shared_ptr<Piece> pieceMove = b.getSquare(moveToRow, moveToCol)->getPiece();
					shared_ptr<Piece> pieceOrig = b.getSquare(origRow, origCol)->getPiece();
					Piece* pieceOrig2 = b.getSquare(origRow, origCol)->getPiece2();
					if(pieceOrig->getName() == "King" && pieceOrig->getColour() == "White" && moveToRow == 7){
						if(moveToCol == 2 && static_pointer_cast<King>(pieceOrig)->canCastle(&b, "Left")){

							Position origRook{0, 7};
							Position moveRook{3, 7};
							b.movePiece(origRook, moveRook);
							cout << "White has castled!" << endl;
						}
						if(moveToCol == 6 && static_pointer_cast<King>(pieceOrig)->canCastle(&b, "Right")){
							Position origRook{7, 7};
							Position moveRook{5, 7};
							b.movePiece(origRook, moveRook);
							cout << "White has castled!" << endl;
						}
					}
					if(pieceOrig->getName() == "King" && pieceOrig->getColour() == "Black" && moveToRow == 0){
						if(moveToCol == 2 && static_pointer_cast<King>(pieceOrig)->canCastle(&b, "Left")){
							Position origRook{0, 0};
							Position moveRook{3, 0};
							b.movePiece(origRook, moveRook);
							cout << "Black has castled!" << endl;
						}
						if(moveToCol == 6 && static_pointer_cast<King>(pieceOrig)->canCastle(&b, "Right")){
							Position origRook{7, 0};
							Position moveRook{5, 0};
							b.movePiece(origRook, moveRook);
							cout << "Black has castled!" << endl;
						}
					}

					bool enPassantBypass = false;
					if(movedPawnTwice && pawnShadow.getX() == moveToCol && pawnShadow.getY() == moveToRow && pieceOrig->checkPieceMove(&b, moveToRow, moveToCol, pieceOrig2, false, true)){
						enPassantBypass = true;
						if(pieceOrig->getColour() == "White"){
							b.removePiece(moveToRow + 1, moveToCol);
						}
						if(pieceOrig->getColour() == "Black"){
							b.removePiece(moveToRow - 1, moveToCol);
						}
					}


					// check if the move can be made for the piece
					if (p->checkTotalMoves(move)) {
						string kColour;
						if (g.getTurn() == "White") {
								kColour = "Black";
						} else {
								kColour = "White";
						}
						bool shouldMove = true;
						if(pieceOrig->getName() == "Pawn" && abs(moveToRow - origRow) == 2){
							movedPawnTwice = true;
							if(pieceOrig->getColour() == "White"){
								pawnShadow = Position{moveToCol, moveToRow + 1};
							}
							if(pieceOrig->getColour() == "Black"){
								pawnShadow = Position{moveToCol, moveToRow - 1};
							}
						} else{
							movedPawnTwice = false;
							pawnShadow = Position{0, 0};
						}

						if (pieceMove != nullptr) {
							cout << pieceOrig->getColour() << " " << pieceOrig->getName() << " captured " << pieceMove->getColour() << " " << pieceMove->getName() << "!" << endl;
							b.removePiece(moveToRow, moveToCol);
						}

						if (enPassantBypass){
							cout << pieceOrig->getColour() << " " << pieceOrig->getName() << " captured " << kColour << " Pawn via en passant!" << endl;
						}

						if (p->getName() == "Pawn" || p->getName() == "King" || p->getName() == "Rook") {
							p->setMoved(true);
						}

						if(pieceOrig->getName() == "Pawn" && pieceOrig->getColour() == "White" && moveToRow == 0){
							cout << "Please enter a piece to promote your Pawn to." << endl;
							string promP;

							while(1) {

								if (!g.getPlayer(g.getTurn())->getIsComputer()) {

									cin >> promP;

								} else {
									promP = "Q";
								}

								if(isValidPiece(promP) && promP != "K" && promP != "k" && promP != "r"
										&& promP != "n" && promP != "b" && promP != "q" && promP != "p"
										&& promP != "P"){
									Position newPos{moveToCol, moveToRow};
									b.removePiece(origRow, origCol);
									b.addPiece(makePiece(promP, newPos), moveToRow, moveToCol);
									shouldMove = false;
									cout << "The pawn has been promoted to a: " << b.getSquare(moveToRow, moveToCol)->getPiece()->getName() << endl;
									p = b.getSquare(moveToRow, moveToCol)->getPiece();
									break;

								} else{
									cerr << "That is not a valid piece to promote to." << endl;
								}

							}

						} else if(pieceOrig->getName() == "Pawn" && pieceOrig->getColour() == "Black" && moveToRow == 7){

							cout << "Please enter a piece to promote your Pawn to." << endl;
							string promP;

							while (1) {

								if (!g.getPlayer(g.getTurn())->getIsComputer()) {

									cin >> promP;

								} else {
									promP = "q";
								}

								if(isValidPiece(promP) && promP != "K" && promP != "k" && promP != "R"
										&& promP != "N" && promP != "B" && promP != "Q" && promP != "p"
										&& promP != "P"){
									Position newPos{moveToCol, moveToRow};
									b.removePiece(origRow, origCol);
									b.addPiece(makePiece(promP, newPos), moveToRow, moveToCol);
									shouldMove = false;
									cout << "The pawn has been promoted to a: " << b.getSquare(moveToRow, moveToCol)->getPiece()->getName() << endl;
									p = b.getSquare(moveToRow, moveToCol)->getPiece();
									break;

								} else{
									cerr << "That is not a valid piece to promote to." << endl;
								}
							}
						}

						if(shouldMove){
							// move the piece
							b.movePiece(orig, move);

						}

						// display the board
						bv.displayBoard();
						bv.updateGraphics(orig, move);

						// update the moves based on the opposite king
						b.updateAllMoves(b.findKing(kColour)->getPosition());

						// update the King in question
						shared_ptr<King> ck = static_pointer_cast<King>(b.findKing(kColour));
						ck->updateValidMoves(&b, ck->getPosition(), false);

						// if there is a stalemate, end the game and update score
						if (!(ck->getInCheck()) && b.staleMate(kColour)) {
							cout << "Stalemate!" << endl;

							g.endGame("SARAH!TOMMY!CATHY!");
							setPieceCount(numPieces, 0);

							continue;
						}

						// if this move causes the opposite king to be in checkmate
						if (b.findKing(kColour)->checkMate(&b)) {
							cout << "Checkmate! " << g.getTurn() << " wins!" << endl;

							g.endGame(g.getTurn());
							setPieceCount(numPieces, 0);

							continue;
						}

						// if this move causes the opposite king to be in check
						if (b.findKing(kColour)->getInCheck()) {
							cout << kColour << " king is in check! " << endl;
						}

						// sets the turn to be opposite colour
						g.changeTurn();
						cout << "It is " << g.getTurn() << "'s turn." << endl;


					} else { // the move cannot be made
						cout << to << " is an invalid move." << endl;


						// **FOR LATER:** if this move results in a pawn promotion, read in another word: what to promote the pawn to

					}
				}
			} else { // otherwise, invalid

				cout << "Invalid square(s), please try again." << endl;
			}

		} else if (command == "setup") { // eval command

			bv.displayBoard();
			bv.displayGraphics();

			if (g.getInProgress()) {
				cout << "Setup mode unavailable during ongoing game." << endl;

			} else {

				// enter setup mode:
				cout << "Entered setup mode. Enter <c> for a list of commands." << endl;

				// user input
				string su_command;

				while (cin >> su_command) {

					if (su_command == "c") {

						printSetupCommands();

					} else if (su_command == "+") {

						// create and read in new piece and square
						string piece;
						string square;
						cin >> piece;
						cin >> square;

						// if the piece is valid + square is on the board
						if (isValidPiece(piece) && isValidSquare(square)) {

							// find the coords
							Position coords = convertCoords(square);

							// make the piece
							shared_ptr<Piece> p = makePiece(piece, coords);

							// if the pawn is the placed in the wrong row, invalid move
							if ((piece == "p" || piece == "P") && (coords.getY() == 0 || coords.getY() == 7)) {

								cout << "Pawn cannot be placed in the first or last row, please try again." << endl;

								// remove piece using board's removePiece method
								b.removePiece(coords.getY(), coords.getX());

							} else {

								// if there is a piece already there
								if (b.getSquare(coords.getY(), coords.getX())->getPiece() != nullptr) {

									// get the piece's name and colour
									string pieceName = b.getSquare(coords.getY(), coords.getX())->getPiece()->getName();
									string pieceColour = b.getSquare(coords.getY(), coords.getX())->getPiece()->getColour();

									// remove piece using board's removePiece method
									b.removePiece(coords.getY(), coords.getX());

									// update numPieces map
									string displayName = getDisplayName(pieceName, pieceColour);
									numPieces[displayName] -= 1;
								}

								// add piece to the square using board's setSquare()
								b.setSquare(coords.getY(), coords.getX(), p);
								numPieces[piece] += 1;

								// display the board
								bv.displayBoard();
								bv.updateGraphics(coords, coords, false);
							}

						} else { // otherwise, invalid

							cout << "Invalid piece or square, please try again." << endl;
						}

					} else if (su_command == "-") {
						// create and read in a square
						string square;
						cin >> square;

						// if the square is on the board
						if (isValidSquare(square)) {

							// find the coords
							Position coords = convertCoords(square);

							// if there's no piece, don't do anything
							if (b.getSquare(coords.getY(), coords.getX())->getPiece() != nullptr) {

								// get the piece's name and colour
								string pieceName = b.getSquare(coords.getY(), coords.getX())->getPiece()->getName();
								string pieceColour = b.getSquare(coords.getY(), coords.getX())->getPiece()->getColour();

								// remove piece using board's removePiece method
								b.removePiece(coords.getY(), coords.getX());

								// update numPieces map
								string displayName = getDisplayName(pieceName, pieceColour);
								numPieces[displayName] -= 1;

								// display the board
								bv.displayBoard();
								bv.updateGraphics(coords, coords, false);
							}

						} else { // otherwise, invalid

							cout << "Invalid square, please try again." << endl;
						}

					} else if (su_command == "=") {

						// read in the next turn's colour
						string colour;
						cin >> colour;

						if (colour == "white" || colour == "White") {
							g.setTurn("White");
							cout << "Set White as next turn." << endl;

						} else if (colour == "black" || colour == "Black"){
							g.setTurn("Black");
							cout << "Set Black as next turn." << endl;

						} else {
							cout << "Invalid colour, please try again." << endl;
						}

					} else if (su_command == "done") {

						bool reqs_met = 1;

						// check that there is 1 k, 1 K, no more than 10 rRbBnN, no more than 9 qQ, no more than 8 pP
						if (numPieces["k"] != 1 || numPieces["K"] != 1 || numPieces["r"] > 10 || numPieces["R"] > 10 || numPieces["b"] > 10 || numPieces["B"] > 10 || numPieces["n"] > 10 || numPieces["N"] > 10 || numPieces["q"] > 9 || numPieces["Q"] > 9 || numPieces["p"] > 8 || numPieces["P"] > 8) {

							reqs_met = false;

						}

						// check if there are pawns in the first or last row
						for (int i = 0; i < 8; i++) {

							// check the first row
							if (b.getSquare(0,i)->getPiece() != nullptr && b.getSquare(0,i)->getPiece()->getName() == "Pawn") {
								reqs_met = false;
								break;
							}

							// check the last row
							if (b.getSquare(7,i)->getPiece() != nullptr && b.getSquare(7,i)->getPiece()->getName() == "Pawn") {
								reqs_met = false;
								break;
							}
						}

						// if there is 1 of each King
						if (numPieces["k"] == 1 && numPieces["K"] == 1) {

							// check that both kings aren't in check
							if (b.findKing("White")->getInCheck() && b.findKing("Black")->getInCheck()) {

								reqs_met = false;
							}

						}

						// if the requirements are met, leave setup
						if (reqs_met) {

							cout << "Exited setup mode." << endl;
							break;

						} else { // otherwise, stay in setup mode

							cout << "Conditions not met to leave setup mode." << endl;
						}
					} else if (su_command == "s") {

						Position kpos = Position{0,0};
						b.updateAllMoves(kpos);

						cout << "Valid:" << endl;
						for (int i = 0; i < b.getSquare(4,4)->getPiece()->getValidMoves().size(); i++) {
							cout << b.getSquare(4,4)->getPiece()->getValidMoves().at(i).getX() << ", ";
							cout << b.getSquare(4,4)->getPiece()->getValidMoves().at(i).getY() << endl;
						}
						cout << "Capturing:" << endl;
						for (int i = 0; i < b.getSquare(4,4)->getPiece()->getCapturingMoves().size(); i++) {
							cout << b.getSquare(4,4)->getPiece()->getCapturingMoves().at(i).getX() << ", ";
							cout << b.getSquare(4,4)->getPiece()->getCapturingMoves().at(i).getY() << endl;
						}


						// Position kpos = Position{4,7};
						// b.updateAllMoves(kpos);

						// if (b.getSquare(7,4)->getPiece()->checkMate(&b)) {
						//	cout << "OMG the king is dead" << endl;
						// } else {
						//	cout << "NO checkmate" << endl;
						// }

						// cout << "FRIEND valid moves: " << b.getSquare(5,4)->getPiece()->getValidMoves().size() << endl;
						// cout << "FRIEND capture moves: " << b.getSquare(5,4)->getPiece()->getCapturingMoves().size() << endl;


					} else {
						cout << "Invalid command. Enter <c> for a list of commands." << endl;
					}
				}
				setupUsed = true;
			}
		} else {
			cout << "Invalid command. Enter <c> for a list of commands." << endl;
		}
	}

	// print the Final Score:
	cout << "------------------------------------------" << endl;
	cout << "Final Score:" << endl;
	cout << "White: " << g.getPlayer("White")->getScore() << endl;
	cout << "Black: " << g.getPlayer("Black")->getScore() << endl;
	cout << "------------------------------------------" << endl;
}
