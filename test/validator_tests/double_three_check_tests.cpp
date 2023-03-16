//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "DoubleThreeCheck.hpp"
#include "utils.hpp"
#include "types.hpp"

std::unique_ptr<ITwo> twoCheck = std::make_unique<Two>();
DoubleThreeCheck threeCheck = DoubleThreeCheck(twoCheck);

std::vector<std::vector<Tile>> create_double_three_board_horizontally() {
    std::vector<std::vector<Tile>> board = create_empty_board();
    board[10][11] = Tile::P1;
    board[10][12] = Tile::P1;
//    board[10][13] = Tile::PLAYERONE;
    return board;
}



TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();

    ASSERT_EQ(result.leftBoundaryCoordinates.y, 10);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 12);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 11;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 12;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 13;
    doubles.direction = HORIZONTAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();

    ASSERT_EQ(result.leftBoundaryCoordinates.x, 11);
    ASSERT_EQ(result.rightBoundaryCoordinates.x, 13);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 9;
    doubles.leftBoundaryCoordinates.x = 11;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 11;
    coords.x = 11;
    doubles.direction = VERTICAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();

    ASSERT_EQ(result.leftBoundaryCoordinates.y, 9);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 11);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 9;
    coords.x = 9;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();
    ASSERT_EQ(result.leftBoundaryCoordinates.y, 9);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 11);
}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();
    ASSERT_EQ(result.leftBoundaryCoordinates.x, 9);
    ASSERT_EQ(result.rightBoundaryCoordinates.x, 11);
}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 10;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();
    ASSERT_EQ(result.leftBoundaryCoordinates.y, 10);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 12);
}


TEST(double_three_check_tests, check_double_three_with_open_space_right_horizontal) {
	Doubles doubles;

	doubles.leftBoundaryCoordinates.y = 10;
	doubles.leftBoundaryCoordinates.x = 10;

	doubles.rightBoundaryCoordinates.y = 10;
	doubles.rightBoundaryCoordinates.x = 11;
	// add coordinates right side

	Coordinate coords;
	coords.y = 10;
	coords.x = 13;
	doubles.direction = HORIZONTAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
	auto result = threeCheck.getLastThree();

	ASSERT_TRUE(result.openSpace);
	ASSERT_EQ(result.openSpaceCoordinates.y, 10);
	ASSERT_EQ(result.openSpaceCoordinates.x, 12);
	ASSERT_EQ(result.leftBoundaryCoordinates.y, 10);
	ASSERT_EQ(result.rightBoundaryCoordinates.x, 13);
}



TEST(double_three_check_tests, check_double_three_with_open_space_left_horizontal) {
	Doubles doubles;

	doubles.leftBoundaryCoordinates.y = 10;
	doubles.leftBoundaryCoordinates.x = 10;

	doubles.rightBoundaryCoordinates.y = 10;
	doubles.rightBoundaryCoordinates.x = 11;
	// add coordinates right side

	Coordinate coords;
	coords.y = 10;
	coords.x = 8;
	doubles.direction = HORIZONTAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
	auto result = threeCheck.getLastThree();

	ASSERT_TRUE(result.openSpace);
	ASSERT_EQ(result.openSpaceCoordinates.y, 10);
	ASSERT_EQ(result.openSpaceCoordinates.x, 9);
	ASSERT_EQ(result.leftBoundaryCoordinates.y, 10);
	ASSERT_EQ(result.rightBoundaryCoordinates.x, 11);
}



TEST(double_three_check_tests, check_double_three_with_open_space_up_vertical) {
	Doubles doubles;

	doubles.leftBoundaryCoordinates.y = 10;
	doubles.leftBoundaryCoordinates.x = 10;

	doubles.rightBoundaryCoordinates.y = 11;
	doubles.rightBoundaryCoordinates.x = 10;
	// add coordinates right side

	Coordinate coords;
	coords.y = 13;
	coords.x = 10;
	doubles.direction = VERTICAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
	auto result = threeCheck.getLastThree();

	ASSERT_TRUE(result.openSpace);
	ASSERT_EQ(result.openSpaceCoordinates.y, 12);
	ASSERT_EQ(result.openSpaceCoordinates.x, 10);
	ASSERT_EQ(result.leftBoundaryCoordinates.y, 10);
	ASSERT_EQ(result.rightBoundaryCoordinates.y, 13);
}




