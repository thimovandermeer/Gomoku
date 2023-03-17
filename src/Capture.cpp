//
// Created by Thimo Van der meer on 10/03/2023.
//

#include "Capture.hpp"
#include "logger.hpp"
#include <vector>

Capture::Capture() {
    LOG("Capture constructor");
}


void Capture::check_left_boundary_horizontal_capture(const Coordinate &boundary_coords) {
    if (_newCoords.y == boundary_coords.y) {
        LOG("We are on the same horizontal axis");
        LOG("New coords x = %i boundary coords x = %i", _newCoords.x, boundary_coords.x);
        if (_newCoords.x - boundary_coords.x == -1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.x, boundary_coords.x);
            boundary_true(LEFT);
        }
    }
    LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", _newCoords.x, boundary_coords.x);
}

void Capture::check_left_boundary_vertical_capture(const Coordinate &boundary_coords) {
    if (_newCoords.x == boundary_coords.x) {
        LOG("We are on the same vertical axis");
        LOG("_newCoords y = %i boundary coords y = %i", _newCoords.y, boundary_coords.y);
        if (_newCoords.y - boundary_coords.y == -1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
            boundary_true(LEFT);
        }
    }
}

void Capture::check_left_boundary_cross_capture(const Coordinate &boundary_coords) {
    LOG("new coords y %i boundary_coors y %i ", _newCoords.y, boundary_coords.y);
    if ((_newCoords.y - boundary_coords.y) == -1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
        if (_newCoords.x - boundary_coords.x == -1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", _newCoords.x,
                boundary_coords.x);
            LOG("We are a match");
            boundary_true(LEFT);
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", _newCoords.x,
            boundary_coords.x);
    }
}

void Capture::check_right_boundary_horizontal_capture(const Coordinate &boundary_coords) {
    if (_newCoords.y == boundary_coords.y) {
        LOG("new coords x = %i boundary_coords x = %i", _newCoords.x, boundary_coords.x);
        if (_newCoords.x - boundary_coords.x == 1) {
            LOG("Matching capture new[%i] boundary[%i]", _newCoords.x, boundary_coords.x);
            boundary_true(RIGHT);
        }
    }
}

void Capture::check_right_boundary_vertical_capture(const Coordinate &boundary_coords) {
    if (_newCoords.x == boundary_coords.x) {
        LOG("We are on the same vertical axis");
        if (_newCoords.y - boundary_coords.y == 1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
            boundary_true(RIGHT);
        }
        LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
    }
}

void Capture::check_right_boundary_cross_capture(const Coordinate &boundary_coords) {
    LOG("New coords y = %i", _newCoords.y);
    LOG("boundary coords y = %i", boundary_coords.y);
    if ((_newCoords.y - boundary_coords.y) == 1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
        if (_newCoords.x - boundary_coords.x == 1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", _newCoords.x,
                boundary_coords.x);
            boundary_true(Orientation::RIGHT);
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", _newCoords.x,
            boundary_coords.x);
    }
    LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", _newCoords.y, boundary_coords.y);
}



void Capture::check_left_boundary_capture(const Direction &direction, const Coordinate &boundary_coords) {
    if (direction == HORIZONTAL) {
        check_left_boundary_horizontal_capture(boundary_coords);
    } else if (direction == VERTICAL) {
        check_left_boundary_vertical_capture(boundary_coords);
        LOG("IK RETURN VERTICAL");
        return ;
    } else if (direction == CROSS) {
        check_left_boundary_cross_capture(boundary_coords);
        LOG("IK RETURN CROSS");
        return ;
    }
    // set state
}

void Capture::check_right_boundary_capture(const Direction &direction, const  Coordinate &boundary_coords) {
    if (direction == HORIZONTAL) {
        check_right_boundary_horizontal_capture(boundary_coords);
        LOG("IK RETURN HORIZONTAL");
        return ;
    } else if (direction == VERTICAL) {
        check_right_boundary_vertical_capture(boundary_coords);
        LOG("IK RETURN VERTICAL");
        return ;
    } else if (direction == CROSS) {
        check_right_boundary_cross_capture(boundary_coords);
        LOG("IK RETURN CROSS");
        return ;
    }
    // set state
}

