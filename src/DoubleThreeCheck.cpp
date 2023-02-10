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

Direction       DoubleThreeCheck::determine_direction(Doubles doubles) {
    if(doubles.left_boundary_coordinates.x == doubles.right_boundary_coordinates.x) {
        return VERTICAL;
    } else if (doubles.left_boundary_coordinates.y == doubles.right_boundary_coordinates.y)
        return HORIZONTAL;
    else {
        return CROSS;
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
    doubles.direction = determine_direction(doubles);
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

bool 		DoubleThreeCheck::find_double_three(Coordinates newCoords, std::vector<Doubles> double_two)
{
    LOG("newcoords are %i %i", newCoords.y, newCoords.x);
    for (auto elem : double_two) {
        if(check_right_boundary(elem.right_boundary_coordinates, newCoords, elem.direction)) {
            // add element to list of double three with direction
        }
        if(check_left_boundary(elem.left_boundary_coordinates, newCoords, elem.direction)) {
            // add element to list of double three with direction
        }
    }
    // check if these new coordinates are close to the double two's we already have

}

bool DoubleThreeCheck::check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    if(direction == HORIZONTAL) {
        if(new_coords.y == boundary_coords.y) {
            LOG("We are on the same horizontal axis");
            if(new_coords.x - boundary_coords.x == 1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
                return true;
            }
            LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return false;
        }
    } else if(direction == VERTICAL) {
        if(new_coords.x == boundary_coords.x){
            LOG("We are on the same vertical axis");
            if(new_coords.y - boundary_coords.y == 1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
                return true;
            }
            LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            return false;
        }
    } else if(direction == CROSS) {
        if((new_coords.y - boundary_coords.y) == 1) {
            LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            if(new_coords.x - boundary_coords.x == 1) {
                LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
                LOG("We are a match");
                return true;
            }
            LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return false;
        }
        LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
        return false;
    }
    return false;
}

bool DoubleThreeCheck::check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in left boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    return false;
}
