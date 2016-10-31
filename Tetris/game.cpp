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

	mainPiece = new Piece();

	resetTimer();
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
	/*
	//initialize onEdge variables to false, then check if true
	mainPiece->setOnLeftEdge(false);
	mainPiece->setOnRightEdge(false);

	//collision with edges of board
	for (int i = 0; i < mainPiece->getBlocks().size(); i++)
	{
		//check left and right edges
		if (mainPiece->getBlocks()[i].position.getX() == 0)
			mainPiece->setOnLeftEdge(true);
		else if (mainPiece->getBlocks()[i].position.getX() == BOARD_WIDTH - 1)
			mainPiece->setOnRightEdge(true);

		//check bottom of board
		if (mainPiece->getBlocks()[i].position.getY() == BOARD_LENGTH - 1)
		{
			//piece hit bottom of board
			//std::cerr << "main piece is at the bottom of the board\n";

			board.pieceToBoard(mainPiece);

			mainPiece = createPiece();
		}
	}

	//collisions with other pieces on the board
	if (board.getPiecesOnBoard().size() > 0)
	{
		//iterate through every piece on the board
		for (int i = 0; i < board.getPiecesOnBoard().size(); i++)
		{
			//iterate through every square of the piece on the board
			for (int j = 0; j < board.getPiecesOnBoard()[i]->getBlocks().size(); j++)
			{
				//iterate through every square of the main piece
				for (int k = 0; k < mainPiece->getBlocks().size(); k++)
				{
					if (mainPiece->getBlocks()[k].position.getY() + 1
						== board.getPiecesOnBoard()[i]->getBlocks()[j].position.getY()
						&& mainPiece->getBlocks()[k].position.getX()
						== board.getPiecesOnBoard()[i]->getBlocks()[j].position.getX())
					{
						//std::cerr << "main piece is above a piece on the board\n";
						
						board.pieceToBoard(mainPiece);

						mainPiece = createPiece();
					}
				}
			}
		}
	}
	*/
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