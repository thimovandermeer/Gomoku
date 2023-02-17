//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include "Validator.hpp"

#define MAX_BOARD_SIZE 19

errorState
Validator::validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    this->set_data(board, coord, player);
    this->board_validation();
    if (_state.state == ERROR)
        return _state;
    this->coordinates_validation();
    if (_state.state == ERROR)
        return _state;
    this->double_three_validation();
    return _state;
}

void Validator::set_data(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    this->set_board(board);
    this->set_coordinates(coord);
    this->set_player(player);
    std::string reason;
    this->set_state(ACCEPTED, reason);
}

void Validator::set_board(const std::vector<std::vector<Tile>>& board) {
    this->_board = board;
}

void Validator::set_coordinates(const Coordinates& coord) {
    this->_coord = coord;
}

void Validator::set_player(const Player& player) {
    this->_player = player;
}

void Validator::board_validation() {
    LOG("Board size = %i", _board.size());
    if (_board.size() > MAX_BOARD_SIZE) {
        LOG("Board is bigger than max size");
        std::string reason = "Board is bigger than max size";
        set_state(ERROR, reason);
    }
}

void Validator::coordinates_validation() {
    LOG("coords x %i coords y %i", _coord.x, _coord.y);
    this->boundary_checking();
    if (_state.state == ERROR)
        return;
    this->taken_check();
}

void Validator::player_validation() {
    //
}

void Validator::boundary_checking() {
    if (_coord.x >= MAX_BOARD_SIZE || _coord.y >= MAX_BOARD_SIZE) {
        LOG("coords is bigger than max board size");
        std::string reason = "coords is bigger than max board size";
        set_state(ERROR, reason);
    }
    if (_coord.x < 0 || _coord.y < 0) {
        LOG("coords is smaller than 0");
        std::string reason = "coords is smaller than 0";
        set_state(ERROR, reason);
    }
}

void Validator::taken_check() {
    LOG("Coordinates %i %i with ", _coord.y, _coord.x);
    if (_board[_coord.y][_coord.x] != Tile::FREE) {
        LOG("Coordinates %i %i are not free", _coord.y, _coord.x);
        std::string reason = "Coordinates are not free";
        set_state(ERROR, reason);
    }
}

void Validator::set_state(State newState, std::string& errorReason) {
    _state.error_reason = errorReason;
    _state.state = newState;
}

void Validator::double_three_validation() {
    _state = _doubleThreeCheck->DoubleThreeChecker(_board, _coord, _player);
}




