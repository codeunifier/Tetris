#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "piece.h"
#include "board.h"

/**************************
* GAME
*   game class definition
***************************/
class Game
{
public:
	Game(Point tl, Point br);
	~Game() {}

	void advance();
	void handleInput(const Interface & ui);
	void draw(const Interface & ui);

private:
	//coordinates of the screen
	Point topLeftScreen;
	Point bottomRightScreen;

	Piece * mainPiece;
	Board board;
	Piece* createPiece() { return new Piece(); }

	int timer;
	void resetTimer() { timer = 35; }
	int random(int, int);
	void handleCollisions();
};

#endif