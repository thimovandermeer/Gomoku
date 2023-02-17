//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"

errorState DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinates& coord,
                                                const Player& player) {
    this->set_board(board);
    this->two_in_a_row(board, coord, player);
    this->find_three(coord, _doubleTwoList);
    return (this->find_double_three());

}

void DoubleThreeCheck::set_board(const std::vector<std::vector<Tile>>& board) {
    this->_board = board;
}

void DoubleThreeCheck::set_state(State newState, std::string& errorReason) {
    _state.error_reason = errorReason;
    _state.state = newState;
}

// deze moet verplaatst worden naar Two en via een getter verkregen kunnen worden
size_t DoubleThreeCheck::double_two_size() {
    return _doubleTwoList.size();
}

void DoubleThreeCheck::two_in_a_row(const std::vector<std::vector<Tile>>& board, const Coordinates& coord,
                                    const Player& play) {
    _doubleTwoList.push_back(_two->create_two(board, coord, play));
}

bool DoubleThreeCheck::find_three(Coordinates newCoords, std::vector<Doubles>& double_two) {
    LOG("newcoords are %i %i", newCoords.y, newCoords.x);
    for (auto elem: double_two) {
        Threes three_in_a_row{};
        if (check_right_boundary(elem.right_boundary_coordinates, newCoords, elem.direction) != NONE) {
            // dit moet zometeen in een functie om complexiteit te managen
            three_in_a_row.open_space = false;
            three_in_a_row.open_space_coordinates.y = -1;
            three_in_a_row.open_space_coordinates.x = -1;
            three_in_a_row.left_boundary_coordinates = elem.left_boundary_coordinates;
            three_in_a_row.right_boundary_coordinates = newCoords;
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
        if (check_left_boundary(elem.left_boundary_coordinates, newCoords, elem.direction) != NONE) {
            three_in_a_row.left_boundary_coordinates = newCoords;
            three_in_a_row.right_boundary_coordinates = elem.right_boundary_coordinates;
            LOG("Wordt deze nog gepusht?");
            _doubleThreeList.push_back(three_in_a_row);
            return true;
        }
    }
    return false;
}

bool DoubleThreeCheck::open_space_is_empty(Coordinates empty_space) {
    LOG("OPEN SPACE IS EMPTY");
    if (_board[empty_space.y][empty_space.x] == Tile::FREE) {
        return true;
    } else {
        return false;
    }
}

double_type DoubleThreeCheck::check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
    if (direction == HORIZONTAL) {
        if (new_coords.y == boundary_coords.y) {
            LOG("We are on the same horizontal axis");
            if (new_coords.x - boundary_coords.x == 1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
                return NORMAL;
            }
            if (new_coords.x - boundary_coords.x == 2) {
                LOG("Potentially one empty space in between");
                auto open_space_coords = new_coords;
                open_space_coords.x = new_coords.x + 1;
                LOG("OPEN space coords = %i", open_space_coords.x);
                if (open_space_is_empty(open_space_coords)) {
                    LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]",
                        new_coords.x, new_coords.y);
                    return EMPTYSPACE;
                } else {
                    LOG("The space in between was not empty");
                    return NONE;
                }
            }
            LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x,
                boundary_coords.x);
            return NONE;
        }
    } else if (direction == VERTICAL) {
        if (new_coords.x == boundary_coords.x) {
            LOG("We are on the same vertical axis");
            if (new_coords.y - boundary_coords.y == 1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
                return NORMAL;
            }
            if (new_coords.y - boundary_coords.y == 2) {
                // check y -1 inbouwen
                LOG("Match Vertical we create double three with empty space in the middle new[%i] boundary[%i]",
                    new_coords.x, new_coords.y);
                return EMPTYSPACE;
            }
            LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y,
                boundary_coords.y);
            return NONE;
        }
    } else if (direction == CROSS) {
        if ((new_coords.y - boundary_coords.y) == 1) {
            LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y,
                boundary_coords.y);
            if (new_coords.x - boundary_coords.x == 1) {
                LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]",
                    new_coords.x, boundary_coords.x);
                LOG("We are a match");
                return NORMAL;
                // check y -1 inbouwen
            }
            if (new_coords.x - boundary_coords.x == 2) {
                LOG("Match Cross we create double three with empty space in the middle new[%i] boundary[%i]",
                    new_coords.x, new_coords.y);
                return EMPTYSPACE;
            }
            LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x,
                boundary_coords.x);
            return NONE;
        }
        LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y,
            boundary_coords.y);
        return NONE;
    }
    LOG("Did not access any right boundary direction checks");
    return NONE;
}

double_type DoubleThreeCheck::check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction) {
    LOG("boundary_coords in left boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
    if (direction == HORIZONTAL) {
        if (new_coords.y == boundary_coords.y) {
            LOG("We are on the same horizontal axis");
            if (new_coords.x - boundary_coords.x == -1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
                return NORMAL;
            }
            LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x,
                boundary_coords.x);
            return NONE;
        }
    } else if (direction == VERTICAL) {
        if (new_coords.x == boundary_coords.x) {
            LOG("We are on the same vertical axis");
            if (new_coords.y - boundary_coords.y == -1) {
                LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
                return NORMAL;
            }
            LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y,
                boundary_coords.y);
            return NONE;
        }
    } else if (direction == CROSS) {
        if ((new_coords.y - boundary_coords.y) == -1) {
            LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y,
                boundary_coords.y);
            if (new_coords.x - boundary_coords.x == -1) {
                LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]",
                    new_coords.x, boundary_coords.x);
                LOG("We are a match");
                return NORMAL;
            }
            LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x,
                boundary_coords.x);
            return NONE;
        }
        LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y,
            boundary_coords.y);
        return NONE;
    }
    return NONE;
}

Threes DoubleThreeCheck::get_last_three() {
    LOG("Kom ik hier?");
    return _doubleThreeList.back();
}

errorState DoubleThreeCheck::find_double_three() {

    return errorState{};
}
