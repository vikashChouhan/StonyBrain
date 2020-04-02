#include "Board.h"
#include "constants.h"
#include <iostream>
#include <vector>

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
			else if ((i == 2 && (j == 2 || j == 4)) || (i == 4 && (j == 2 || j == 4)))
			{
				board[i][j] = 4;
			}
			else
				board[i][j] = -1;
		}
	}

	bigstone_count = 4;
	smallstone_count = 20;
}

inline bool Board::can_cross(POSITION loc)
{
	if (loc.first == loc.second || (loc.first - 1 == 5 - loc.second))
		return true;
	return false;
}

inline bool Board::valid_pos(POSITION loc)
{
	if (loc.first >= 1 && loc.first <= maxRows && loc.second >= 1 && loc.second <= maxCols)
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
			if (board[i][j] == EMPTY)
				std::cout << "_" << "    ";
			else
				std::cout << board[i][j] << "    ";
		}
	}
	std::cout << "\n";
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
		if (bigstone_loc[i] == start)
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

int Board::get_points(PLAYER player)
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
		return count_bigstone_cannot_move * 5 + (20 - smallstone_count) - smallstone_count;
	}
	else
		return 5 * count_bigstone_cannot_move + smallstone_count - (20 - smallstone_count);
}


bool Board::is_stuck(POSITION loc)
{
	if (generate_moves(loc).empty()) 
		return true;
	return false;
}

std::vector<POSITION> Board::generate_moves(POSITION loc)
{
		
	std::vector<POSITION> moves;
	if (board[loc.first][loc.second] == EMPTY)
		return moves;

	POSITION newPos;
	for (short i = 0; i < 4; i++)
	{
		newPos.first = loc.first + noncrossmove_x[i];
		newPos.second = loc.second + noncrossmove_y[i];

		if (valid_pos(newPos) && board[newPos.first][newPos.second] == EMPTY)
			moves.emplace_back(newPos);

		if (can_cross(loc))
		{
			newPos.first = loc.first + crossmove_x[i];
			newPos.second = loc.second + crossmove_y[i];

			if (valid_pos(newPos) && board[newPos.first][newPos.second] == EMPTY)
				moves.emplace_back(newPos);
		}
	}

	if (board[loc.first][loc.second] == BIGSTONE)
	{
		for (short i = 0; i < 4; i++)
		{
			newPos.first = loc.first + noncrossmove_x[i] == 0 ? 0: noncrossmove_x[i]*2;
			newPos.second = loc.second + noncrossmove_y[i] == 0 ? 0: noncrossmove_y[i]*2;

			if (board[loc.first + noncrossmove_x[i]][loc.second + noncrossmove_y[i]] != SMALLSTONE)
				continue;

			if (valid_pos(newPos) && board[newPos.first][newPos.second] == EMPTY)
				moves.emplace_back(newPos);

			if (can_cross(loc))
			{
				newPos.first = loc.first + 2*crossmove_x[i];
				newPos.second = loc.second + 2*crossmove_y[i];

				if (board[loc.first + crossmove_x[i]][loc.second + crossmove_y[i]] != SMALLSTONE)
					continue;

				if (valid_pos(newPos) && board[newPos.first][newPos.second] == EMPTY)
					moves.emplace_back(newPos);
			}
		}
	}
		
	return moves;
}

bool Board::smallstonewin()
{
	for (int i = 0; i < 4; i++)
	{
		if (!is_stuck(bigstone_loc[i]))
			return false;
	}
	return true;
}

void Board::generate_moves(PLAYER player, 
	std::vector<std::pair<POSITION, std::vector<POSITION>> >&moves)
{
	for (short i = 1; i <= maxRows; i++)
	{
		for (short j = 1; j <= maxCols; j++)
		{
			if (board[i][j] == player)
			{
				moves.emplace_back(std::make_pair(POSITION(i, j), generate_moves(POSITION(i, j))));
			}
		}
	}
}
