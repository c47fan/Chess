#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.h"

class Board;

class Game{

    private:
        Board* board;
        std::string turn;
        bool inProgress;
        Player* whitePlayer;
        Player* blackPlayer;

    public:
	    Game(Board* b, Player* w, Player* bl);
	    ~Game();

        std::string getTurn() const;
        void setTurn(std::string c);

        bool getInProgress();
        void setInProgress(bool p);

        Player* getPlayer(std::string c);

        void endGame(std::string c);
        void changeTurn();
};

#endif
