#pragma once

#include "Board.h";

class agent
{
private:
	int maxDepth, alpha , beta;
	bool optimize;
	PLAYER _player;

public:

	agent(PLAYER, int , bool);

	int get_move(Board&, int, PLAYER, std::pair<POSITION,POSITION>&);
	void make_move(Board&);
};

