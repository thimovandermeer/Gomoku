//
// Created by Thimo Van der meer on 27/03/2023.
//

#ifndef GOMOKU_BOARDSTATE_HPP
#define GOMOKU_BOARDSTATE_HPP
#include "Gomoku.hpp"
#include "Ai.hpp"

struct bestMove {
	Coordinate 	bestCoords;
	int 		maxScore;
};

class BoardState {
public:
	std::vector<std::vector<Tile>> board;
	Tile player;

	BoardState(std::vector<std::vector<Tile>> board, Player player) :
	board(board), player((Tile)player)
	{
	}

	// Check if a move is valid
	bool isValidMove(int row, int col) {
		if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != Tile::EMPTY) {
			return false;
		}
		return true;
	}

	// Make a move on the board
	void makeMove(bestMove move) {
		board[move.bestCoords.y][move.bestCoords.x] = player;
		player = (player == Tile::P1) ? Tile::P2 : Tile::P1;
	}


	std::vector<bestMove> getValidMoves() {
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

	// Check if the game has ended
	bool isTerminal() {
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

	// Get the current player
	Tile getPlayer() {
		return player;
	}


	// undoMove
	void undoMove(bestMove move) {
		board[move.bestCoords.y][move.bestCoords.x] = Tile::EMPTY;
		player = (player == Tile::P1) ? Tile::P2: Tile::P1;
	}
};

#endif //GOMOKU_BOARDSTATE_HPP
