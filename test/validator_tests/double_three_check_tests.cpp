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

TEST(double_three_check_tests, check_right_boundary_horizontal) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 11;
	auto result = threeCheck.check_right_boundary(boundary_coords, new_coords, HORIZONTAL);
    ASSERT_EQ(result.doubleType, NORMAL);
}

TEST(double_three_check_tests, check_right_boundary_horizontal_false) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 15;
	auto result = threeCheck.check_right_boundary(boundary_coords, new_coords, HORIZONTAL);
    ASSERT_EQ(result.doubleType, NONE);
}

TEST(double_three_check_tests, check_right_boundary_vertical) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 10;
	auto result = threeCheck.check_right_boundary(boundary_coords, new_coords, VERTICAL);
    ASSERT_EQ(result.doubleType, NORMAL);
}

TEST(double_three_check_tests, check_right_boundary_vertical_false) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 15;
    new_coords.x = 10;

    ASSERT_EQ(threeCheck.check_right_boundary(boundary_coords, new_coords, VERTICAL).doubleType, NONE);
}

TEST(double_three_check_tests, check_right_boundary_cross) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 11;

    ASSERT_EQ(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS).doubleType, NORMAL);
}

TEST(double_three_check_tests, check_right_boundary_cross_false_y_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 12;
    new_coords.x = 11;

    ASSERT_EQ(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}

TEST(double_three_check_tests, check_right_boundary_cross_false_x_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 15;

    ASSERT_EQ(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}

TEST(double_three_check_tests, check_left_boundary_horizontal) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 9;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, HORIZONTAL).doubleType, NORMAL);
}

TEST(double_three_check_tests, check_left_boundary_horizontal_false) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 5;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, HORIZONTAL).doubleType, NONE);
}

TEST(double_three_check_tests, check_left_boundary_vertical) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 10;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, VERTICAL).doubleType, NORMAL);
}

TEST(double_three_check_tests, check_left_boundary_vertical_false) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 5;
    new_coords.x = 10;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, VERTICAL).doubleType, NONE);
}

TEST(double_three_check_tests, check_left_boundary_cross) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 9;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NORMAL);
}

TEST(double_three_check_tests, check_left_boundary_cross_false_y_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 7;
    new_coords.x = 9;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}

TEST(double_three_check_tests, check_left_boundary_cross_false_x_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 7;

    ASSERT_EQ(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}


TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 10;
    doubles.left_boundary_coordinates.x = 10;

    doubles.right_boundary_coordinates.y = 11;
    doubles.right_boundary_coordinates.x = 11;
    // add coordinates right side

    Coordinates coords;
    coords.y = 12;
    coords.x = 12;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();

    ASSERT_EQ(result.left_boundary_coordinates.y, 10);
    ASSERT_EQ(result.right_boundary_coordinates.y, 12);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 10;
    doubles.left_boundary_coordinates.x = 11;

    doubles.right_boundary_coordinates.y = 10;
    doubles.right_boundary_coordinates.x = 12;
    // add coordinates right side

    Coordinates coords;
    coords.y = 10;
    coords.x = 13;
    doubles.direction = HORIZONTAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();

    ASSERT_EQ(result.left_boundary_coordinates.x, 11);
    ASSERT_EQ(result.right_boundary_coordinates.x, 13);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_right_side_addition_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 9;
    doubles.left_boundary_coordinates.x = 11;

    doubles.right_boundary_coordinates.y = 10;
    doubles.right_boundary_coordinates.x = 11;
    // add coordinates right side

    Coordinates coords;
    coords.y = 11;
    coords.x = 11;
    doubles.direction = VERTICAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();

    ASSERT_EQ(result.left_boundary_coordinates.y, 9);
    ASSERT_EQ(result.right_boundary_coordinates.y, 11);

}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_cross) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 10;
    doubles.left_boundary_coordinates.x = 10;

    doubles.right_boundary_coordinates.y = 11;
    doubles.right_boundary_coordinates.x = 11;
    // add coordinates right side

    Coordinates coords;
    coords.y = 9;
    coords.x = 9;
    doubles.direction = CROSS;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();
    ASSERT_EQ(result.left_boundary_coordinates.y, 9);
    ASSERT_EQ(result.right_boundary_coordinates.y, 11);
}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_horizontal) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 10;
    doubles.left_boundary_coordinates.x = 10;

    doubles.right_boundary_coordinates.y = 10;
    doubles.right_boundary_coordinates.x = 11;
    // add coordinates right side

    Coordinates coords;
    coords.y = 10;
    coords.x = 9;
    doubles.direction = HORIZONTAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();
    ASSERT_EQ(result.left_boundary_coordinates.x, 9);
    ASSERT_EQ(result.right_boundary_coordinates.x, 11);
}

