#pragma once

static const short BIGSTONE = 1;
static const short SMALLSTONE = 0;
static const short EMPTY = -1;

class Board
{
private:
	short **board;
	const short maxRows = 5;
	const short maxCols = 5;
	
public:
	
	Board();

	void print_board();
	
	short make_move(short, short, short, short);

};

