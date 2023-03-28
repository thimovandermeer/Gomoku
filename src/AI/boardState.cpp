//
// Created by Thimo Van der meer on 27/03/2023.
//

#include "boardState.hpp"

bool BoardState::isValidMove(int row, int col) {
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != Tile::EMPTY) {
		return false;
	}
	return true;
}

void BoardState::makeMove(bestMove move) {
	board[move.bestCoords.y][move.bestCoords.x] = player;
	player = (player == Tile::P1) ? Tile::P2 : Tile::P1;
}


std::vector<bestMove> BoardState::getValidMoves() {
	std::vector<bestMove> moves;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == Tile::EMPTY) {
				moves.push_back(bestMove{{i,j}, -1});
			}
		}
	}
	return moves;
}

bool BoardState::isTerminal() {
	// Check horizontal
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j] != Tile::EMPTY && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3] && board[i][j] == board[i][j+4]) {
				return true;
			}
		}
	}

	// Check vertical
	for (int i = 0; i < BOARD_SIZE - 4; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != Tile::EMPTY && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j] && board[i][j] == board[i+4][j]) {
				return true;
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE - 4; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j] != Tile::EMPTY && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3] && board[i][j] == board[i+4][j+4]) {
				return true;
			}
		}
	}

	// Check diagonal /
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j] != Tile::EMPTY && board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3] && board[i][j] == board[i-4][j+4]) {
				return true;
			}
		}
	}

	// Check for tie game
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == Tile::EMPTY) {
				return false;
			}
		}
	}

	return true;
}

// undoMove
void BoardState::undoMove(bestMove move) {
	board[move.bestCoords.y][move.bestCoords.x] = Tile::EMPTY;
	player = (player == Tile::P1) ? Tile::P2: Tile::P1;
}