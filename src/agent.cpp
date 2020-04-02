#include "agent.h"
#include "constants.h"


agent::agent(PLAYER player, int depth=5, bool fast=false)
{
	_player = player;
	maxDepth = depth;
	optimize = fast;
	alpha = INF;
	beta = -INF;
}

int agent::get_move(Board &currBoard, int depth, PLAYER player, std::pair<POSITION, POSITION>&return_move)
{
	if (currBoard.smallstonewin() || depth == maxDepth)
	{
		return currBoard.get_points(player);
	}

	if (player == SMALLSTONE)
	{
		std::vector<std::pair<POSITION, std::vector<POSITION>> > moves;
		currBoard.generate_moves(player,moves);

		int bestval = -INF, value;
		std::pair<POSITION, POSITION> best_move;
		for (auto& pos2mov : moves)
		{
			for (auto& endPos : pos2mov.second)
			{
				currBoard.make_move(pos2mov.first, endPos);
				
				value = get_move(currBoard, depth + 1, BIGSTONE, return_move);

				if (value > bestval)
				{
					best_move = std::make_pair(pos2mov.first, endPos);
					bestval = value;
				}
				currBoard.reverse_move(pos2mov.first, endPos);
			}
		}
		return bestval;
	}
	else if (player == BIGSTONE)
	{
		std::vector<std::pair<POSITION, std::vector<POSITION>> > moves;
		currBoard.generate_moves(player, moves);

		int bestval = INF, value;
		std::pair<POSITION, POSITION> best_move;
		for (auto& pos2mov : moves)
		{
			for (auto& endPos : pos2mov.second)
			{
				currBoard.make_move(pos2mov.first, endPos);
				
				value = get_move(currBoard, depth + 1, BIGSTONE, return_move);
				
				if (value < bestval)
				{
					best_move = std::make_pair(pos2mov.first, endPos);
					bestval = value;
				}
				currBoard.reverse_move(pos2mov.first, endPos);
			}

		}
		return bestval;
	}

	return 0;
}

void agent::make_move(Board& board)
{
	std::pair<POSITION, POSITION> move;
	get_move(board, 0, _player, move);

	board.make_move(move.first, move.second);
}