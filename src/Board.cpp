#include "Board.h"
#include <iostream>

Board::Board()
{
	board = new short* [6];
	for (short i = 0; i <= maxRows; i++)
	{
		board[i] = new short[6];
		
		for (short j = 0; j <= maxCols; j++)
		{
			if ((j == 1 || j == 5) && (i == 1 || i == 5))
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}
}

void Board::print_board()
{
	std::cout << "\n\n";
	
	std::cout << "\t";
	for (short i = 1; i <= maxCols; i++)
	{
		std::cout << i << "    ";
	}

	std::cout << "\n";
	for (short i = 1; i <= maxRows; i++)
	{
		std::cout << "\n\n" << i << "\t";

		for (short j = 1; j <= maxCols; j++)
		{
			std::cout << board[i][j] << "    ";
		}
	}
}


short Board::make_move(short startPos_x, short startPos_y, short endPos_x, short endPos_y)
{
	if (board[endPos_x][endPos_y] != EMPTY)
		return 0;

	board[endPos_x][endPos_y] = board[startPos_x][startPos_y];
	board[startPos_x][startPos_x] = EMPTY;

	return 1;
}