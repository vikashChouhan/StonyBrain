#pragma once

#include <utility>
#include "constants.h"
#include <vector>
class Board
{
private:
	short **board;
	const short maxRows = 5;
	const short maxCols = 5;
	
	short bigstone_count, smallstone_count;
	POSITION bigstone_loc[4];

	short noncrossmove_x [4] = { 0,0,1,-1, };
	short noncrossmove_y [4] = { 1,-1,0,0 };

	short crossmove_x[4] = { 1,1,-1,-1 };
	short crossmove_y[4] = { 1,-1,1,-1 };
	
	inline bool can_cross(POSITION);
	inline bool valid_pos(POSITION);
	std::vector<POSITION> generate_moves(POSITION);
public:
	
	Board();

	void print_board();
	bool smallstonewin();
	short make_move(POSITION, POSITION);
	short reverse_move(POSITION, POSITION);
	int get_points(PLAYER);
	bool is_stuck(POSITION);
	void generate_moves(PLAYER, std::vector<std::pair<POSITION, std::vector<POSITION>> >&);
};

