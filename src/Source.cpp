#include <iostream>
#include "game.h"
#include "Board.h"


int main()
{
	Board board;
	
	std::cout << "Choose your player (Bagga(1), Baggi(2)) :";
	int ch;
	std::cin >> ch;
	if (ch == 2)
	{
		game newGame(SMALLSTONE, BIGSTONE, 5, true);
		newGame.play();
	}
	else
	{
		game newGame(BIGSTONE, SMALLSTONE, 5, true);
		newGame.play();
	}
	std::system("pause");
}