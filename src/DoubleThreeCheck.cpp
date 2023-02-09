//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"

void DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &coord,
										  const Player &player)
{
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

Doubles 		DoubleThreeCheck::boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates) {
	auto doubles = Doubles();
	if(coordinates_on_board.y < new_coordinates.y || coordinates_on_board.x < new_coordinates.x) {
		doubles.left_boundary_coordinates = coordinates_on_board;
		doubles.right_boundary_coordinates = new_coordinates;
	} else {
		doubles.left_boundary_coordinates = new_coordinates;
		doubles.right_boundary_coordinates = coordinates_on_board;
	}
	return doubles;
}

size_t		DoubleThreeCheck::double_two_size() {
	return _doubleTwoList.size();
}

void 		DoubleThreeCheck::two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play)
{
	auto current_coordinates = check_two_in_a_row(board, coord, play);
	if(current_coordinates.y != -1) {
		auto doubletwo_elem = boundary_check(current_coordinates, coord);
		_doubleTwoList.push_back(doubletwo_elem);
	}
}

bool 		DoubleThreeCheck::find_double_three()
{
	return false;
}
