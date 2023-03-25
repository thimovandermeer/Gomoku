#include <iostream>
#include <vector>
#include "Capture.hpp"
#include "Gomoku.hpp"
#include "logger.hpp"

// Capture test function

State Capture::captureLogic(const Coordinate &newCoords, const Tile &player, const std::vector<std::vector<Tile>>& board) {
	Tile opponent = (player == Tile::P1) ? Tile::P2 : Tile::P1;

	// Check for horizontal captures
	if (newCoords.x > 1 && board[newCoords.y][newCoords.x-2] == opponent && board[newCoords.y][newCoords.x-1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("Before last validation step");
		if(board[newCoords.y][newCoords.x -3] == player) {
			LOG("first horizontal if");
			Coordinate one{newCoords.y, newCoords.x-2};
			Coordinate two{newCoords.y, newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid horizontal capture", true, doubles};
			return return_value;
		}
	}
	if (newCoords.x < BOARD_SIZE-2 && board[newCoords.y][newCoords.x+2] == opponent && board[newCoords.y][newCoords.x+1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("Second horizontal if");
		if(board[newCoords.y][newCoords.x +3] == player) {
			Coordinate one{newCoords.y, newCoords.x+2};
			Coordinate two{newCoords.y, newCoords.x+1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid horizontal capture", true, doubles};
			return return_value;
		}
	}

	// Check for vertical captures
	if (newCoords.y > 1 && board[newCoords.y-2][newCoords.x] == opponent && board[newCoords.y-1][newCoords.x] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("First vertical if");
		if(board[newCoords.y -3][newCoords.x] == player) {
			Coordinate one{newCoords.y -2, newCoords.x};
			Coordinate two{newCoords.y -1, newCoords.x};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid vertical capture", true, doubles};
			return return_value;
		}
	}
	if (newCoords.y < BOARD_SIZE-2 && board[newCoords.y+2][newCoords.x] == opponent && board[newCoords.y+1][newCoords.x] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("Second vertical if");
		if(board[newCoords.y +3][newCoords.x] == player) {
			Coordinate one{newCoords.y +2, newCoords.x};
			Coordinate two{newCoords.y +1, newCoords.x};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid vertical capture", true, doubles};
			return return_value;
		}
	}

	// Check for diagonal captures
	if (newCoords.y > 1 && newCoords.x > 1 && board[newCoords.y-2][newCoords.x-2] == opponent && board[newCoords.y-1][newCoords.x-1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("First diagonal if");
		if(board[newCoords.y -3][newCoords.x-3] == player) {
			Coordinate one{newCoords.y -2, newCoords.x-2};
			Coordinate two{newCoords.y -1, newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}

	}
	if (newCoords.y > 1 && newCoords.x < BOARD_SIZE-2 && board[newCoords.y-2][newCoords.x+2] == opponent && board[newCoords.y-1][newCoords.x+1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("second diagonal if");
		if(board[newCoords.y -3][newCoords.x+3] == player) {
			Coordinate one{newCoords.y -2, newCoords.x-2};
			Coordinate two{newCoords.y -1, newCoords.x-1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}
	}
	if (newCoords.y < BOARD_SIZE-2 && newCoords.x > 1 && board[newCoords.y+2][newCoords.x-2] == opponent && board[newCoords.y+1][newCoords.x-1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("third diagonal if");
		if(board[newCoords.y +3][newCoords.x-3] == player) {
			Coordinate one{newCoords.y + 2, newCoords.x - 2};
			Coordinate two{newCoords.y + 1, newCoords.x - 1};
			auto doubles = Doubles{one, two};
			State return_value{ACCEPTED, "Valid diagonal capture", true, doubles};
			return return_value;
		}
	}
	if (newCoords.y < BOARD_SIZE-2 && newCoords.x < BOARD_SIZE-2 && board[newCoords.y+2][newCoords.x+2] == opponent && board[newCoords.y+1][newCoords.x+1] == opponent && board[newCoords.y][newCoords.x] == player) {
		LOG("Fourth diagonal if");
		if(board[newCoords.y +3][newCoords.x+3] == player) {
			Coordinate one{newCoords.y +2, newCoords.x+2};
			Coordinate two{newCoords.y +1, newCoords.x+1};
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

	auto result = captureLogic(newCoords, playerCapture, board);
	LOG("Result = %s",result.errorReason.c_str());
	return result;
}
