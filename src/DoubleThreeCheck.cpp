//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"

errorState DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &coord,
										  const Player &player)
{
	this->set_board(board);
	this->two_in_a_row(board, coord, player);
	this->find_three(coord, _doubleTwoList);
	return (this->find_double_three());

}

void DoubleThreeCheck::set_board(const std::vector<std::vector<Tile>> &board) {
	this->_board = board;
}

void DoubleThreeCheck::set_state(State newState, std::string &errorReason) {
	_state.error_reason = errorReason;
	_state.state = newState;
}

// deze moet verplaatst worden naar Two en via een getter verkregen kunnen worden
size_t		DoubleThreeCheck::double_two_size() {
	return _doubleTwoList.size();
}

void 		DoubleThreeCheck::two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play)
{
    _doubleTwoList.push_back(_two->create_two(board, coord, play));
}

Threes		DoubleThreeCheck::fill_double_three_stack(Coordinates bound_coordinates, Coordinates newCoords,
														boundary_check_return type, bool left)
{
	Threes result;
	result.open_space_coordinates = type.openSpace;
	if(left) {
		result.left_boundary_coordinates = newCoords;
		result.right_boundary_coordinates = bound_coordinates;
	} else {
		result.left_boundary_coordinates = bound_coordinates;
		result.right_boundary_coordinates = newCoords;
	}
	if(type.doubleType == NORMAL) {
		result.open_space = false;
	}
	if (type.doubleType == EMPTYSPACE) {
		result.open_space = true;;
	}
	return result;
}

bool 		DoubleThreeCheck::find_three(Coordinates newCoords, std::vector<Doubles> &double_two)
{
    LOG("newcoords are %i %i", newCoords.y, newCoords.x);
    for (auto elem : double_two) {
		Threes three_in_a_row;
		auto result = check_right_boundary(elem.right_boundary_coordinates, newCoords, elem.direction);
		if(result.doubleType != NONE) {
			three_in_a_row = fill_double_three_stack(elem.left_boundary_coordinates, newCoords, result, false);
			_doubleThreeList.push_back(three_in_a_row);
            return true;
        }
		result = check_left_boundary(elem.left_boundary_coordinates, newCoords, elem.direction);
        if(result.doubleType != NONE) {
			three_in_a_row = fill_double_three_stack(elem.right_boundary_coordinates, newCoords, result, true);
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
    }
    return false;
}

bool		DoubleThreeCheck::open_space_is_empty(Coordinates empty_space) {
	LOG("OPEN SPACE IS EMPTY Y [%i] X [%i]", empty_space.y, empty_space.x);
	if(_board[empty_space.y][empty_space.x] == Tile::EMPTY) {
		return true;
	} else {
		return false;
	}
}

double_type			DoubleThreeCheck::check_right_boundary_horizontal(Coordinates boundary_coords, Coordinates new_coords)
{
	if(new_coords.y == boundary_coords.y) {
		LOG("We are on the same horizontal axis");
		if(new_coords.x - boundary_coords.x == 1) {
			LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			return NORMAL;
		} if(new_coords.x - boundary_coords.x == 2) {
			LOG("Potentially one empty space in between");
			auto open_space_coords = new_coords;
			open_space_coords.x = new_coords.x + 1;
			LOG("OPEN space coords = %i", open_space_coords.x);
			if(open_space_is_empty(open_space_coords)) {
				LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
				return EMPTYSPACE;
			} else {
				LOG("The space in between was not empty");
				return NONE;
			}
		}
		LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	}
}

double_type		DoubleThreeCheck::check_right_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords) {
	if(new_coords.x == boundary_coords.x){
		LOG("We are on the same vertical axis");
		if(new_coords.y - boundary_coords.y == 1) {
			LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
			return NORMAL;
		} if(new_coords.y - boundary_coords.y == 2) {
			// check y -1 inbouwen
			LOG("Match Vertical we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
			return EMPTYSPACE;
		}
		LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		return NONE;
	}
}

double_type		DoubleThreeCheck::check_right_boundary_cross(Coordinates boundary_coords, Coordinates new_coords) {
	if((new_coords.y - boundary_coords.y) == 1) {
		LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		if(new_coords.x - boundary_coords.x == 1) {
			LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			LOG("We are a match");
			return NORMAL;
		} if (new_coords.x -boundary_coords.x == 2) {
			LOG("Match Cross we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
			return EMPTYSPACE;
		}
		LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	}
	LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
	return NONE;
}

boundary_check_return DoubleThreeCheck::check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
	boundary_check_return result{};
	if(direction == HORIZONTAL) {
        auto  three_type = check_right_boundary_horizontal(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1, -1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.x = new_coords.x -1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
		return result;
    } else if(direction == VERTICAL) {
		auto three_type = check_right_boundary_vertical(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y - 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
		return result;
    } else if(direction == CROSS) {
		auto three_type = check_right_boundary_cross(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y + 1;
			open_space_coords.x = new_coords.x + 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
			return result;
		}
		return result;
    }
	result.doubleType = NONE;
	result.openSpace = Coordinates{-1,-1};
    LOG("Did not access any right boundary direction checks");
    return result;
}

double_type			DoubleThreeCheck::check_left_boundary_horizontal(Coordinates boundary_coords,
																		Coordinates new_coords)
{
	if(new_coords.y == boundary_coords.y) {
		LOG("We are on the same horizontal axis");
		if(new_coords.x - boundary_coords.x == -1) {
			LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			return NORMAL;
		} if(new_coords.x - boundary_coords.x == -2) {
			LOG("EMPTY SPACE?");
			return EMPTYSPACE;
		}
		LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	}
	return NONE;
}

double_type			DoubleThreeCheck::check_left_boundary_vertical(Coordinates boundary_coords,
																	  Coordinates new_coords)
{
	if(new_coords.x == boundary_coords.x){
		LOG("We are on the same vertical axis");
		if(new_coords.y - boundary_coords.y == -1) {
			LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
			return NORMAL;
		} if (new_coords.y - boundary_coords.y == -2) {
			LOG("");
			return EMPTYSPACE;
		}
		LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		return NONE;
	}
	return NONE;
}

double_type			DoubleThreeCheck::check_left_boundary_cross(Coordinates boundary_coords, Coordinates new_coords)
{
	if((new_coords.y - boundary_coords.y) == -1) {
		LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		if(new_coords.x - boundary_coords.x == -1) {
			LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			LOG("We are a match");
			return NORMAL;
		} if(new_coords.x - boundary_coords.x == -2) {
			return EMPTYSPACE;
		}
		LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	}
	return NONE;
}


boundary_check_return DoubleThreeCheck::check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in left boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
	boundary_check_return result{};
	if(direction == HORIZONTAL) {
		auto three_type = check_left_boundary_horizontal(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.x = new_coords.x + 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
		return result;
	} else if(direction == VERTICAL) {
		auto three_type = check_left_boundary_vertical(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if (three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y + 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
		return result;
	} else if(direction == CROSS) {
		auto three_type = check_left_boundary_cross(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y - 1;
			open_space_coords.x = new_coords.x - 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
		return result;
		LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
    }
	result.doubleType = NONE;
	result.openSpace = Coordinates{-1,-1};
	return result;
}

Threes DoubleThreeCheck::get_last_three() {
	LOG("Kom ik hier?");
    return  _doubleThreeList.back();
}

errorState DoubleThreeCheck::find_double_three() {

    return errorState{};
}
