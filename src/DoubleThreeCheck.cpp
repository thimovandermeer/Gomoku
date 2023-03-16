//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"
#include "CommonValidationCode.hpp"


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
		auto result = check_right_boundary(elem.right_boundary_coordinates, newCoords, elem.direction, _board);
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




Threes DoubleThreeCheck::get_last_three() {
    return  _doubleThreeList.back();
}

bool        DoubleThreeCheck::full_free_check() {
    auto three = get_last_three();
    if (check_free_left(three.left_boundary_coordinates, three.direction, _board) && check_free_right(three.right_boundary_coordinates, three.direction, _board)) {
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
