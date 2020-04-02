#pragma once

#include "constants.h"
#include "agent.h"
#include "Board.h"

class game
{
private:
    PLAYER _userPlayer, _computerPlayer;
    Board _board;
    bool _win;

    
public:
    game(PLAYER, PLAYER);

    void play();

};