TEST(double_three_check_tests, check_double_three_vector_coordinates_left_side_addition_vertical) {
    // create a double with coordinates
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 10;
    doubles.left_boundary_coordinates.x = 10;

    doubles.right_boundary_coordinates.y = 11;
    doubles.right_boundary_coordinates.x = 10;
    // add coordinates right side

    Coordinates coords;
    coords.y = 12;
    coords.x = 10;
    doubles.direction = VERTICAL;
    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();
    ASSERT_EQ(result.left_boundary_coordinates.y, 10);
    ASSERT_EQ(result.right_boundary_coordinates.y, 12);
}

//TEST(double_three_check_tests, check_double_three_with_open_space_right_horizontal) {
//    Doubles doubles;
//
//    doubles.left_boundary_coordinates.y = 10;
//    doubles.left_boundary_coordinates.x = 11;
//
//    doubles.right_boundary_coordinates.y = 10;
//    doubles.right_boundary_coordinates.x = 12;
//    // add coordinates right side
//
//	Coordinates coords;
//	coords.y = 10;
//	coords.x = 14;
//	doubles.direction = HORIZONTAL;
//	// check coordinates
//	std::vector<Doubles> vec;
//	vec.push_back(doubles);
//	auto board = create_empty_board();
//    coords.y = 10;
//    coords.x = 14;
//    doubles.direction = HORIZONTAL;
//    // check coordinates
//    vec.push_back(doubles);
//    threeCheck.set_board(board);
//    threeCheck.find_three(coords, vec);
//    auto result = threeCheck.get_last_three();
//    ASSERT_EQ(result.left_boundary_coordinates.y, 10);
//    ASSERT_EQ(result.right_boundary_coordinates.y, 12);
//}

TEST(double_three_check_tests, open_space_is_empty_positive) {
    Coordinates coords;
    coords.y = 10;
    coords.x = 10;


    auto board = create_filled_board();
    board[coords.y][coords.x] = Tile::EMPTY;
    threeCheck.set_board(board);

    // function undertest
    threeCheck.open_space_is_empty(coords);
}

TEST(double_three_check_tests, open_space_is_empty_negative) {
    Coordinates coords;
    coords.y = 10;
    coords.x = 10;


    auto board = create_empty_board();
    board[coords.y][coords.x] = Tile::P2;
    threeCheck.set_board(board);
    // function undertest
    threeCheck.open_space_is_empty(coords);
}

TEST(double_three_check_tests, check_double_three_with_open_space_right_horizontal) {
	Doubles doubles;

	doubles.left_boundary_coordinates.y = 10;
	doubles.left_boundary_coordinates.x = 10;

	doubles.right_boundary_coordinates.y = 10;
	doubles.right_boundary_coordinates.x = 11;
	// add coordinates right side

	Coordinates coords;
	coords.y = 10;
	coords.x = 13;
	doubles.direction = HORIZONTAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
	threeCheck.set_board(board);
	threeCheck.find_three(coords, vec);
	auto result = threeCheck.get_last_three();

	ASSERT_TRUE(result.open_space);
	ASSERT_EQ(result.open_space_coordinates.y, 10);
	ASSERT_EQ(result.open_space_coordinates.x, 12);
	ASSERT_EQ(result.left_boundary_coordinates.y, 10);
	ASSERT_EQ(result.right_boundary_coordinates.x, 13);
}

TEST(double_three_check_tests, check_double_three_with_open_space_left_horizontal) {
	Doubles doubles;

	doubles.left_boundary_coordinates.y = 10;
	doubles.left_boundary_coordinates.x = 10;

	doubles.right_boundary_coordinates.y = 10;
	doubles.right_boundary_coordinates.x = 11;
	// add coordinates right side

	Coordinates coords;
	coords.y = 10;
	coords.x = 8;
	doubles.direction = HORIZONTAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
	threeCheck.set_board(board);
	threeCheck.find_three(coords, vec);
	auto result = threeCheck.get_last_three();

	ASSERT_TRUE(result.open_space);
	ASSERT_EQ(result.open_space_coordinates.y, 10);
	ASSERT_EQ(result.open_space_coordinates.x, 9);
	ASSERT_EQ(result.left_boundary_coordinates.y, 10);
	ASSERT_EQ(result.right_boundary_coordinates.x, 11);
}

