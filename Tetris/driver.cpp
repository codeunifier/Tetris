/**************************************************************
* driver.cpp is the portion of the program that runs the game
***************************************************************/

#include "game.h"

/********************************************************************
* DRIVER callBack
*    game engine - runs and draws the game and handles player input
*********************************************************************/
void callBack(const Interface *pUI, void *p)
{
	Game *pGame = (Game *)p;

	pGame->advance();
	pGame->handleInput(*pUI);
	pGame->draw(*pUI);
}

/********************************************
* DRIVER main
*    initializes game and calls game engine
*********************************************/
int main(int argc, char ** argv)
{
	Point topLeftScreen(-300, 340);
	Point bottomRightScreen(300, -340);

	Interface ui(argc, argv, "Tetris", topLeftScreen, bottomRightScreen);
	Game game(topLeftScreen, bottomRightScreen);
	ui.run(callBack, &game);

	return 0;
}