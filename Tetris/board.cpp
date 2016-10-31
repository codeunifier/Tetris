#include "board.h"
#include "draw.h"

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

/***************************************
* BOARD Board
*    default constructor for the board
****************************************/
Board::Board()
{
	topLeftBoard.setX(-(BOARD_WIDTH * (BLOCK_SIZE / 2)));
	topLeftBoard.setY(BOARD_LENGTH * (BLOCK_SIZE / 2));
	bottomRightBoard.setX(BOARD_WIDTH * (BLOCK_SIZE / 2));
	bottomRightBoard.setY(-(BOARD_LENGTH * (BLOCK_SIZE / 2)));
}

/*********************************************************************
* BOARD advance
*    called every nanosecond - advances the board a unit of time
*    the main piece is moved down when the timer reaches 0
**********************************************************************/
void Board::advance()
{
}

/*********************************************************
* BOARD draw
*    calls the drawBoard function from the draw.cpp file
**********************************************************/
void Board::draw()
{
	drawBoard(topLeftBoard, bottomRightBoard);

	//draw any pieces already on the board
	if (piecesOnBoard.size() > 0)
	{
		//for (int i = 0; i < piecesOnBoard.size(); i++)
			//piecesOnBoard[i]->draw(topLeftBoard);
	}
}

/******************************************
* BOARD pieceToBoard
*    moves the main piece onto the board
*******************************************/
void Board::pieceToBoard(Piece * add)
{
	piecesOnBoard.push_back(add);
}