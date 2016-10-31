/*****************************************************************************
* draw.cpp holds the function definitions for drawing shapes onto the screen
******************************************************************************/

#include "draw.h"
#include <cmath>

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#define deg2rad(value) ((M_PI / 180) * (value))

/***********************************************
* DRAW drawRect
*    draws an unfilled rectangle on the screen
************************************************/
void drawRect(Point topLeft, int blockSize)
{
	Point tr(false /*check*/); // top right 
	Point bl(false /*check*/); // bottom left
	Point br(false /*check*/); // bottom right
	
	//Top right point
	tr.setX(topLeft.getX() + blockSize);
	tr.setY(topLeft.getY());

	//Bottom left point
	bl.setX(topLeft.getX());
	bl.setY(topLeft.getY() - blockSize);

	//Bottom right point
	br.setX(topLeft.getX() + blockSize);
	br.setY(topLeft.getY() - blockSize);

	//Finally draw the rectangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(topLeft.getX(), topLeft.getY(), br.getX(), br.getY());
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(topLeft.getX() + .5, topLeft.getY() + .5);
	glVertex2f(tr.getX() + .5, tr.getY() + .5);
	glVertex2f(br.getX() + .5, br.getY() + .5);
	glVertex2f(bl.getX() + .5, bl.getY() + .5);
	glVertex2f(topLeft.getX() + .5, topLeft.getY() + .5);
	glEnd();
}

/*******************************************************
* DRAW drawBoard
*    draws the frame of the game board (optional grid)
********************************************************/
void drawBoard(const Point & topLeft, const Point & bottomRight)
{
	//frame
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(topLeft.getX(), topLeft.getY());
	glVertex2f(bottomRight.getX(), topLeft.getY());
	glVertex2f(bottomRight.getX(), bottomRight.getY());
	glVertex2f(topLeft.getX(), bottomRight.getY());
	glVertex2f(topLeft.getX(), topLeft.getY());
	glEnd();

	//grid
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int dy = topLeft.getY(); dy > bottomRight.getY(); dy -= 20)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(topLeft.getX(), dy);
		glVertex2f(bottomRight.getX(), dy);
		glEnd();
	}
	for (int dx = topLeft.getX(); dx < bottomRight.getX(); dx += 20)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(dx, topLeft.getY());
		glVertex2f(dx, bottomRight.getY());
		glEnd();
	}
}

/*************************************
* DRAW arrayToPoint
*    converts array index to pixels
**************************************/
Point indexToPixel(Point topLeftBoard, Point index)
{
	float dy, dx;

	dy = topLeftBoard.getY() - index.getY() * 20;
	dx = topLeftBoard.getX() + index.getX() * 20;

	Point pixels;
	pixels.setX(dx);
	pixels.setY(dy);

	return pixels;
}