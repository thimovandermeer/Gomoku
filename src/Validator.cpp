//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include "Validator.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"

State Validator::validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
	// TODO: Remove this hack
	LOG("WAT DOET DIT");
	auto board_hack = board;
	board_hack[coord.y][coord.x] = static_cast<Tile>(player);
	LOG("The state on the second run is %s", _state.errorReason.c_str());
	_state.state = OkState::ACCEPTED;
    this->boardValidation(board_hack);
    if (_state.state == ERROR) {
		LOG("Error board validation");
        return _state;
    }
    this->coordinatesValidation(coord);
    if (_state.state == ERROR) {
		LOG("COORDINATES VALIDATION ERROR");
        return _state;
    }
	LOG("Kom ik hier wel?");
	this->doubleThreeValidation(board_hack, coord, player);
    if (_state.state == ERROR) {
		LOG("Double three validation should error");
        return _state;
    }

	this->captureValidation(board_hack, coord, player);
	LOG("Doet hij dus niet");

    return _state;
}


void Validator::boardValidation(const std::vector<std::vector<Tile>>& board) {
    if (board.size() > BOARD_SIZE) {
		LOG("Kom ik hier?");
        std::string reason = "Board is bigger than max size";
        setState(ERROR, reason);
    }
}

void Validator::coordinatesValidation(const Coordinate &coords) {
    this->boundaryChecking(coords);
    if (_state.state == ERROR) {
        return;
    }
}

void Validator::boundaryChecking(const Coordinate &coords) {
    if (coords.x >= BOARD_SIZE || coords.y >= BOARD_SIZE) {
        std::string reason = "coords is bigger than max board size";
        setState(ERROR, reason);
    }
    if (coords.x < 0 || coords.y < 0) {
        std::string reason = "coords is smaller than 0";
        setState(ERROR, reason);
    }
}

void Validator::takenCheck(const std::vector<std::vector<Tile>>& board, const Coordinate& coord) {
    if (board[coord.y][coord.x] != Tile::EMPTY) {
        std::string reason = "Coordinates are not free";
        setState(ERROR, reason);
    }
}

void Validator::setState(OkState newState, std::string& errorReason) {
    _state.errorReason = errorReason;
    _state.state = newState;
}

void Validator::doubleThreeValidation(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
	auto result =  _doubleThreeCheck->DoubleThreeChecker(board, coord, player);
	_state = result;
}

void Validator::captureValidation(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    _state = _capture->CaptureCheck( coord, board, player);
}





