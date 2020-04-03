#include <iostream>
#include "game.h"
#include "Board.h"


int main()
{
	game newGame(SMALLSTONE, BIGSTONE, 4,false);
	newGame.play();
	std::system("pause");
}