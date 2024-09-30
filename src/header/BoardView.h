#ifndef BOARD_VIEW
#define BOARD_VIEW
#include "Window.h"
#include "Position.h"
#include <memory>

class Board;

class BoardView{
        Board* board;
        std::shared_ptr<Xwindow> window;
      public:
        explicit BoardView(Board *board);
        ~BoardView();
        void displayBoard();
        void displayGraphics() const;
        void updateGraphics(Position from, Position to, bool two = true) const;

};

#endif
