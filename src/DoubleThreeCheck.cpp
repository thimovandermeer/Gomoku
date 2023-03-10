//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"

errorState DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &new_coord,
										  const Player &player)
{
	errorState result;
    this->set_board(board);
    auto size = _doubleTwoList.size();
    if(size > 0) {
        LOG("SIZE OF TWO IS BIGGER THEN 0 first check if this one is close to two block");
        if(this->find_three(new_coord, _doubleTwoList)) {
            LOG("FOUND THREE");
            if (this->full_free_check()) {
                LOG("OOk hier meoten we in komen bij de first occ");
                LOG("Full free size = %i", _full_frees);
                if (_full_frees == 1) {
                    result.error_reason = "second fully free for this player";
                    result.state = State::ERROR;
                    return result;
                } else {
                    LOG("KOM IK HIER IN VOORDAT IK ERROR");
                    _full_frees++;
                    result.error_reason = "This is a valid move";
                    result.state = State::ACCEPTED;
                    return result;
                }
            }
        }
    }
    LOG("Checking two in a row");
	if(this->two_in_a_row(board, new_coord, player)) {
        LOG("Created two in a row so no need to check three in a row");
        result.error_reason = "creating two in a row";
        result.state = ACCEPTED;
        return result;
    }
    LOG("NOT two in a roww and not three in a row so fine regular move");
    result.error_reason = "valid move openfield";
    result.state = ACCEPTED;
    return result;
}

void DoubleThreeCheck::set_board(const std::vector<std::vector<Tile>> &board) {
	this->_board = board;
}

void DoubleThreeCheck::set_state(State newState, std::string &errorReason) {
	_state.error_reason = errorReason;
	_state.state = newState;
}

size_t		DoubleThreeCheck::double_two_size() {
	return _doubleTwoList.size();
}

bool 		DoubleThreeCheck::two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play)
{
    auto result = _two->create_two(board, coord, play);
    LOG("Result = %i", result.right_boundary_coordinates.y);
    LOG("Double two list size = %i", _doubleTwoList.size());
    if(result.right_boundary_coordinates.y != -1) {
        LOG("Wordt er uberhaupt iets gepusht?");
        _doubleTwoList.push_back(result);
        return true;
    }
    return false;
}

Threes		DoubleThreeCheck::fill_double_three_stack(Coordinates bound_coordinates, Coordinates newCoords,
														boundary_check_return type, bool left, Direction dir)
{
	Threes result;
	result.open_space_coordinates = type.openSpace;
    result.direction = dir;
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
			three_in_a_row = fill_double_three_stack(elem.left_boundary_coordinates, newCoords, result, false, elem.direction);
			_doubleThreeList.push_back(three_in_a_row);
            return true;
        }
		result = check_left_boundary(elem.left_boundary_coordinates, newCoords, elem.direction);
        if(result.doubleType != NONE) {
			three_in_a_row = fill_double_three_stack(elem.right_boundary_coordinates, newCoords, result, true, elem.direction);
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
    }
    return false;
}

bool		DoubleThreeCheck::open_space_is_empty(Coordinates empty_space) {
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
    return NONE;
}

double_type		DoubleThreeCheck::check_right_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords) {
	if(new_coords.x == boundary_coords.x){
		LOG("We are on the same vertical axis");
		if(new_coords.y - boundary_coords.y == 1) {
			LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
			return NORMAL;
		} if(new_coords.y - boundary_coords.y == 2) {
			LOG("Match Vertical we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
			return EMPTYSPACE;
		}
		LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		return NONE;
	}
    LOG("ERROR FOUND");
    return NONE;
}

double_type		DoubleThreeCheck::check_right_boundary_cross(Coordinates boundary_coords, Coordinates new_coords) {
    LOG("New coords y = %i", new_coords.y);
    LOG("boundary coords y = %i", boundary_coords.y);
	if((new_coords.y - boundary_coords.y) == 1) {
		LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		if(new_coords.x - boundary_coords.x == 1) {
			LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			return NORMAL;
		}
		LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	} else if ((new_coords.y - boundary_coords.y) == 2) {
        LOG("Potentially a match");
        if (new_coords.x - boundary_coords.x == 2) {
            LOG("Match Cross we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x,
                new_coords.y);
            return EMPTYSPACE;
        }
    }
	LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
	return NONE;
}

boundary_check_return DoubleThreeCheck::check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Wat is de DIR %i", direction);
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
        LOG("IK RETURN HORIZONTAL");
		return result;
    } else if(direction == VERTICAL) {
		auto three_type = check_right_boundary_vertical(boundary_coords, new_coords);
        LOG("THREE TYPE = %I", three_type);
        result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y - 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
		}
        LOG("WAT RETURN IK UBERHAUPT %i", result);
        LOG("IK RETURN VERTICAL");
		return result;
    } else if(direction == CROSS) {
		auto three_type = check_right_boundary_cross(boundary_coords, new_coords);
		result.doubleType = three_type;
		result.openSpace = Coordinates{-1,-1};
		if(three_type == EMPTYSPACE) {
			auto open_space_coords = new_coords;
			open_space_coords.y = new_coords.y - 1;
			open_space_coords.x = new_coords.x - 1;
			result.openSpace = open_space_coords;
			result.doubleType = three_type;
			return result;
		}
        LOG("IK RETURN CROSS");
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
    LOG("new coords y %i boundary_coors y %i ", new_coords.y, boundary_coords.y);
	if((new_coords.y - boundary_coords.y) == -1) {
		LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
		if(new_coords.x - boundary_coords.x == -1) {
			LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
			LOG("We are a match");
			return NORMAL;
		}
		LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
		return NONE;
	}else if ((new_coords.y - boundary_coords.y) == -2) {
        LOG("Potential with open space");
        if(new_coords.x - boundary_coords.x == -2) {
            return EMPTYSPACE;
        }
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
			open_space_coords.y = new_coords.y + 1;
			open_space_coords.x = new_coords.x + 1;
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
    return  _doubleThreeList.back();
}

bool DoubleThreeCheck::check_free_left(Coordinates left_boundary, Direction dir) {
    if(dir == HORIZONTAL) {
        if(_board[left_boundary.y][left_boundary.x - 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == VERTICAL) {
        if(_board[left_boundary.y - 1][left_boundary.x] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == CROSS) {
        if(_board[left_boundary.y - 1][left_boundary.x -1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
}

bool DoubleThreeCheck::check_free_right(Coordinates right_boundary, Direction dir) {
    if(dir == HORIZONTAL) {
        if(_board[right_boundary.y][right_boundary.x + 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == VERTICAL) {
        if(_board[right_boundary.y + 1][right_boundary.x] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == CROSS) {
        if(_board[right_boundary.y + 1][right_boundary.x + 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
}

bool        DoubleThreeCheck::full_free_check() {
    auto three = get_last_three();
    if (check_free_left(three.left_boundary_coordinates, three.direction) && check_free_right(three.right_boundary_coordinates, three.direction)) {
        three.full_free = true;
        return true;
    } else {
        three.full_free = false;
        return false;
    }
}

std::vector<Doubles> DoubleThreeCheck::get_double_two() {
    return _doubleTwoList;
}
