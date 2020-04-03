#include <iostream>
#include "game.h"
#include "Board.h"


int main()
{
	game newGame(SMALLSTONE, BIGSTONE, 5, true);
	newGame.play();
	std::system("pause");
}