TEST(double_three_check_tests, check_double_three_with_open_space_up_vertical) {
	Doubles doubles;

	doubles.left_boundary_coordinates.y = 10;
	doubles.left_boundary_coordinates.x = 10;

	doubles.right_boundary_coordinates.y = 11;
	doubles.right_boundary_coordinates.x = 10;
	// add coordinates right side

	Coordinates coords;
	coords.y = 13;
	coords.x = 10;
	doubles.direction = VERTICAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
	threeCheck.set_board(board);
	threeCheck.find_three(coords, vec);
	auto result = threeCheck.get_last_three();

	ASSERT_TRUE(result.open_space);
	ASSERT_EQ(result.open_space_coordinates.y, 12);
	ASSERT_EQ(result.open_space_coordinates.x, 10);
	ASSERT_EQ(result.left_boundary_coordinates.y, 10);
	ASSERT_EQ(result.right_boundary_coordinates.y, 13);
}


TEST(double_three_check_tests, check_double_three_with_open_space_down_vertical) {
	Doubles doubles;

	doubles.left_boundary_coordinates.y = 10;
	doubles.left_boundary_coordinates.x = 10;

	doubles.right_boundary_coordinates.y = 11;
	doubles.right_boundary_coordinates.x = 10;
	// add coordinates right side

	Coordinates coords;
	coords.y = 8;
	coords.x = 10;
	doubles.direction = VERTICAL;


	// check coordinates
	std::vector<Doubles> vec;
	vec.push_back(doubles);
	auto board = create_empty_board();
	threeCheck.set_board(board);
	threeCheck.find_three(coords, vec);
	auto result = threeCheck.get_last_three();

	ASSERT_TRUE(result.open_space);
	ASSERT_EQ(result.open_space_coordinates.y, 9);
	ASSERT_EQ(result.open_space_coordinates.x, 10);
	ASSERT_EQ(result.left_boundary_coordinates.y, 8);
	ASSERT_EQ(result.right_boundary_coordinates.y, 11);
}

TEST(double_three_check_tests, check_double_three_with_open_space_left_cross) {
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 3;
    doubles.left_boundary_coordinates.x = 2;

    doubles.right_boundary_coordinates.y = 4;
    doubles.right_boundary_coordinates.x = 3;
    // add coordinates right side

    Coordinates coords;
    coords.y = 1;
    coords.x = 0;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    threeCheck.set_board(board);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();

    ASSERT_TRUE(result.open_space);
    ASSERT_EQ(result.open_space_coordinates.y, 2);
    ASSERT_EQ(result.open_space_coordinates.x, 1);
    ASSERT_EQ(result.left_boundary_coordinates.x, 0);
    ASSERT_EQ(result.right_boundary_coordinates.x, 3);
    ASSERT_EQ(result.left_boundary_coordinates.y, 1);
    ASSERT_EQ(result.right_boundary_coordinates.y, 4);
}

TEST(double_three_check_tests, check_double_three_with_open_space_right_cross) {
    Doubles doubles;

    doubles.left_boundary_coordinates.y = 3;
    doubles.left_boundary_coordinates.x = 2;

    doubles.right_boundary_coordinates.y = 4;
    doubles.right_boundary_coordinates.x = 3;
    // add coordinates right side

    Coordinates coords;
    coords.y = 6;
    coords.x = 5;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    threeCheck.set_board(board);
    threeCheck.find_three(coords, vec);
    auto result = threeCheck.get_last_three();

    ASSERT_TRUE(result.open_space);
    ASSERT_EQ(result.open_space_coordinates.y, 5);
    ASSERT_EQ(result.open_space_coordinates.x, 4);
    ASSERT_EQ(result.left_boundary_coordinates.x, 2);
    ASSERT_EQ(result.right_boundary_coordinates.x, 5);
    ASSERT_EQ(result.left_boundary_coordinates.y, 3);
    ASSERT_EQ(result.right_boundary_coordinates.y, 6);
}

TEST(double_three_check_tests, find_double_three_cross) {
    // create board with double three on it

}
