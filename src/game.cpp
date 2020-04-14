#include "game.h"
#include <iostream>

game::game(PLAYER user, PLAYER computer, int depth=5, bool fast=false):_computer(computer, depth, fast)
{
	_userPlayer = user;
	_computerPlayer = computer;
}



std::pair<POSITION, POSITION> game::get_user_move()
{
	enterMove:

	std::cout << "\n Enter your move as {start position x start position y end positon x end_posotion y} or '-1 to quite' :\n";
	short startPos_x, startPos_y, endPos_x, endPos_y;
	std::cin >> startPos_x;

	if (startPos_x != -1)
	{
		std::cin >> startPos_y >> endPos_x >> endPos_y;

		if (_board.valid_move({ {startPos_x,startPos_y},{endPos_x,endPos_y} }, _userPlayer))
			return { {startPos_x,startPos_y},{endPos_x,endPos_y} };
		else
			goto enterMove;
	}
	else
		return { {-1,-1},{-1,-1} };
}
void game::play()
{
	std::pair<POSITION, POSITION> move;
	std::cout << "Enter any key to play...";
	std::getchar();

	std::system("cls");
	_board.print_board();

	while (!_board.smallstonewin())
	{
		if (_userPlayer == SMALLSTONE)
		{
			again1:
			move = get_user_move();
			
			//check if user quit game
			if (move.first.first == -1)
				break;

			short res = _board.make_move(move.first, move.second);
			if (res == 0)
				goto again1;

			std::system("cls");
			_board.print_board();
			std::system("pause");
		}
		else
		{
			_computer.make_move(_board);
			//printing board after each move
			std::system("cls");
			_board.print_board();
			std::cout << "\n";
		}


		if (_board.smallstonewin()) break;
		
		if (_userPlayer == SMALLSTONE)
		{
			_computer.make_move(_board);
			//printing board after each move
			std::system("cls");
			_board.print_board();
			std::cout << "\n";
		}
		else
		{
		again2:
			move = get_user_move();
			if (move.first.first == -1)
				break;
			short res = _board.make_move(move.first, move.second);
			if (res == 0)
				goto again2;

			std::system("cls");
			_board.print_board();
			std::system("pause");
		}
	}


	std::cout << "\nResult : ";
	if (_userPlayer == SMALLSTONE && _board.smallstonewin())
		std::cout << "User Win! :)";
	else
		std::cout << "Computer Win! :>";

}