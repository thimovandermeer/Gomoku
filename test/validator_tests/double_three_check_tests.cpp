//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "../inc/DoubleThreeCheck.hpp"
#include "utils.hpp"


std::vector<std::vector<Tile>> create_double_three_board_horizontally() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[10][11] = Tile::PLAYERONE;
	board[10][12] = Tile::PLAYERONE;
	board[10][13] = Tile::PLAYERONE;
	return board;
}

std::vector<std::vector<Tile>> create_double_three_board_vertically() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[11][10] = Tile::PLAYERONE;
	board[12][10] = Tile::PLAYERONE;
	board[13][10] = Tile::PLAYERONE;
	return board;
}

std::vector<std::vector<Tile>> create_double_three_board_cross() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[3][3] = Tile::PLAYERONE;
	board[4][4] = Tile::PLAYERONE;
	board[5][5] = Tile::PLAYERONE;
	return board;
}

std::vector<std::vector<Tile>> create_double_two_board_horizontally() {
	std::vector<std::vector<Tile>> board = create_empty_board();
	board[10][11] = Tile::PLAYERONE;
	return board;
}

TEST(double_two_check_tests, find_double_two_horizontally) {
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 10;
	coord.x = 12;

	auto result = threeCheck.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_vertically) {
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 11;
	coord.x = 11;

	auto result = threeCheck.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_up) {
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 11;
	coord.x = 12;

	auto result = threeCheck.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_down) {
	DoubleThreeCheck threeCheck = DoubleThreeCheck();
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 9;
	coord.x = 11;

	auto result = threeCheck.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, no_double_two_possible) {		DoubleThreeCheck threeCheck = DoubleThreeCheck();
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 17;
	coord.x = 17;

	auto result = threeCheck.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, -1);
	ASSERT_EQ(result.x, -1);
}




//TEST(double_three_check_tests, find_double_three_horizontally) {
//	// create board with double three on it
//	std::vector<std::vector<Tile>> board = create_double_three_board_horizontally();
//	DoubleThreeCheck threeCheck = DoubleThreeCheck();
//	ASSERT_TRUE(threeCheck.find_double_three(board));
//}
//
//TEST(double_three_check_tests, find_double_three_vertically) {
//	// create board with double three on it
//	std::vector<std::vector<Tile>> board = create_double_three_board_vertically();
//	DoubleThreeCheck threeCheck = DoubleThreeCheck();
//	ASSERT_TRUE(threeCheck.find_double_three(board));
//}
//
//TEST(double_three_check_tests, find_double_three_cross) {
//	// create board with double three on it
//	std::vector<std::vector<Tile>> board = create_double_three_board_cross();
//	DoubleThreeCheck threeCheck = DoubleThreeCheck();
//	ASSERT_TRUE(threeCheck.find_double_three(board));
//}
