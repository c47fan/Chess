CXX = g++
CXXFLAGS = -std=c++14 -g -MMD \
		   -Wall -Werror=vla -Wextra \
		   -I ./src -I ./src/headers
EXEC = chess
OBJECTS = Board.o main.o Piece.o Square.o BoardView.o Position.o Rook.o Bishop.o King.o Pawn.o Knight.o Queen.o Game.o Player.o Window.o
DEPENDS = ${OBJECTS:.o=.d}

VPATH = src:src/headers

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS} # ignore errors

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


