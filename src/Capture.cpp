//
// Created by Thimo Van der meer on 10/03/2023.
//

#include "Capture.hpp"
#include "logger.hpp"
#include <vector>

Capture::Capture() {
    LOG("Capture constructor");
}

void Capture::checkLeftBoundaryHorizontalCapture(const Coordinate& boundaryCoords) {
    if (_newCoords.y == boundaryCoords.y) {
        LOG("We are on the same horizontal axis");
        LOG("New coords x = %i boundary coords x = %i", _newCoords.x, boundaryCoords.x);
        if (_newCoords.x - boundaryCoords.x == -1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.x, boundaryCoords.x);
            boundaryTrue(LEFT);
        }
    }
    LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", _newCoords.x, boundaryCoords.x);
}

void Capture::checkLeftBoundaryVerticalCapture(const Coordinate& boundaryCoords) {
    if (_newCoords.x == boundaryCoords.x) {
        LOG("We are on the same vertical axis");
        LOG("_newCoords y = %i boundary coords y = %i", _newCoords.y, boundaryCoords.y);
        if (_newCoords.y - boundaryCoords.y == -1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.y, boundaryCoords.y);
            boundaryTrue(LEFT);
        }
    }
}

void Capture::checkLeftBoundaryCrossCapture(const Coordinate& boundaryCoords) {
    LOG("new coords y %i boundary_coors y %i ", _newCoords.y, boundaryCoords.y);
    if ((_newCoords.y - boundaryCoords.y) == -1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", _newCoords.y,
            boundaryCoords.y);
        if (_newCoords.x - boundaryCoords.x == -1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", _newCoords.x,
                boundaryCoords.x);
            LOG("We are a match");
            boundaryTrue(LEFT);
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", _newCoords.x,
            boundaryCoords.x);
    }
}

void Capture::checkRightBoundaryHorizontalCapture(const Coordinate& boundaryCoords) {
    if (_newCoords.y == boundaryCoords.y) {
        LOG("new coords x = %i boundary_coords x = %i", _newCoords.x, boundaryCoords.x);
        if (_newCoords.x - boundaryCoords.x == 1) {
            LOG("Matching capture new[%i] boundary[%i]", _newCoords.x, boundaryCoords.x);
            boundaryTrue(RIGHT);
        }
    }
}

void Capture::checkRightBoundaryVerticalCapture(const Coordinate& boundaryCoords) {
    if (_newCoords.x == boundaryCoords.x) {
        LOG("We are on the same vertical axis");
        if (_newCoords.y - boundaryCoords.y == 1) {
            LOG("Matching new[%i] boundary[%i]", _newCoords.y, boundaryCoords.y);
            boundaryTrue(RIGHT);
        }
        LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", _newCoords.y, boundaryCoords.y);
    }
}

void Capture::checkRightBoundaryCrossCapture(const Coordinate& boundaryCoords) {
    LOG("New coords y = %i", _newCoords.y);
    LOG("boundary coords y = %i", boundaryCoords.y);
    if ((_newCoords.y - boundaryCoords.y) == 1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", _newCoords.y,
            boundaryCoords.y);
        if (_newCoords.x - boundaryCoords.x == 1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", _newCoords.x,
                boundaryCoords.x);
            boundaryTrue(Orientation::RIGHT);
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", _newCoords.x,
            boundaryCoords.x);
    }
    LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", _newCoords.y, boundaryCoords.y);
}


void Capture::checkLeftBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords) {
    if (direction == HORIZONTAL) {
        checkLeftBoundaryHorizontalCapture(boundaryCoords);
    } else if (direction == VERTICAL) {
        checkLeftBoundaryVerticalCapture(boundaryCoords);
        LOG("IK RETURN VERTICAL");
        return;
    } else if (direction == CROSS) {
        checkLeftBoundaryCrossCapture(boundaryCoords);
        LOG("IK RETURN CROSS");
        return;
    }
    // set state
}

