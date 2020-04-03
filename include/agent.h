#pragma once

#include "Board.h";

class agent
{
private:
	int maxDepth;
	bool optimize;
	PLAYER _player;

public:

	agent(PLAYER, int , bool);

	int get_move(Board&, int, PLAYER, std::pair<POSITION,POSITION>&,long int,long int);
	void make_move(Board&);
};

