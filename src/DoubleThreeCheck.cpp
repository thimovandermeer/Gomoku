//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"

void DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &coord,
										  const Player &player)
{
//	_board = board;
//	_coord = coord;
//	_player = player;
	std::string reason;
	this->set_state(ACCEPTED, reason);
}

void DoubleThreeCheck::set_state(State newState, std::string &errorReason) {
	_state.error_reason = errorReason;
	_state.state = newState;
}

Coordinates		DoubleThreeCheck::check_two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& player) {
	Coordinates already_on_board_coords{};
	LOG("incoming coords %i, %i", coord.y, coord.x);
	LOG("wat is deze %i", board[coord.y - 1][coord.x -1]);
	LOG("wat is player %i", player);
	if(static_cast<Player>(board[coord.y - 1][coord.x -1]) == player) {
		already_on_board_coords.y = coord.y -1;
		already_on_board_coords.x = coord.x -1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y][coord.x - 1]) == player) {
		already_on_board_coords.y = coord.y;
		already_on_board_coords.x = coord.x -1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y + 1][coord.x -1]) == player) {
		already_on_board_coords.y = coord.y + 1;
		already_on_board_coords.x = coord.x - 1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y][coord.x + 1]) == player ) {
		already_on_board_coords.y = coord.y;
		already_on_board_coords.x = coord.x +1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y + 1][coord.x + 1]) == player)  {
		already_on_board_coords.y = coord.y +1;
		already_on_board_coords.x = coord.x +1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y - 1][coord.x + 1]) == player) {
		already_on_board_coords.y = coord.y -1;
		already_on_board_coords.x = coord.x +1;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y + 1][coord.x]) == player) {
		already_on_board_coords.y = coord.y +1;
		already_on_board_coords.x = coord.x;
		return already_on_board_coords;
	} else if (static_cast<Player>(board[coord.y - 1][coord.x]) == player) {
		already_on_board_coords.y = coord.y -1;
		already_on_board_coords.x = coord.x;
		return already_on_board_coords;
	} else {
		already_on_board_coords.y = -1;
		already_on_board_coords.x = -1;
		return already_on_board_coords;
	}
}
void 		DoubleThreeCheck::two_in_a_row()
{

}

bool 		DoubleThreeCheck::find_double_three(std::vector <std::vector<Tile>> &board)
{
//	std::vector< std::vector<Tile> >::iterator row;
//	std::vector<Tile>::iterator col;
//	for (row = board.begin(); row != board.end(); row++) {
//		for (col = row->begin(); col != row->end(); col++) {
//			if(static_cast<Player>(*col) == _player) {
//				LOG("is this the case?");
//
//			}
//		}
//	}
}
