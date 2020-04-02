#pragma once

#include "constants.h"
#include "agent.h"
#include "Board.h"

class game
{
private:
    PLAYER _userPlayer, _computerPlayer;
    Board _board;
    agent _computer;

    bool _win;

    std::pair<POSITION, POSITION> get_user_move();
public:
    game(PLAYER, PLAYER, int, bool);

    void play();
};

