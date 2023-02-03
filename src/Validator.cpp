//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include <iostream>
#include "../inc/Validator.hpp"

#define MAX_BOARD_SIZE 19
#include "logger.hpp"
#include "Gomoku.hpp"

State Validator::validate(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) {
    this->set_data(board, coord, player);
    this->board_validation();
    if(_state == ERROR)
        return _state;
    this->coordinates_validation();
    return _state;
}

void Validator::set_data(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player &player) {
    this->set_board(board);
    this->set_coordinates(coord);
    this->set_player(player);
    this->set_state(ACCEPTED);
}

void Validator::set_board(const std::vector<std::vector<Tile>> &board) {
    this->_board = board;
}

void Validator::set_coordinates(const Coordinates &coord) {
    this->_coord = coord;
}

void Validator::set_player(const Player &player) {
    this->_player = player;
}

void Validator::board_validation() {
    if(_board.size() > MAX_BOARD_SIZE){
        LOG("Board is bigger than max size");
        set_state(ERROR);
    }
}

void Validator::coordinates_validation() {
    LOG("coords x %i coords y %i", _coord.x, _coord.y);
    this->boundary_checking();
    if(_state == ERROR)
        return;
    LOG("KOM IK UBERHAUPT BY DE TAKEN CHECK");
    this->taken_check();
}

void Validator::player_validation() {
    //
}

void Validator::boundary_checking() {
    if(_coord.x >= MAX_BOARD_SIZE || _coord.y >= MAX_BOARD_SIZE) {
        LOG("coords is bigger than max board size");
        set_state(ERROR);
    }
    if (_coord.x < 0 || _coord.y < 0) {
        LOG("coords is smaller than 0");
        set_state(ERROR);
    }
}

void Validator::taken_check() {
    LOG("Coordinates %i %i with ", _coord.y, _coord.x);
    if( _board[_coord.y][_coord.x] != Tile::FREE) {
        LOG("Coordinates %i %i are not free", _coord.y, _coord.x);
        set_state(ERROR);
    }
}

void Validator::set_state(State newState) {
    _state = newState;
}