void Capture::checkRightBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords) {
    if (direction == HORIZONTAL) {
        checkRightBoundaryHorizontalCapture(boundaryCoords);
        LOG("IK RETURN HORIZONTAL");
        return;
    } else if (direction == VERTICAL) {
        checkRightBoundaryVerticalCapture(boundaryCoords);
        LOG("IK RETURN VERTICAL");
        return;
    } else if (direction == CROSS) {
        checkRightBoundaryCrossCapture(boundaryCoords);
        LOG("IK RETURN CROSS");
        return;
    }
    // set state
}

void Capture::isNewStoneBoundary(const Doubles& elem) {
    checkRightBoundaryCapture(elem.direction, elem.rightBoundaryCoordinates);
    LOG("Wat is boundary hier %i", _boundary.is_boundary);
    LOG("Wat is the orientation hier %i", _boundary.orientation);
    if (not _boundary.is_boundary) {
        LOG("Hier kom ik dus niet");
        checkLeftBoundaryCapture(elem.direction, elem.leftBoundaryCoordinates);
    }
}

bool Capture::isOtherBoundarySameColor(const Doubles& elem) {
    if (elem.direction == HORIZONTAL) {
        LOG("It is horizontal");
        if (_boundary.orientation == RIGHT) {
            LOG("The orientation is right");
            if (static_cast<Player>(_board[elem.leftBoundaryCoordinates.y][elem.leftBoundaryCoordinates.x - 1]) ==
                _player)
                LOG("So we check the other side");
            return true;
        } else {
            if (static_cast<Player>(_board[elem.rightBoundaryCoordinates.y][elem.rightBoundaryCoordinates.x + 1]) ==
                _player) {
                return true;
            }
        }
    } else if (elem.direction == VERTICAL) {
        LOG("Vertical directin");
        if (_boundary.orientation == RIGHT) {
            LOG("RIGHT Orientation");
            LOG("lft boundary coordinate -1 = %i left boundary coordinates x = %i", elem.leftBoundaryCoordinates.y - 1,
                elem.leftBoundaryCoordinates.x);
            if (static_cast<Player>(_board[elem.leftBoundaryCoordinates.y - 1][elem.leftBoundaryCoordinates.x]) ==
                _player) {
                return true;
            }
        } else {
            LOG("Left orientation");
            LOG("lft boundary coordinate y  +1 = %i left boundary coordinates x = %i",
                elem.leftBoundaryCoordinates.y + 1, elem.leftBoundaryCoordinates.x);
            if (static_cast<Player>(_board[elem.rightBoundaryCoordinates.y + 1][elem.rightBoundaryCoordinates.x]) ==
                _player) {
                return true;
            }
        }
    } else if (elem.direction == CROSS) {
        if (_boundary.orientation == RIGHT) {
            if (static_cast<Player>(_board[elem.leftBoundaryCoordinates.y - 1][elem.leftBoundaryCoordinates.x - 1]) ==
                _player) {
                return true;
            }
        } else {
            if (static_cast<Player>(_board[elem.rightBoundaryCoordinates.y + 1][elem.rightBoundaryCoordinates.x + 1]) ==
                _player) {
                return true;
            }
        }
    }
}

State Capture::CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                            const std::vector<std::vector<Tile>>& board, const Player& player) {
    setVariables(doubles, newCoords, board, player);
    LOG("WE start capture check with a double stack size of %i", doubles.size());
    for (auto elem: doubles) {
        isNewStoneBoundary(elem);
        if (_boundary.is_boundary) {
            LOG("We are going to check if the other one is also boundary coords");
            if (isOtherBoundarySameColor(elem)) {
                return State{ACCEPTED, "Valid capture", true, elem};
            }
        }

    }
    return State{ACCEPTED, "No capture", false};
}

void Capture::setVariables(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                           const std::vector<std::vector<Tile>>& board, const Player& player) {
    _doubles = doubles;
    _newCoords = newCoords;
    _board = board;
    _player = player;
    // TODO: hier moet ik eigenlijk een setter van maken want dan kan ik dat in Gmock gebruiken
    _boundary.is_boundary = false;
}

void Capture::boundaryTrue(Orientation orientation) {
    LOG("Returned boundary true");
    _boundary.is_boundary = true;
    _boundary.orientation = orientation;
}




