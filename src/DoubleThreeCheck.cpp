//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"
#include "CommonValidationCode.hpp"

State DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& newCoord,
                                           const Player& player) {
    State result;
    this->setBoard(board);
    auto size = _doubleTwoVector.size();
    if (size > 0) {
        LOG("SIZE OF TWO IS BIGGER THEN 0 first check if this one is close to two block");
        if (this->findThree(newCoord, _doubleTwoVector)) {
            LOG("FOUND THREE");
            if (this->fullFreeCheck()) {
                LOG("OOk hier meoten we in komen bij de first occ");
                LOG("Full free size = %i", _fullFrees);
                if (_fullFrees == 1) {
                    result.errorReason = "second fully free for this player";
                    result.state = OkState::ERROR;
                    return result;
                } else {
                    LOG("KOM IK HIER IN VOORDAT IK ERROR");
                    _fullFrees++;
                    result.errorReason = "This is a valid move";
                    result.state = OkState::ACCEPTED;
                    return result;
                }
            }
        }
    }
    LOG("Checking two in a row");
    if (this->twoInARow(board, newCoord, player)) {
        LOG("Created two in a row so no need to check three in a row");
        result.errorReason = "creating two in a row";
        result.state = ACCEPTED;
        return result;
    }
    LOG("NOT two in a roww and not three in a row so fine regular move");
    result.errorReason = "valid move openfield";
    result.state = ACCEPTED;
    return result;
}

void DoubleThreeCheck::setBoard(const std::vector<std::vector<Tile>>& board) {
    this->_board = board;
}

void DoubleThreeCheck::setState(OkState newState, std::string& errorReason) {
    _state.errorReason = errorReason;
    _state.state = newState;
}

size_t DoubleThreeCheck::doubleTwoSize() {
    return _doubleTwoVector.size();
}

bool DoubleThreeCheck::twoInARow(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& play) {
    auto result = _two->createTwo(board, coord, play);
    LOG("Result = %i", result.rightBoundaryCoordinates.y);
    LOG("Double two list size = %i", _doubleTwoVector.size());
    if (result.rightBoundaryCoordinates.y != -1) {
        LOG("Wordt er uberhaupt iets gepusht?");
        _doubleTwoVector.push_back(result);
        return true;
    }
    return false;
}

Threes DoubleThreeCheck::fillDoubleThreeStack(Coordinate boundCoordinates, Coordinate newCoords,
                                              BoundaryCheckReturn type, bool left, Direction dir) {
    Threes result{};
    result.openSpaceCoordinates = type.openSpace;
    result.direction = dir;
    if (left) {
        result.leftBoundaryCoordinates = newCoords;
        result.rightBoundaryCoordinates = boundCoordinates;
    } else {
        result.leftBoundaryCoordinates = boundCoordinates;
        result.rightBoundaryCoordinates = newCoords;
    }
    if (type.doubleType == NORMAL) {
        result.openSpace = false;
    }
    if (type.doubleType == EMPTYSPACE) {
        result.openSpace = true;
    }
    return result;
}

bool DoubleThreeCheck::findThree(Coordinate newCoords, const std::vector<Doubles>& doubleTwo) {
    LOG("newcoords are %i %i", newCoords.y, newCoords.x);
    for (auto elem: doubleTwo) {
        Threes three_in_a_row{};
        auto result = check_right_boundary(elem.rightBoundaryCoordinates, newCoords, elem.direction, _board);
        if (result.doubleType != NONE) {
            three_in_a_row = fillDoubleThreeStack(elem.leftBoundaryCoordinates, newCoords, result, false,
                                                  elem.direction);
            _doubleThreeVector.push_back(three_in_a_row);
            return true;
        }
        result = check_left_boundary(elem.leftBoundaryCoordinates, newCoords, elem.direction, _board);
        if (result.doubleType != NONE) {
            three_in_a_row = fillDoubleThreeStack(elem.rightBoundaryCoordinates, newCoords, result, true,
                                                  elem.direction);
            _doubleThreeVector.push_back(three_in_a_row);
            return true;
        }
    }
    return false;
}


Threes DoubleThreeCheck::getLastThree() {
    if (not _doubleThreeVector.empty()) {
        return _doubleThreeVector.back();
    } else {
        return {};
    }
}

bool DoubleThreeCheck::fullFreeCheck() {
    auto three = getLastThree();
    if (check_free_left(three.leftBoundaryCoordinates, three.direction, _board) &&
        check_free_right(three.rightBoundaryCoordinates, three.direction, _board)) {
        three.fullFree = true;
        return true;
    } else {
        three.fullFree = false;
        return false;
    }
}

std::vector<Doubles> DoubleThreeCheck::getDoubleTwo() {
    return _doubleTwoVector;
}
