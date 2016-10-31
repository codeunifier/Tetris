#ifndef BOARD_H
#define BOARD_H

#include "point.h"
#include "piece.h"
#include <vector>

#define BOARD_WIDTH 10
#define BOARD_LENGTH 20

class Board
{
public:
	Board();
	void draw();
	Point getTLB() { return topLeftBoard; }
	Point getBRB() { return bottomRightBoard; }
	void pieceToBoard(Piece * add);
	void advance();
private:
	Point topLeftBoard;
	Point bottomRightBoard;
	std::vector<Piece*> piecesOnBoard;
	
};

#endif