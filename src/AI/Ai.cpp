//
// Created by Thimo Van der meer on 27/03/2023.
//

#include <cmath>
#include "Ai.hpp"
#include "Gomoku.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include <iostream>

#define DEPTH 4

#define TWO_IN_A_ROW 10
#define THREE_IN_A_ROW 100
#define FOUR_IN_A_ROW 1000
#define FIVE_IN_A_ROW 100000


AiResponse Ai::AiMove(const std::vector<std::vector<Tile>>& board,const Player &player){
	BoardState state{board, player};
	bool maximizingPlayer = false;
	if(player == Player::PLAYERONE) {
		maximizingPlayer = false;
	} else {
		maximizingPlayer = true;
	}
	auto score = miniMax(state, DEPTH, INT_MIN, INT_MAX, maximizingPlayer);
	return (AiResponse{"Valid ai move", score});

}

int Ai::evaluateOwnMoves(const std::vector<std::vector<TileAi>> &board, Tile player)
{
	int score = 0;
	// Evaluate the board based on potential win conditions for the AI
	// 1. Check horizontal lines
	for (int i = 0; i < BOARD_SIZE; i++) {
		int count = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].pos == player) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score += FIVE_IN_A_ROW;
			} else if (count == 4) {
				score += FOUR_IN_A_ROW;
			} else if (count == 3) {
				score += THREE_IN_A_ROW;
			} else if (count == 2) {
				score += TWO_IN_A_ROW;
			}
		}
	}

	// 2. Check vertical lines
	for (int j = 0; j < BOARD_SIZE; j++) {
		int count = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (board[i][j].pos == player) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score += FIVE_IN_A_ROW;
			} else if (count == 4) {
				score += FOUR_IN_A_ROW;
			} else if (count == 3) {
				score += THREE_IN_A_ROW;
			} else if (count == 2) {
				score += TWO_IN_A_ROW;
			}
		}
	}

	// 3. Check diagonal lines (top-left to bottom-right)
	for (int i = 0; i <= BOARD_SIZE - 5; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i+k][j+k].pos == player) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score += FIVE_IN_A_ROW;
			} else if (count == 4) {
				score += FOUR_IN_A_ROW;
			} else if (count == 3) {
				score += THREE_IN_A_ROW;
			} else if (count == 2) {
				score += TWO_IN_A_ROW;
			}
		}
	}

	// 4. Check diagonal lines (bottom-left to top-right)
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i-k][j+k].pos == player) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score += FIVE_IN_A_ROW;
			} else if (count == 4) {
				score += FOUR_IN_A_ROW;
			} else if (count == 3) {
				score += THREE_IN_A_ROW;
			} else if (count == 2) {
				score += TWO_IN_A_ROW;
			}
		}
	}
	return score;
}

int Ai::evaluateOpponentMoves(const std::vector<std::vector<TileAi>> &board, Tile opponent)
{
	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		int count = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].pos == opponent) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score -= FIVE_IN_A_ROW;
			} else if (count == 4) {
				score -= FOUR_IN_A_ROW;
			} else if (count == 3) {
				score -= THREE_IN_A_ROW;
			} else if (count == 2) {
				score -= TWO_IN_A_ROW;
			}
		}
	}

	// 2. Check vertical lines
	for (int j = 0; j < BOARD_SIZE; j++) {
		int count = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (board[i][j].pos == opponent) {
				count++;
			} else {
				count = 0;
			}

			if (count == 5) {
				score -= FIVE_IN_A_ROW;
			} else if (count == 4) {
				score -= FOUR_IN_A_ROW;
			} else if (count == 3) {
				score -= THREE_IN_A_ROW;
			} else if (count == 2) {
				score -= TWO_IN_A_ROW;
			}
		}
	}

	// 3. Check diagonal lines (top-left to bottom-right)
	for (int i = 0; i <= BOARD_SIZE - 5; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i+k][j+k].pos == opponent) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score -= FIVE_IN_A_ROW;
			} else if (count == 4) {
				score -= FOUR_IN_A_ROW;
			} else if (count == 3) {
				score -= THREE_IN_A_ROW;
			} else if (count == 2) {
				score -= TWO_IN_A_ROW;
			}
		}
	}

	// 4. Check diagonal lines (bottom-left to top-right)
	for (int i = 4; i < BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			int count = 0;
			for (int k = 0; k < 5; k++) {
				if (board[i-k][j+k].pos == opponent) {
					count++;
				} else {
					count = 0;
					break;
				}
			}

			if (count == 5) {
				score -= FIVE_IN_A_ROW;
			} else if (count == 4) {
				score -= FOUR_IN_A_ROW;
			} else if (count == 3) {
				score -= THREE_IN_A_ROW;
			} else if (count == 2) {
				score -= TWO_IN_A_ROW;
			}
		}
	}
	return score;
}

int Ai::evaluate(BoardState state)
{
	int score = 0;
	auto player = Tile::P2;
	auto opponent = Tile::P1;
	score = evaluateOwnMoves(state.board, player);
	score -= evaluateOpponentMoves(state.board, opponent);
	return score;
}



bestMove Ai::miniMax(BoardState state, int depth, int alpha, int beta, bool maximizingPlayer) {
	if (depth == 0 || state.isTerminal()) {
		auto score = evaluate(state);
		return { {-1, -1} ,score};
	}

	bestMove theMove{state.getValidMoves().front(), maximizingPlayer ? INT_MIN : INT_MAX};
	int bestScore = maximizingPlayer ? INT_MIN : INT_MAX;
	for (auto& move : state.getValidMoves()) {
		BoardState newState = state;
		newState.makeMove(move);
		int score = miniMax(newState, depth-1, alpha, beta, !maximizingPlayer).maxScore;

		if (maximizingPlayer && score > bestScore || (score == bestScore && std::rand() % 2 == 0)) {
			bestScore = score;
			theMove = { move, bestScore };
			alpha = std::max(alpha, bestScore);
		} else if ((!maximizingPlayer && score < bestScore) || (score == bestScore && std::rand() % 2 == 0)) {
			bestScore = score;
			theMove = { move, bestScore };
			beta = std::min(beta, bestScore);
		}
		if (beta <= alpha) {
			break;
		}
	}
	return theMove;
}