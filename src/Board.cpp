#include "Board.h"
#include "constants.h"
#include <iostream>

Board::Board()
{
	board = new short* [6];
	short cnt = 0;

	for (short i = 0; i <= maxRows; i++)
	{
		board[i] = new short[6];
		
		for (short j = 0; j <= maxCols; j++)
		{
			if ((j == 1 || j == 5) && (i == 1 || i == 5))
			{
				board[i][j] = 1;
				bigstone_loc[cnt++] = std::make_pair(i, j);
			}
			else
				board[i][j] = 0;
		}
	}

	bigstone_count = 4;
	smallstone_count = 20;
}

bool Board::can_cross(POSITION loc)
{
	if (loc.first == loc.second || (loc.first - 1 == 5 - loc.second))
		return true;
	return false;
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


short Board::make_move(POSITION start, POSITION end)
{
	// check if destination cell is empty
	if (board[end.first][end.second] != EMPTY)
		return 0;

	// make move
	board[end.first][end.second] = board[start.first][start.second];
	board[start.first][start.second] = EMPTY;

	//update bigstone location
	for (short i = 0; i < 4; i++)
	{
		if (bigstone_loc[i] == start);
		{
			bigstone_loc[i] = end;
			break;
		}
	}

	// reduce smallstone count if it destroyed
	if (abs(start.first - end.first) == 2 || abs(start.second - end.second) == 2)
		smallstone_count = smallstone_count > 0 ? smallstone_count - 1 : 0;

	return 1;
}

short Board::reverse_move(POSITION start, POSITION end)
{
	if (board[start.first][start.second] != EMPTY)
		return 0;
	
	//reverse move
	board[start.first][start.second] = board[end.first][end.second];
	board[end.first][end.second] = EMPTY;

	//update bigstone location
	for (short i = 0; i < 4; i++)
	{
		if (bigstone_loc[i] == end)
		{
			bigstone_loc[i] = start;
			break;
		}
	}

	//reverse destruction of smallstone if it happened
	if (abs(start.first - end.first) == 2 || abs(start.second - end.second) == 2)
		smallstone_count = smallstone_count > 0 ? smallstone_count + 1 : 0;

	return 1;
}

int Board::get_points(short player)
{
	short count_bigstone_cannot_move = 0;
	//check if bigstone can move or not
	for (short i = 0; i < 4; i++)
	{
		if (is_stuck(bigstone_loc[i]))
			count_bigstone_cannot_move++;
	}

	if (player == BIGSTONE)
	{
		return -count_bigstone_cannot_move * 5 + (20 - smallstone_count);
	}
	else
		return 5 * count_bigstone_cannot_move + smallstone_count;
}


bool Board::is_stuck(POSITION loc)
{

	return false;
}

POSITION* generate_moves(POSITION loc)
{
	POSITION* dest;

	return NULL;
}

