#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <cstdlib>
#include <vector>
#include "Position.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"

class Player{
    
    private:
        std::string type;
        std::string colour;
        float score;
        bool isComputer;
        int computerLevel;

    public:
        Player(std::string c);
        ~Player();

        std::string getType() const;
        std::string getColour() const;
        float getScore() const;
        bool getIsComputer() const;
        int getComputerLevel() const;

        void setType(std::string t);
        void setScore(float point);
        void setIsComputer(bool c);
        void setComputerLevel(int l);

        std::vector<Position> computerLevel1(Board *b);
        std::vector<Position> computerLevel2(Board *b);
        std::vector<Position> computerLevel3(Board *b);


};

#endif
