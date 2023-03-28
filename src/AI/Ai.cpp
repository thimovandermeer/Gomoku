//
// Created by Thimo Van der meer on 27/03/2023.
//

#include <cmath>
#include "Ai.hpp"
#include "Gomoku.hpp"
#include "utils.hpp"
#include "logger.hpp"

#define DEPTH 4



AiResponse Ai::AiMove(const std::vector<std::vector<Tile>>& board,const Player &player)
{
	LOG("Entry point of AI");
	BoardState state{board, player};
	bool maximizingPlayer = false;
	if(player == Player::PLAYERONE) {
		maximizingPlayer = true;
	} else {
		maximizingPlayer = false;
	}
	auto score = miniMax(state, DEPTH, INT_MIN, INT_MAX, maximizingPlayer);
	LOG("Minimax Score = %i", score);
	LOG("Next coordinates proposed by AI [%i][%i]", score.bestCoords.y, score.bestCoords.x);
	return (AiResponse{"Valid ai move", score});

}

int Ai::evaluateOwnMoves(const std::vector<std::vector<Tile>> &board, Tile player)
{
	int score = 0;
	// Evaluate the board based on potential win conditions for the AI
	// 1. Check horizontal lines
	for (int i = 0; i < BOARD_SIZE; i++) {
		int count = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == player) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score += 1000;
			} else if (count == 4) {
				score += 100;
			} else if (count == 3) {
				score += 10;
			} else if (count == 2) {
				score += 1;
			}
		}
	}

	// 2. Check vertical lines
	for (int j = 0; j < BOARD_SIZE; j++) {
		int count = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (board[i][j] == player) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score += 1000;
			} else if (count == 4) {
				score += 100;
			} else if (count == 3) {
				score += 10;
			} else if (count == 2) {
				score += 1;
			}
		}
	}

	// 3. Check diagonal lines (top-left to bottom-right)
	for (int i = 0; i <= BOARD_SIZE - 5; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i+k][j+k] == player) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score += 1000;
			} else if (count == 4) {
				score += 100;
			} else if (count == 3) {
				score += 10;
			} else if (count == 2) {
				score += 1;
			}
		}
	}

	// 4. Check diagonal lines (bottom-left to top-right)
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i-k][j+k] == player) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score += 1000;
			} else if (count == 4) {
				score += 100;
			} else if (count == 3) {
				score += 10;
			} else if (count == 2) {
				score += 1;
			}
		}
	}
	return score;
}

int Ai::evaluateOpponentMoves(const std::vector<std::vector<Tile>> &board, Tile opponent)
{
	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		int count = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == opponent) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score -= 1000;
			} else if (count == 4) {
				score -= 100;
			} else if (count == 3) {
				score -= 10;
			} else if (count == 2) {
				score -= 1;
			}
		}
	}

	// 2. Check vertical lines
	for (int j = 0; j < BOARD_SIZE; j++) {
		int count = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (board[i][j] == opponent) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score -= 1000;
			} else if (count == 4) {
				score -= 100;
			} else if (count == 3) {
				score -= 10;
			} else if (count == 2) {
				score -= 1;
			}
		}
	}

	// 3. Check diagonal lines (top-left to bottom-right)
	for (int i = 0; i <= BOARD_SIZE - 5; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i+k][j+k] == opponent) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score -= 1000;
			} else if (count == 4) {
				score -= 100;
			} else if (count == 3) {
				score -= 10;
			} else if (count == 2) {
				score -= 1;
			}
		}
	}

	// 4. Check diagonal lines (bottom-left to top-right)
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i-k][j+k] == opponent) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score -= 1000;
			} else if (count == 4) {
				score -= 100;
			} else if (count == 3) {
				score -= 10;
			} else if (count == 2) {
				score -= 1;
			}
		}
	}
	return score;
}

int Ai::evaluate(BoardState state)
{
	auto player = (Tile)state.player;
	auto opponent = player == Tile::P1 ? Tile::P2 : Tile::P1;
	int score = 0;

	score = evaluateOwnMoves(state.board, player);
	score -= evaluateOpponentMoves(state.board, opponent);

	return score;
}



bestMove Ai::miniMax(BoardState state, int depth, int alpha, int beta, bool maximizingPlayer) {
	if (depth == 0 || state.isTerminal()) {
		LOG("Debt is %i",depth);
		auto score = evaluate(state);
		LOG("We terminated = %i", state.isTerminal());
		// If we have reached the maximum search depth or the game is over, return the score and no move.
		return { {-1, -1} ,score};
	}

	// Initialize the best move to an invalid position and the best score to the opposite of the expected range.
	bestMove best_move = { {-1, -1} ,-1};
	LOG("Maximizing player? %i", maximizingPlayer);
	int best_score = maximizingPlayer ? INT_MIN : INT_MAX;
	LOG("What is the best score %i", best_score);
	// Get the list of valid moves for the current state.
	std::vector<bestMove> moves = state.getValidMoves();

	for (const bestMove& move : moves) {
		// Apply the current move to the board state.
		state.makeMove(move);
		// Recursively search the game tree for the score of the resulting board state.
		int score = miniMax(state, depth - 1, alpha, beta, !maximizingPlayer).maxScore;
		LOG("What is this score exactly? %i", score);
		LOG("Current move coords = [%i][%i]", move.bestCoords.y, move.bestCoords.x);
		// Undo the current move to restore the board state.
		state.undoMove(move);

		// Update the best score and best move based on the current score and search direction.
		if (maximizingPlayer && score > best_score) {
			LOG("Maximizing player");
			best_score = score;
			best_move = move;
			alpha = std::max(alpha, best_score);
		} else if (!maximizingPlayer && score < best_score) {
			LOG("Minimizing player");
			LOG("Score = %i", score);
			LOG("Best score = %i", best_score);
			best_score = score;
			best_move = move;
			beta = std::min(beta, best_score);
			LOG("Mn beta is hier = %i", beta);
			LOG("mn best score is hier = %i", best_score);
			LOG("mn best move is hier = [%i] [%i]", best_move.bestCoords.y, best_move.bestCoords.x);
		}

		// Check whether we can prune the search based on the current alpha and beta values.
		LOG("Alpha = %i", alpha);
		LOG("Beta = %i", beta);
		if (alpha >= beta) {
			break;
		}
	}

	// Return the best move and its score.
	best_move.maxScore = best_score;
	LOG("What do we return [%i] [%i]", best_move.bestCoords.y, best_move.bestCoords.x);
	return (best_move);
}


