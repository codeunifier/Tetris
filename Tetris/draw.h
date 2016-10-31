#ifndef DRAW_H
#define DRAW_H

#include "point.h"
#include <vector>

void drawRect(Point topLeft, int blockSize);
void drawBoard(const Point & topLeft, const Point & bottomRight);
Point indexToPixel(Point topLeftBoard, Point position);

#endif