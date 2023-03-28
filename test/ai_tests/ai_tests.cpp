//
// Created by Thimo Van der meer on 27/03/2023.
//

#include <gtest/gtest.h>
#include "Ai.hpp"
#include "utils.hpp"
#include "logger.hpp"

auto AI = Ai();

TEST(evaluate_test, two_in_a_row) {
	// create a current game stae with all different settings
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;

	printBoard(board);
	auto state = BoardState{board, Player::PLAYERONE};
	auto result = AI.evaluate(state);
	ASSERT_EQ(1, result);
}


TEST(evaluate_test, three_in_a_row) {
	// create a current game stae with all different settings
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][3] = Tile::P1;
	auto state = BoardState{board, Player::PLAYERONE};
	auto result = AI.evaluate(state);
	ASSERT_EQ(11, result);
}

TEST(evaluate_test, four_in_a_row) {
	// create a current game stae with all different settings
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][3] = Tile::P1;
	board[1][4] = Tile::P1;

	auto state = BoardState{board, Player::PLAYERONE};
	auto result = AI.evaluate(state);
	ASSERT_EQ(111, result);
}


TEST(evaluate_test, minimax) {
	// create a current game stae with all different settings
	auto board = create_empty_board();
	board[5][5] = Tile::P1;
	board[6][6] = Tile::P1;
	board[7][7] = Tile::P1;
	board[8][8] = Tile::P1;

	auto result = AI.AiMove(board, Player::PLAYERONE);
	ASSERT_EQ(result.move.bestCoords.y, 4);
	ASSERT_EQ(result.move.bestCoords.x, 4);
}



