#include "agent.h"

#define INF 99999999

agent::agent(int depth, bool fast)
{
	maxDepth = depth;
	optimize = fast;
	alpha = INF;
	beta = -INF;
}

int generate_move()
{

	return 0;
}