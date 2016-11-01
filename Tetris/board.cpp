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

	//set all grid positions to empty
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_LENGTH; j++)
			grid[i][j] = EMPTY;

	//std::cout<<"Board created." << std::endl;
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
	//board
	//frame
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(topLeftBoard.getX(), topLeftBoard.getY());
	glVertex2f(bottomRightBoard.getX(), topLeftBoard.getY());
	glVertex2f(bottomRightBoard.getX(), bottomRightBoard.getY());
	glVertex2f(topLeftBoard.getX(), bottomRightBoard.getY());
	glVertex2f(topLeftBoard.getX(), topLeftBoard.getY());
	glEnd();
	//grid
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int dy = topLeftBoard.getY(); dy > bottomRightBoard.getY(); dy -= 20)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(topLeftBoard.getX(), dy);
		glVertex2f(bottomRightBoard.getX(), dy);
		glEnd();
	}
	for (int dx = topLeftBoard.getX(); dx < bottomRightBoard.getX(); dx += 20)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(dx, topLeftBoard.getY());
		glVertex2f(dx, bottomRightBoard.getY());
		glEnd();
	}

	//draw any pieces already on the board
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_LENGTH; j++)
			if (grid[i][j] == FILLED)
				drawRect(indexToPixel(topLeftBoard, Point(i, j)), BLOCK_SIZE);
}

/******************************************
* BOARD pieceToBoard
*    moves the main piece onto the board
*******************************************/
void Board::pieceToBoard(Piece * add)
{
	for (int i = 0, x = add->getPosition().getX(); i < 5; i++, x++)
		for (int j = 0, y = add->getPosition().getY(); j < 5; j++, y--)
			if (add->getBlockType(i, j) != 0)
				grid[x][y] = FILLED;
}

/******************************************************************************************************
* BOARD clearPossibleRow
*    checks if there is a completed row and eliminates it, moving all other filled blocks above it down
*******************************************************************************************************/
void Board::clearPossibleRow()
{
	bool complete;
	int row;

	//check if a row is complete
	for (int y = 0; y < BOARD_LENGTH; y++)
	{
		complete = true;

		//check for any empty spaces
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (grid[x][y] == EMPTY)
				complete = false;
		}

		if (complete)
		{
			row = y;
			break;
		}
	}

	//if complete, eliminate and move everything above it down one row
	if (complete)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
			grid[x][row] = EMPTY;

		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < row; y++)
			{
				if (grid[x][y] == FILLED)
				{
					grid[x][y] = EMPTY;
					grid[x][y + 1] = FILLED;
				}
			}
		}
	}
}