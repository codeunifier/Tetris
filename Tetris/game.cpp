#include "game.h"
#include "draw.h"
#include <time.h>
#include <cassert>

/********************************************
* GAME Game
*    default constructor for the game class
*********************************************/
Game::Game(Point tl, Point br) : topLeftScreen(tl), bottomRightScreen(br)
{
	srand(time(NULL));

	mainPiece = new Piece(BOARD_WIDTH);

	resetTimer();

	//std::cout << "Game created." << std::endl;
}

/***************************
* GAME advance
*    advances the game 1ns
****************************/
void Game::advance()
{
	board.advance();

	if (timer <= 0)
	{
		mainPiece->moveDown();
		resetTimer();
	}

	timer--;

	handleCollisions();
}

/****************************************************
* GAME handleCollisions
*    handles collisions between pieces and the board
*****************************************************/
void Game::handleCollisions()
{
	if (mainPiece->getPosition().getY() >= BOARD_LENGTH)
	{
		std::cerr << "Piece has reached bottom of board\n";
	}
}

/*********************************************************************
* GAME draw
*    calls the draw functions for the piece, the board, and the menu
**********************************************************************/
void Game::draw(const Interface & ui)
{
	mainPiece->draw(board.getTLB());
	board.draw();
}

/*******************************************
* GAME handleInput
*    handle keyboard input from the player
********************************************/
void Game::handleInput(const Interface & ui)
{
	if (ui.isLeft())
	{
		//if (!mainPiece->canMoveLeft())
			mainPiece->moveLeft();
	}

	if (ui.isRight())
	{
		//if (!mainPiece->canMoveRight())
			mainPiece->moveRight();
	}

	if (ui.isUp())
	{
		mainPiece->rotate();
	}

	if (ui.isDown())
	{
		mainPiece->moveDown();
	}
}

int Game::random(int min, int max)
{
	assert(min <= max);
	int num = (rand() % (max - min)) + min;
	assert(min <= num && num <= max);

	return num;
}