#include "agent.h"
#include "constants.h"
#include <iostream>

agent::agent(PLAYER player, int depth=5, bool fast=false)
{
	_player = player;
	maxDepth = depth;
	optimize = fast;
}

int agent::get_move(Board &currBoard, int depth, PLAYER player, std::pair<POSITION, POSITION>&return_move, long int alpha, long int beta)
{
	
	if (currBoard.smallstonewin() || depth == maxDepth)
	{
		return currBoard.get_points(player);
	}

	if (player == SMALLSTONE)
	{
		std::vector<std::pair<POSITION, std::vector<POSITION>> > moves;
		//std::getchar();
		currBoard.generate_moves(player,moves);

		long int bestval = -INF, value;
		std::pair<POSITION, POSITION> best_move;
		for (auto& pos2mov : moves)
		{
			for (auto& endPos : pos2mov.second)
			{
				//std::getchar();
				currBoard.make_move(pos2mov.first, endPos);
				//currBoard.print_board();
				
				value = get_move(currBoard, depth + 1, BIGSTONE, return_move,alpha,beta);
				if (value > bestval)
				{
					best_move = std::make_pair(pos2mov.first, endPos);
					bestval = value;
				}
				
				currBoard.reverse_move(pos2mov.first, endPos);
				if (optimize)
				{
					alpha = bestval > alpha ? bestval : alpha;
					if (beta <= alpha)
						break;
				}
				//std::cout << "reverse b\n";
			}
		}
		return_move = best_move;
		return bestval;
	}
	else if (player == BIGSTONE)
	{
		std::vector<std::pair<POSITION, std::vector<POSITION>> > moves;
		//std::getchar();
		currBoard.generate_moves(player, moves);

		long int bestval = INF, value;
		std::pair<POSITION, POSITION> best_move;
		for (auto& pos2mov : moves)
		{
			for (auto& endPos : pos2mov.second)
			{
				/*std::getchar();*/
				currBoard.make_move(pos2mov.first, endPos);
				//currBoard.print_board();
				
				value = get_move(currBoard, depth + 1, SMALLSTONE, return_move, alpha, beta);
				
				if (value < bestval)
				{
					best_move = std::make_pair(pos2mov.first, endPos);
					bestval = value;
				}
				//std::cout << "reverse B\n";
				currBoard.reverse_move(pos2mov.first, endPos);

				if (optimize)
				{
					beta = bestval < beta ? bestval : beta;
					if (beta <= alpha)
						break;
				}
			}

		}
		return_move = best_move;
		return bestval;
	}

	return 0;
}

void agent::make_move(Board& board)
{
	std::pair<POSITION, POSITION> move;
	//std::cout << "change of computer : " << char(_player) << "\n";
	get_move(board, 0, _player, move, -INF, +INF);
	//std::cout << move.first.first << " " << move.first.second << " ->" << move.second.first << " " << move.second.second<<"\n";
	//std::cout << "starting moves... \n";
	std::cout << "\n(" << move.first.first << "," << move.first.second << ")->(" << move.second.first << "," << move.second.second << ")\n";
	board.make_move(move.first, move.second);
	//board.print_board();
}