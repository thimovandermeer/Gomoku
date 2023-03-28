//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "DoubleThreeCheck.hpp"
#include "utils.hpp"
#include "types.hpp"

TEST(one_double_three_horizontal, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][3]= Tile::P1;
	Coordinate newCoords{1,3};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_open_space_horizontal, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][4]= Tile::P1;
	Coordinate newCoords{1,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(no_double_three, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][7]= Tile::P1;
	Coordinate newCoords{1,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "NO DOUBLE THREE FOUND");
}

TEST(one_double_three_vertical, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[2][1] = Tile::P1;
	board[3][1]= Tile::P1;
	Coordinate newCoords{3,1};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_open_space_vertical, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[2][1] = Tile::P1;
	board[4][1]= Tile::P1;
	Coordinate newCoords{4,1};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_diagonal, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[2][2] = Tile::P1;
	board[3][3]= Tile::P1;
	Coordinate newCoords{3,3};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_open_space_diagonal, double_three_check_test) {
	auto board = create_empty_board();
	board[1][1] = Tile::P1;
	board[2][2] = Tile::P1;
	board[4][4]= Tile::P1;
	Coordinate newCoords{4,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_anti_diagonal, double_three_check_test) {
	auto board = create_empty_board();

	board[0][9] = Tile::P1;
	board[1][8] = Tile::P1;
	board[2][7] = Tile::P1;

	Coordinate newCoords{2,7};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(one_double_three_open_space_anti_diagonal, double_three_check_test) {
	auto board = create_empty_board();

	board[0][9] = Tile::P1;
	board[1][8] = Tile::P1;
	board[3][6] = Tile::P1;

	Coordinate newCoords{3,6};


	auto threeCheck = DoubleThreeCheck();
	printBoard(board);
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);
	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(result.errorReason, "FIRST DOUBLE THREE");
}

TEST(two_double_three, double_three_check_test) {
	auto board = create_empty_board();

	board[0][9] = Tile::P1;
	board[1][8] = Tile::P1;
	board[3][6] = Tile::P1;

	Coordinate newCoords{3,6};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	board[1][1] = Tile::P1;
	board[1][2] = Tile::P1;
	board[1][3]= Tile::P1;
	Coordinate secondCoords{1,3};


	auto second_result = threeCheck.DoubleThreeChecker(board,secondCoords, Player::PLAYERONE);
	ASSERT_EQ(second_result.state,ERROR);
	ASSERT_EQ(second_result.errorReason, "SECOND DOUBLE THREE");
}

TEST(two_double_three_same_time, double_three_check_test) {
	auto board = create_empty_board();

	board[6][4] = Tile::P1;
	board[5][4] = Tile::P1;
	board[4][5] = Tile::P1;
	board[4][6] = Tile::P1;
	board[4][4] = Tile::P1;
	Coordinate newCoords{4,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	ASSERT_EQ(result.state,ERROR);
	ASSERT_EQ(result.errorReason, "SECOND DOUBLE THREE");

}

TEST(two_double_three_same_time, four_horizontal_test) {
	auto board = create_empty_board();

	board[4][1] = Tile::P1;
	board[4][2] = Tile::P1;
	board[4][3] = Tile::P1;
	board[4][4] = Tile::P1;
	Coordinate newCoords{4,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(threeCheck.getSizeP1(), 0);

}

TEST(two_double_three_same_time, four_vertical_test) {
	auto board = create_empty_board();

	board[1][4] = Tile::P1;
	board[2][4] = Tile::P1;
	board[3][4] = Tile::P1;
	board[4][4] = Tile::P1;
	Coordinate newCoords{4,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(threeCheck.getSizeP1(), 0);

}

TEST(two_double_three_same_time, four_diagonal_test) {
	auto board = create_empty_board();

	board[1][1] = Tile::P1;
	board[2][2] = Tile::P1;
	board[3][3] = Tile::P1;
	board[4][4] = Tile::P1;
	Coordinate newCoords{4,4};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(threeCheck.getSizeP1(), 0);

}

TEST(two_double_three_same_time, four_anti_diagonal_test) {
	auto board = create_empty_board();

	board[0][9] = Tile::P1;
	board[1][8] = Tile::P1;
	board[2][7] = Tile::P1;
	board[3][6] = Tile::P1;
	Coordinate newCoords{3,6};


	auto threeCheck = DoubleThreeCheck();
	auto result = threeCheck.DoubleThreeChecker(board,newCoords, Player::PLAYERONE);

	ASSERT_EQ(result.state,ACCEPTED);
	ASSERT_EQ(threeCheck.getSizeP1(), 0);

}