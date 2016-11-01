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
	//board.advance(); doesn't do anything right now

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
	//iterate through 5x5 grid
	for (int x = mainPiece->getPosition().getX(), i = 0; x < mainPiece->getPosition().getX() + 5; x++, i++)
	{
		for (int y = mainPiece->getPosition().getY(), j = 0; y > mainPiece->getPosition().getY() - 5; y--, j++)
		{
			//we only care about the actual piece within the 5x5
			if (mainPiece->getBlockType(i, j) != 0)
			{
				//checks if piece collides with a filled space on the board
				if (y >= 0 && board.isFilled(x, y))
				{
					mainPiece->moveUp();
					board.pieceToBoard(mainPiece);
					mainPiece = createPiece();
					break;
				}
				//checks if the piece is at the bottom of the board
				if (y == BOARD_LENGTH - 1)
				{
					//piece has reached the bottom of the board
					board.pieceToBoard(mainPiece);
					mainPiece = createPiece();
					break;
				}
			}			
		}
	}

	//checks if any piece in the top row in filled
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		if (board.isFilled(x, 0))
		{
			//game over
		}
	}

	board.clearPossibleRow();
}

/*********************************************************************
* GAME draw
*    calls the draw functions for the piece, the board, and the menu
**********************************************************************/
void Game::draw(const Interface & ui)
{
	//drawRect(indexToPixel(board.getTLB(), Point(2, 19)), BLOCK_SIZE);
	//std::cout << "main piece position for drawing: " << mainPiece->getPosition().getX() << ", " << mainPiece->getPosition().getY() << std::endl;
	mainPiece->draw(indexToPixel(board.getTLB(), mainPiece->getPosition()));
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
		if(mainPiece->canMoveLeft())
			mainPiece->moveLeft();
	}

	if (ui.isRight())
	{
		if (mainPiece->canMoveRight(BOARD_WIDTH))
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