//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"

errorState DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &coord,
										  const Player &player)
{
    this->two_in_a_row(board, coord, player);
    this->find_three(coord, _doubleTwoList);
    return (this->find_double_three());

}

void DoubleThreeCheck::set_state(State newState, std::string &errorReason) {
	_state.error_reason = errorReason;
	_state.state = newState;
}

size_t		DoubleThreeCheck::double_two_size() {
	return _doubleTwoList.size();
}

void 		DoubleThreeCheck::two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play)
{
    _doubleTwoList.push_back(_Two->create_two(board, coord, play));
}

bool 		DoubleThreeCheck::find_three(Coordinates newCoords, std::vector<Doubles> &double_two)
{
    LOG("newcoords are %i %i", newCoords.y, newCoords.x);
    for (auto elem : double_two) {
        if(check_right_boundary(elem.right_boundary_coordinates, newCoords, elem.direction)) {
            Doubles three_in_a_row;
            three_in_a_row.left_boundary_coordinates = elem.left_boundary_coordinates;
            three_in_a_row.right_boundary_coordinates = newCoords;
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
        if(check_left_boundary(elem.left_boundary_coordinates, newCoords, elem.direction)) {
            Doubles three_in_a_row;
            three_in_a_row.left_boundary_coordinates = newCoords;
            three_in_a_row.right_boundary_coordinates = elem.right_boundary_coordinates;
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
    }
    return false;
}

bool DoubleThreeCheck::check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
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
    LOG("Did not access any right boundary direction checks");
    return false;
}

bool DoubleThreeCheck::check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in left boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
    if(direction == HORIZONTAL) {
        if(new_coords.y == boundary_coords.y) {
            LOG("We are on the same horizontal axis");
            if(new_coords.x - boundary_coords.x == -1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
                return true;
            }
            LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return false;
        }
    } else if(direction == VERTICAL) {
        if(new_coords.x == boundary_coords.x){
            LOG("We are on the same vertical axis");
            if(new_coords.y - boundary_coords.y == -1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
                return true;
            }
            LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            return false;
        }
    } else if(direction == CROSS) {
        if((new_coords.y - boundary_coords.y) == -1) {
            LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            if(new_coords.x - boundary_coords.x == -1) {
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

Doubles DoubleThreeCheck::get_last_three() {
    return  _doubleThreeList.back();
}

errorState DoubleThreeCheck::find_double_three() {

    return errorState{};
}
