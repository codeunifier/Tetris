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
	bool isFilled(int i, int j) { if (grid[i][j] == FILLED) return true; return false; }
	void clearPossibleRow();
private:
	Point topLeftBoard;
	Point bottomRightBoard;
	int grid[BOARD_WIDTH][BOARD_LENGTH];
	enum { FILLED, EMPTY };
};

#endif