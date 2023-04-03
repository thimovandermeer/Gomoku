//
// Created by Thimo Van der meer on 27/03/2023.
//

#include <unistd.h>
#include "boardState.hpp"
#include "utils.hpp"
#include "logger.hpp"

void BoardState::setBoard(std::vector<std::vector<Tile>> boardOut)
{
//	TileAi tile = {Tile::EMPTY, false};
	board = std::vector<std::vector<TileAi>>(BOARD_SIZE, std::vector<TileAi>(BOARD_SIZE));
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if(boardOut[y][x] == Tile::P1) {
				board[y][x] = TileAi{Tile::P1, false};
			}
			else if(boardOut[y][x] == Tile::P2) {
				board[y][x] = TileAi{Tile::P2, false};
			} else {
				board[y][x] = TileAi{Tile::EMPTY, true};
			}
		}
	}
//	printBoardAi(board);
}

bool BoardState::isValidMove(int row, int col) {
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col].pos != Tile::EMPTY) {
		return false;
	}
	return true;
}

bool BoardState::makeMove(Coordinate move) {
	if(board[move.y][move.x].Removable == true) {
		board[move.y][move.x].pos = player;
		return true;
	}
	return false;
}


std::vector<Coordinate> BoardState::getValidMoves() {
	std::vector<Coordinate> moves;
//	printBoard(board);
	for (int y= 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if (board[y][x].pos == Tile::EMPTY) {
				if(board[y][x].Removable){
					moves.push_back({x, y});
				} else {
					WARN("Is unremovable [%i] [%i]", y,x);
				}
			}
		}
	}
	return moves;
}

bool BoardState::isTerminal() {
	// Check horizontal
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j].pos != Tile::EMPTY && board[i][j].pos == board[i][j+1].pos && board[i][j].pos == board[i][j+2].pos && board[i][j].pos == board[i][j+3].pos && board[i][j].pos == board[i][j+4].pos) {
				return true;
			}
		}
	}

	// Check vertical
	for (int i = 0; i < BOARD_SIZE - 4; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].pos != Tile::EMPTY && board[i][j].pos == board[i+1][j].pos && board[i][j].pos == board[i+2][j].pos && board[i][j].pos == board[i+3][j].pos && board[i][j].pos == board[i+4][j].pos) {
				return true;
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE - 4; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j].pos != Tile::EMPTY && board[i][j].pos == board[i+1][j+1].pos && board[i][j].pos == board[i+2][j+2].pos && board[i][j].pos == board[i+3][j+3].pos && board[i][j].pos == board[i+4][j+4].pos) {
				return true;
			}
		}
	}

	// Check diagonal /
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE - 4; j++) {
			if (board[i][j].pos != Tile::EMPTY && board[i][j].pos == board[i-1][j+1].pos && board[i][j].pos == board[i-2][j+2].pos && board[i][j].pos == board[i-3][j+3].pos && board[i][j].pos == board[i-4][j+4].pos) {
				return true;
			}
		}
	}

	// Check for tie game
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].pos == Tile::EMPTY) {
				return false;
			}
		}
	}
	ERROR("State Terminal reached this would be bad");
	return true;
}

// undoMove
void BoardState::undoMove(bestMove move) {
	if(board[move.bestCoords.y][move.bestCoords.x].Removable == true) {
		board[move.bestCoords.y][move.bestCoords.x].pos = Tile::EMPTY;
	}
}