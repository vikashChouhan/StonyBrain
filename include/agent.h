#pragma once

#include "Board.h";

class agent
{
private:
	int maxDepth, alpha , beta;
	bool optimize;

public:

	agent(int, bool);

	int generate_move(short, short, short, short);

	Board make_move(Board);
};

