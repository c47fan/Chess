#include "Game.h"
#include "Board.h"
#include <string>
#include <iostream>

using namespace std;

Game::Game(Board* b, Player* w, Player* bl): board{b}, whitePlayer{w}, blackPlayer{bl}, turn{"White"}, inProgress{false} {}

Game::~Game() {}

string Game::getTurn() const{
    return turn;
}

void Game::setTurn(string c) {
    this->turn = c;
}

bool Game::getInProgress() {
    return inProgress;
}

void Game::setInProgress(bool p) {
    this->inProgress = p;
}

Player* Game::getPlayer(std::string c) {
    if (c == "White") {
        return whitePlayer;
    } else {
        return blackPlayer;
    }
}

void Game::endGame(string c) {

    // reset the Game fields
    this->inProgress = false;
    board->clearBoard();
    this->setTurn("White");

    // update the scores
    if (c == "White") {
        // White wins
        whitePlayer->setScore(1);
    } else if (c == "Black") {
        // Black wins
        blackPlayer->setScore(1);
    } else {
        // Stalemate
        whitePlayer->setScore(0.5);
        blackPlayer->setScore(0.5);
    }

    // print the Current Score:
    cout << "------------------------------------------" << endl;
    cout << "Current Score:" << endl;
    cout << "White: " << whitePlayer->getScore() << endl;
    cout << "Black: " << blackPlayer->getScore() << endl;
    cout << "------------------------------------------" << endl;
}

void Game::changeTurn() {
    if (this->turn == "White") {
        this->turn = "Black";
    } else {
        this->turn = "White";
    }
}