TEST(double_three_check_tests, check_double_three_with_open_space_down_vertical) {
	Doubles doubles;

	doubles.leftBoundaryCoordinates.y = 10;
	doubles.leftBoundaryCoordinates.x = 10;

	doubles.rightBoundaryCoordinates.y = 11;
	doubles.rightBoundaryCoordinates.x = 10;
	// add coordinates right side

	Coordinate coords;
	coords.y = 8;
	coords.x = 10;
	doubles.direction = VERTICAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
	auto result = threeCheck.getLastThree();

	ASSERT_TRUE(result.openSpace);
	ASSERT_EQ(result.openSpaceCoordinates.y, 9);
	ASSERT_EQ(result.openSpaceCoordinates.x, 10);
	ASSERT_EQ(result.leftBoundaryCoordinates.y, 8);
	ASSERT_EQ(result.rightBoundaryCoordinates.y, 11);
}



TEST(double_three_check_tests, check_double_three_with_open_space_left_cross) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 3;
    doubles.leftBoundaryCoordinates.x = 2;

    doubles.rightBoundaryCoordinates.y = 4;
    doubles.rightBoundaryCoordinates.x = 3;
    // add coordinates right side

    Coordinate coords;
    coords.y = 1;
    coords.x = 0;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();

    ASSERT_TRUE(result.openSpace);
    ASSERT_EQ(result.openSpaceCoordinates.y, 2);
    ASSERT_EQ(result.openSpaceCoordinates.x, 1);
    ASSERT_EQ(result.leftBoundaryCoordinates.x, 0);
    ASSERT_EQ(result.rightBoundaryCoordinates.x, 3);
    ASSERT_EQ(result.leftBoundaryCoordinates.y, 1);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 4);
}



TEST(double_three_check_tests, check_double_three_with_open_space_right_cross) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 3;
    doubles.leftBoundaryCoordinates.x = 2;

    doubles.rightBoundaryCoordinates.y = 4;
    doubles.rightBoundaryCoordinates.x = 3;
    // add coordinates right side

    Coordinate coords;
    coords.y = 6;
    coords.x = 5;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    threeCheck.setBoard(board);
    threeCheck.findThree(coords, vec);
    auto result = threeCheck.getLastThree();

    ASSERT_TRUE(result.openSpace);
    ASSERT_NE(result.direction, NULL);
    ASSERT_EQ(result.openSpaceCoordinates.y, 5);
    ASSERT_EQ(result.openSpaceCoordinates.x, 4);
    ASSERT_EQ(result.leftBoundaryCoordinates.x, 2);
    ASSERT_EQ(result.rightBoundaryCoordinates.x, 5);
    ASSERT_EQ(result.leftBoundaryCoordinates.y, 3);
    ASSERT_EQ(result.rightBoundaryCoordinates.y, 6);
}



TEST(double_three_check_tests, double_three_is_fully_free_true_left_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[10][8] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_left_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[10][8] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_true_left_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 10;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[9][10] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_left_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 10;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[9][10] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_true_left_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[9][9] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_left_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[9][9] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_true_right_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[10][12] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_right_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 10;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[10][12] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_true_right_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 10;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[13][10] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_right_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 10;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[13][10] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_true_right_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[13][13] = Tile::EMPTY;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_TRUE(threeCheck.fullFreeCheck());

}

TEST(double_three_check_tests, double_three_is_fully_free_false_right_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 10;
    doubles.leftBoundaryCoordinates.x = 10;

    doubles.rightBoundaryCoordinates.y = 11;
    doubles.rightBoundaryCoordinates.x = 11;
    // add coordinates right side

    Coordinate coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.findThree(coords, vec);
    auto board = create_empty_board();
    board[13][13] = Tile::P2;
    threeCheck.setBoard(board);
    auto result = threeCheck.getLastThree();
    ASSERT_FALSE(threeCheck.fullFreeCheck());

}