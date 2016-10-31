#ifndef PIECE_H
#define PIECE_H

#include "point.h"
#include <vector>

#define BLOCK_SIZE 20

/*******************************
* PIECE
*    base class for the pieces
********************************/
class Piece
{
public:
	Piece(int boardWidth);
	int getBlockType(int xBlock, int yBlock);
	int getXInitialPosition();
	int getYInitialPosition();
	Point getPosition() { return position; }
	void draw(Point topLeft);
	void moveLeft() { position.addX(-1); }
	void moveRight() { position.addX(1); }
	void moveDown() { position.addY(1); }
	void rotate() {	rotation++;	if (rotation > 3) rotation = 0;	}
private:
	int kind;
	int rotation;
	Point position;
};

#endif