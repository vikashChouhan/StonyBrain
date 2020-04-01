#pragma once

#include "constants.h"
#include <utility>


class Board
{
private:
	short **board;
	const short maxRows = 5;
	const short maxCols = 5;
	
	short bigstone_count, smallstone_count;
	POSITION bigstone_loc[4];


	bool can_cross(POSITION);

public:
	
	Board();

	void print_board();
	
	short make_move(POSITION, POSITION);
	short reverse_move(POSITION, POSITION);

	int get_points(short);

	bool is_stuck(POSITION);
	POSITION* generate_moves(POSITION);
};

