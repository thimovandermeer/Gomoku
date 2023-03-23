//
// Created by Thimo Van der meer on 10/03/2023.
//

#include "Capture.hpp"
#include "logger.hpp"
#include "utils.hpp"
#include <vector>

Capture::Capture() {
    LOG("Capture constructor");
}

void Capture::checkLeftBoundaryHorizontalCapture(const Coordinate& boundaryCoords) {
    if (_newCoords.y == boundaryCoords.y) {
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
    }
}

void Capture::checkRightBoundaryCrossCapture(const Coordinate& boundaryCoords) {
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
}


void Capture::checkLeftBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords) {
    if (direction == HORIZONTAL) {
        checkLeftBoundaryHorizontalCapture(boundaryCoords);
    } else if (direction == VERTICAL) {
        checkLeftBoundaryVerticalCapture(boundaryCoords);
        return;
    } else if (direction == CROSS) {
        checkLeftBoundaryCrossCapture(boundaryCoords);
        return;
    }
    // set state
}

void Capture::checkRightBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords) {
    if (direction == HORIZONTAL) {
        checkRightBoundaryHorizontalCapture(boundaryCoords);
        return;
    } else if (direction == VERTICAL) {
        checkRightBoundaryVerticalCapture(boundaryCoords);
        return;
    } else if (direction == CROSS) {
        checkRightBoundaryCrossCapture(boundaryCoords);
        return;
    }
    // set state
}

void Capture::isNewStoneBoundary(const Doubles& elem) {
    checkRightBoundaryCapture(elem.direction, elem.rightBoundaryCoordinates);
    if (not _boundary.is_boundary) {
        checkLeftBoundaryCapture(elem.direction, elem.leftBoundaryCoordinates);
    }
}

bool Capture::isOtherBoundarySameColor(const Doubles& elem) {
    if (elem.direction == HORIZONTAL) {
        if (_boundary.orientation == RIGHT) {
            if (static_cast<Player>(_board[elem.leftBoundaryCoordinates.y][elem.leftBoundaryCoordinates.x - 1]) ==
                _player) {
                return true;
            }
        } else {
            if (static_cast<Player>(_board[elem.rightBoundaryCoordinates.y][elem.rightBoundaryCoordinates.x + 1]) ==
                _player) {
                return true;
            }
        }
    } else if (elem.direction == VERTICAL) {
        if (_boundary.orientation == RIGHT) {
                elem.leftBoundaryCoordinates.x);
            if (static_cast<Player>(_board[elem.leftBoundaryCoordinates.y - 1][elem.leftBoundaryCoordinates.x]) ==
                _player) {
                return true;
            }
        } else {
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
    return false;
}

State Capture::CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                            const std::vector<std::vector<Tile>>& board, const Player& player) {
    setVariables(doubles, newCoords, board, player);
    for (auto elem: doubles) {
        isNewStoneBoundary(elem);
        if (_boundary.is_boundary) {
            if (isOtherBoundarySameColor(elem)) {
                return State{ACCEPTED, "Valid capture", true, elem};
            }
        }

    }
    return State{ACCEPTED, "No capture", false, {}};
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
    _boundary.is_boundary = true;
    _boundary.orientation = orientation;
}




