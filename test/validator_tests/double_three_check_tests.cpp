//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "../inc/DoubleThreeCheck.hpp"

std::vector<std::vector<Tile>> create_empty_board() {
	return{MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::FREE}};
}

std::vector<std::vector<Tile>> create_double_three_board_horizontally() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[10][11] = Tile::PLAYERONE;
	board[10][12] = Tile::PLAYERONE;
	board[10][13] = Tile::PLAYERONE;
}

std::vector<std::vector<Tile>> create_double_three_board_vertically() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[11][10] = Tile::PLAYERONE;
	board[12][10] = Tile::PLAYERONE;
	board[13][10] = Tile::PLAYERONE;
}

std::vector<std::vector<Tile>> create_double_three_board_cross() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[3][3] = Tile::PLAYERONE;
	board[4][4] = Tile::PLAYERONE;
	board[5][5] = Tile::PLAYERONE;
}

TEST(double_three_check_tests, find_double_three_horizontally) {
	// create board with double three on it
	std::vector<std::vector<Tile>> board = create_double_three_board_horizontally();
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	GTEST_ASSERT_TRUE(threeCheck.find_double_three(board));
}

TEST(double_three_check_tests, find_double_three_vertically) {
	// create board with double three on it
	std::vector<std::vector<Tile>> board = create_double_three_board_vertically();
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	threeCheck.find_double_three(board);
}

TEST(double_three_check_tests, find_double_three_cross) {
	// create board with double three on it
	std::vector<std::vector<Tile>> board = create_double_three_board_cross();
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	threeCheck.find_double_three(board);
}
