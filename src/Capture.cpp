#include <iostream>
#include <vector>
#include "Capture.hpp"
#include "Gomoku.hpp"
// Capture test function
bool Capture::captureLogic(const Coordinate &newCoords,const Tile &player,const std::vector<std::vector<Tile>>& board) {
	// Check for captures in all directions
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			// Skip the center square
			if (dx == 0 && dy == 0) {
				continue;
			}
			// Check for a possible capture
			int i = newCoords.x + dx;
			int j = newCoords.y + dy;
			if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE) {
				continue;
			}
			if (board[i][j] != player && board[i][j] != Tile::EMPTY) {
				int count = 0;
				// Check for a line of enemy pieces
				while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == board[newCoords.x][newCoords.y]) {
					count++;
					i += dx;
					j += dy;
				}
				// Check for a capture
				if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == Tile::EMPTY && count >= 2) {
					// Perform the capture
					i = newCoords.x + dx;
					j = newCoords.y + dy;
					while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == board[newCoords.x][newCoords.y]) {
//						Doubles result;
						// dit moet ik zo nog even fixen
//						board[i][j] = Tile::EMPTY;
						i += dx;
						j += dy;
					}
					return true;
				}
			}
		}
	}
	return false;
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

	captureLogic(newCoords, playerCapture, board);
	return State{};
}