void    Capture::is_new_stone_boundary(const Doubles &elem) {
    check_right_boundary_capture(elem.direction, elem.rightBoundaryCoordinates);
    LOG("Wat is boundary hier %i", _boundary.is_boundary);
    LOG("Wat is the orientation hier %i", _boundary.orientation);
    if(not _boundary.is_boundary) {
        LOG("Hier kom ik dus niet");
        check_left_boundary_capture(elem.direction, elem.leftBoundaryCoordinates);
    }
}

bool Capture::is_other_boundary_same_color(const Doubles &elem) {
    if(elem.direction == HORIZONTAL) {
        LOG("It is horizontal");
        if (_boundary.orientation == RIGHT) {
            LOG("The orientation is right");
            if(static_cast<Player>(_board[elem.leftBoundaryCoordinates.y][elem.leftBoundaryCoordinates.x - 1]) == _player)
                LOG("So we check the other side");
                return true;
        } else {
            if(static_cast<Player>(_board[elem.rightBoundaryCoordinates.y][elem.rightBoundaryCoordinates.x + 1]) == _player) {
                return true;
            }
        }
    } else if(elem.direction == VERTICAL) {
        LOG("Vertical directin");
        if(_boundary.orientation == RIGHT) {
            LOG("RIGHT Orientation");
            LOG("lft boundary coordinate -1 = %i left boundary coordinates x = %i", elem.leftBoundaryCoordinates.y - 1, elem.leftBoundaryCoordinates.x);
            if(static_cast<Player>(_board[elem.leftBoundaryCoordinates.y - 1][elem.leftBoundaryCoordinates.x]) == _player) {
                return true;
            }
        } else {
            LOG("Left orientation");
            LOG("lft boundary coordinate y  +1 = %i left boundary coordinates x = %i", elem.leftBoundaryCoordinates.y + 1, elem.leftBoundaryCoordinates.x);
            if (static_cast<Player>(_board[elem.rightBoundaryCoordinates.y + 1][elem.rightBoundaryCoordinates.x]) == _player)
                return  true;
        }
    } else if (elem.direction == CROSS) {
        if(_boundary.orientation == RIGHT) {
            if(static_cast<Player>(_board[elem.leftBoundaryCoordinates.y - 1][elem.leftBoundaryCoordinates.x - 1]) == _player) {
                return true;
            }
        } else {
            if(static_cast<Player>(_board[elem.rightBoundaryCoordinates.y + 1][elem.rightBoundaryCoordinates.x + 1]) == _player) {
                return true;
            }
        }
    }
}

State Capture::CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                            const std::vector<std::vector<Tile>>& board, const Player &player) {
    set_variables(doubles, newCoords, board, player);
    for (auto elem: doubles) {
        is_new_stone_boundary(elem);
        if(_boundary.is_boundary) {
            LOG("We are going to check if the other one is also boundary coords");
            if(is_other_boundary_same_color(elem)) {
                return State{ACCEPTED, "Valid capture", true, elem};
            }
        }

    }
    return State{ACCEPTED, "No capture", false};
}

void Capture::set_variables(const std::vector<Doubles> &doubles, const Coordinate &newCoords,
                            const std::vector<std::vector<Tile>> &board, const Player &player) {
    _doubles = doubles;
    _newCoords = newCoords;
    _board = board;
    _player = player;
    // TODO: hier moet ik eigenlijk een setter van maken want dan kan ik dat in Gmock gebruiken
    _boundary.is_boundary = false;
}

void Capture::boundary_true(Orientation orientation) {
    LOG("Returned boundary true");
    _boundary.is_boundary = true;
    _boundary.orientation = orientation;
}




