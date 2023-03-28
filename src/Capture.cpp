#include <iostream>
#include <vector>
#include "Capture.hpp"
#include "Gomoku.hpp"
#include "logger.hpp"

// Capture test function

bool Capture::checkLeftHorizontal() {
	return(_newCoords.x > 1 && _board[_newCoords.y][_newCoords.x-2] == _opponent && _board[_newCoords.y][_newCoords.x-1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkRightHorizontal() {
	return (_newCoords.x < BOARD_SIZE-2 && _board[_newCoords.y][_newCoords.x+2] == _opponent && _board[_newCoords.y][_newCoords.x+1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkLeftVertical()
{
	return(_newCoords.y > 1 && _board[_newCoords.y-2][_newCoords.x] == _opponent && _board[_newCoords.y-1][_newCoords.x] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkRightVertical()
{
	return(_newCoords.y < BOARD_SIZE-2 && _board[_newCoords.y+2][_newCoords.x] == _opponent && _board[_newCoords.y+1][_newCoords.x] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkDiagonalLeftDown()
{
	return(_newCoords.y > 1 && _newCoords.x > 1 && _board[_newCoords.y-2][_newCoords.x-2] == _opponent && _board[_newCoords.y-1][_newCoords.x-1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkDiagonalLeftUp()
{
	return(_newCoords.y > 1 && _newCoords.x < BOARD_SIZE-2 && _board[_newCoords.y-2][_newCoords.x+2] == _opponent && _board[_newCoords.y-1][_newCoords.x+1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkDiagonalRightDown()
{
	return(_newCoords.y < BOARD_SIZE-2 && _newCoords.x > 1 && _board[_newCoords.y+2][_newCoords.x-2] == _opponent && _board[_newCoords.y+1][_newCoords.x-1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

bool Capture::checkDiagonalRightUp()
{
	return(_newCoords.y < BOARD_SIZE-2 && _newCoords.x < BOARD_SIZE-2 && _board[_newCoords.y+2][_newCoords.x+2] == _opponent && _board[_newCoords.y+1][_newCoords.x+1] == _opponent && _board[_newCoords.y][_newCoords.x] == _player);
}

void	Capture::setVars(const Coordinate &newCoords, const Tile &player, const std::vector<std::vector<Tile>> &board)
{
	_newCoords = newCoords;
	_player = player;
	_opponent= (player == Tile::P1) ? Tile::P2 : Tile::P1;
	_board = board;
}
State Capture::captureLogic() {

	// Check for horizontal captures
	if (checkLeftHorizontal()) {
		LOG("Before last validation step");
		if(_board[_newCoords.y][_newCoords.x -3] == _player) {
			LOG("first horizontal if");
			Coordinate one{_newCoords.y, _newCoords.x-2};
			Coordinate two{_newCoords.y, _newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid horizontal capture", true, doubles};
			return return_value;
		}
	}
	if (checkRightHorizontal()) {
		LOG("Second horizontal if");
		if(_board[_newCoords.y][_newCoords.x +3] == _player) {
			Coordinate one{_newCoords.y, _newCoords.x+2};
			Coordinate two{_newCoords.y, _newCoords.x+1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid horizontal capture", true, doubles};
			return return_value;
		}
	}

	// Check for vertical captures
	if (checkLeftVertical()) {
		LOG("First vertical if");
		if(_newCoords.y -3 > 0 && _board[_newCoords.y -3][_newCoords.x] == _player) {
			Coordinate one{_newCoords.y -2, _newCoords.x};
			Coordinate two{_newCoords.y -1, _newCoords.x};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid vertical capture", true, doubles};
			return return_value;
		}
	}
	if (checkRightVertical()) {
		LOG("Second vertical if");
		if(_newCoords.y + 3 < BOARD_SIZE && _board[_newCoords.y +3][_newCoords.x] == _player) {
			Coordinate one{_newCoords.y +2, _newCoords.x};
			Coordinate two{_newCoords.y +1, _newCoords.x};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid vertical capture", true, doubles};
			return return_value;
		}
	}

	// Check for diagonal captures
	if (checkDiagonalLeftDown()) {
		LOG("First diagonal if");
		if(_newCoords.y -3 > 0 && _board[_newCoords.y -3][_newCoords.x-3] == _player) {
			Coordinate one{_newCoords.y -2, _newCoords.x-2};
			Coordinate two{_newCoords.y -1, _newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}

	}
	if (checkDiagonalLeftUp()) {
		LOG("second diagonal if");
		if(_newCoords.y -3 > 0 && _board[_newCoords.y -3][_newCoords.x+3] == _player) {
			Coordinate one{_newCoords.y -2, _newCoords.x-2};
			Coordinate two{_newCoords.y -1, _newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}
	}
	if (checkDiagonalRightDown()) {
		LOG("third diagonal if");
		if(_board[_newCoords.y +3][_newCoords.x-3] == _player) {
			Coordinate one{_newCoords.y + 2, _newCoords.x - 2};
			Coordinate two{_newCoords.y + 1, _newCoords.x - 1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}
	}
	if (checkDiagonalRightUp()) {
		LOG("Fourth diagonal if");
		if(_board[_newCoords.y +3][_newCoords.x+3] == _player) {
			Coordinate one{_newCoords.y +2, _newCoords.x+2};
			Coordinate two{_newCoords.y +1, _newCoords.x+1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}
	}
	// No capture found
	return (State{ACCEPTED, "No capture found", false, {}});
}

State
Capture::CaptureCheck(const Coordinate &newCoords, const std::vector<std::vector<Tile>> &board, const Player &player)
{
	Tile playerCapture;
	if(player == Player::PLAYERONE) {
		playerCapture = Tile::P1;
	} else {
		playerCapture = Tile::P2;
	}
	setVars(newCoords,playerCapture, board);

	auto result = captureLogic();
	LOG("Result = %s",result.errorReason.c_str());
	return result;
}

