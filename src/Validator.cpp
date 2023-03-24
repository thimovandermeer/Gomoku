//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include "Validator.hpp"
#include "logger.hpp"

State Validator::validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player,
                          const std::vector<Doubles>& opponentDoubles) {
    this->setData(board, coord, player);
    this->boardValidation();
    LOG("OPPONENT DOUBLES SIZE = %i", opponentDoubles.size());
    this->setOpponentDoubles(opponentDoubles);
    if (_state.state == ERROR) {
        return _state;
    }
    this->coordinatesValidation();
    if (_state.state == ERROR) {
        return _state;
    }
    this->doubleThreeValidation();
    if (_state.state == ERROR) {
        return _state;
    }
    updateDoubleList();
    this->captureValidation();


    return _state;
}

void Validator::setData(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    this->setBoard(board);
    this->setCoordinates(coord);
    this->setPlayer(player);
    std::string reason;
    this->setState(ACCEPTED, reason);
}

void Validator::setBoard(const std::vector<std::vector<Tile>>& board) {
    this->_board = board;
}

void Validator::setCoordinates(const Coordinate& coord) {
    this->_coord = coord;
}

void Validator::setPlayer(const Player& player) {
    this->_player = player;
}

void Validator::boardValidation() {
    if (_board.size() > BOARD_SIZE) {
        std::string reason = "Board is bigger than max size";
        setState(ERROR, reason);
    }
}

void Validator::coordinatesValidation() {
    this->boundaryChecking();
    if (_state.state == ERROR) {
        return;
    }
}

void Validator::playerValidation() {
    //
}

void Validator::boundaryChecking() {
    if (_coord.x >= BOARD_SIZE || _coord.y >= BOARD_SIZE) {
        std::string reason = "coords is bigger than max board size";
        setState(ERROR, reason);
    }
    if (_coord.x < 0 || _coord.y < 0) {
        std::string reason = "coords is smaller than 0";
        setState(ERROR, reason);
    }
}

void Validator::setState(OkState newState, std::string& errorReason) {
    _state.errorReason = errorReason;
    _state.state = newState;
}

void Validator::doubleThreeValidation() {
    _state = _doubleThreeCheck->DoubleThreeChecker(_board, _coord, _player);
}

void Validator::captureValidation() {
    _state = _capture->CaptureCheck(_opponentDoubles, _coord, _board, _player);
}

void Validator::updateDoubleList() {
    _doubleVector = _doubleThreeCheck->getDoubleTwo();
}

void Validator::setOpponentDoubles(const std::vector<Doubles>& opponentDoubles) {
    this->_opponentDoubles = opponentDoubles;
}

std::vector<Doubles> Validator::getDoubleTwoList() {
    return _doubleVector;
}



