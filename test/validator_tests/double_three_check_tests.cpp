//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "../inc/DoubleThreeCheck.hpp"
#include "utils.hpp"


std::unique_ptr<ITwo>					twoCheck = std::make_unique<Two>();
DoubleThreeCheck 	threeCheck = DoubleThreeCheck(twoCheck);


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
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 10;
	coord.x = 12;
	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_vertically) {
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 11;
	coord.x = 11;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_up) {
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 11;
	coord.x = 12;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_down) {
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 9;
	coord.x = 11;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, 10);
	ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, no_double_two_possible) {
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 17;
	coord.x = 17;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(result.y, -1);
	ASSERT_EQ(result.x, -1);
}

TEST(double_two_boundary_checks, check_on_board_smaller_than_new) {
	Coordinates coord_one;
	coord_one.y = 9;
	coord_one.x = 11;

	Coordinates coord_two;
	coord_two.y = 10;
	coord_two.x = 11;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.boundary_check(coord_one, coord_two);
	ASSERT_EQ(result.left_boundary_coordinates.y, coord_one.y);
	ASSERT_EQ(result.left_boundary_coordinates.x, coord_one.x);
}

TEST(double_two_boundary_checks, determine_direction_horizontal) {
    Coordinates right_boundary;
    right_boundary.y = 3;
    right_boundary.x = 3;

    Coordinates left_boundary;
    left_boundary.y = 3;
    left_boundary.x = 2;
    Doubles doubles;
    doubles.left_boundary_coordinates = left_boundary;
    doubles.right_boundary_coordinates = right_boundary;
	auto two = *dynamic_cast<Two*>(twoCheck.get());
	ASSERT_EQ(two.determine_direction(doubles), HORIZONTAL);
}

TEST(double_two_boundary_checks, determine_direction_vertical) {
    Coordinates right_boundary;
    right_boundary.y = 3;
    right_boundary.x = 3;

    Coordinates left_boundary;
    left_boundary.y = 4;
    left_boundary.x = 3;
    Doubles doubles;
    doubles.left_boundary_coordinates = left_boundary;
    doubles.right_boundary_coordinates = right_boundary;
	auto two = *dynamic_cast<Two*>(twoCheck.get());
	ASSERT_EQ(two.determine_direction(doubles), VERTICAL);
}

TEST(double_two_boundary_checks, determine_direction_cross_up) {
    Coordinates right_boundary;
    right_boundary.y = 3;
    right_boundary.x = 3;

    Coordinates left_boundary;
    left_boundary.y = 4;
    left_boundary.x = 4;
    Doubles doubles;
    doubles.left_boundary_coordinates = left_boundary;
    doubles.right_boundary_coordinates = right_boundary;
	auto two = *dynamic_cast<Two*>(twoCheck.get());
	ASSERT_EQ(two.determine_direction(doubles), CROSS);
}

TEST(double_two_boundary_checks, determine_direction_cross_down) {
    Coordinates right_boundary;
    right_boundary.y = 3;
    right_boundary.x = 3;

    Coordinates left_boundary;
    left_boundary.y = 2;
    left_boundary.x = 2;
    Doubles doubles;
    doubles.left_boundary_coordinates = left_boundary;
    doubles.right_boundary_coordinates = right_boundary;
	auto two = *dynamic_cast<Two*>(twoCheck.get());
	ASSERT_EQ(two.determine_direction(doubles), CROSS);
}

TEST(double_two_boundary_checks, check_on_board_bigger_than_new) {
	Coordinates coord_one;
	coord_one.y = 9;
	coord_one.x = 11;

	Coordinates coord_two;
	coord_two.y = 8;
	coord_two.x = 11;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.boundary_check(coord_one, coord_two);
	ASSERT_EQ(result.left_boundary_coordinates.y, coord_two.y);
	ASSERT_EQ(result.left_boundary_coordinates.x, coord_two.x);
}

TEST(double_two_two_in_a_row, check_on_board_bigger_than_new) {
	Coordinates coord_one;
	coord_one.y = 9;
	coord_one.x = 11;

	Coordinates coord_two;
	coord_two.y = 8;
	coord_two.x = 11;

	auto two = *dynamic_cast<Two*>(twoCheck.get());
	auto result = two.boundary_check(coord_one, coord_two);
	ASSERT_EQ(result.left_boundary_coordinates.y, coord_two.y);
	ASSERT_EQ(result.left_boundary_coordinates.x, coord_two.x);
}

TEST(double_two_two_in_a_row, check_size_double_two_vector) {
	auto board = create_double_two_board_horizontally();
	Coordinates coord;
	coord.y = 11;
	coord.x = 12;

	threeCheck.two_in_a_row(board, coord, PLAYERONE);
	ASSERT_EQ(1, threeCheck.double_two_size());
}

std::vector<std::vector<Tile>> create_double_three_board_horizontally() {
    std::vector<std::vector<Tile>> board = create_empty_board();
    board[10][11] = Tile::PLAYERONE;
    board[10][12] = Tile::PLAYERONE;
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

    ASSERT_TRUE(threeCheck.check_right_boundary(boundary_coords, new_coords, HORIZONTAL));
}

TEST(double_three_check_tests, check_right_boundary_horizontal_false_test) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 15;

    ASSERT_FALSE(threeCheck.check_right_boundary(boundary_coords, new_coords, HORIZONTAL));
}

TEST(double_three_check_tests, check_right_boundary_vertical) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 10;

    ASSERT_TRUE(threeCheck.check_right_boundary(boundary_coords, new_coords, VERTICAL));
}

TEST(double_three_check_tests, check_right_boundary_vertical_false_test) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 15;
    new_coords.x = 10;

    ASSERT_FALSE(threeCheck.check_right_boundary(boundary_coords, new_coords, VERTICAL));
}

TEST(double_three_check_tests, check_right_boundary_cross) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 11;

    ASSERT_TRUE(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS));
}

TEST(double_three_check_tests, check_right_boundary_cross_false_test_y_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 12;
    new_coords.x = 11;

    ASSERT_FALSE(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS));
}

TEST(double_three_check_tests, check_right_boundary_cross_false_test_x_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 11;
    new_coords.x = 15;

    ASSERT_FALSE(threeCheck.check_right_boundary(boundary_coords, new_coords, CROSS));
}

TEST(double_three_check_tests, check_left_boundary_horizontal) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 9;

    ASSERT_TRUE(threeCheck.check_left_boundary(boundary_coords, new_coords, HORIZONTAL));
}

TEST(double_three_check_tests, check_left_boundary_horizontal_false_test) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 10;
    new_coords.x = 5;

    ASSERT_FALSE(threeCheck.check_left_boundary(boundary_coords, new_coords, HORIZONTAL));
}

TEST(double_three_check_tests, check_left_boundary_vertical) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 10;

    ASSERT_TRUE(threeCheck.check_left_boundary(boundary_coords, new_coords, VERTICAL));
}

TEST(double_three_check_tests, check_left_boundary_vertical_false_test) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 5;
    new_coords.x = 10;

    ASSERT_FALSE(threeCheck.check_left_boundary(boundary_coords, new_coords, VERTICAL));
}

TEST(double_three_check_tests, check_left_boundary_cross) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 9;

    ASSERT_TRUE(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS));
}

TEST(double_three_check_tests, check_left_boundary_cross_false_test_y_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 8;
    new_coords.x = 9;

    ASSERT_FALSE(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS));
}

TEST(double_three_check_tests, check_left_boundary_cross_false_test_x_different) {
    // create board with double three on it
    Coordinates boundary_coords;
    boundary_coords.y = 10;
    boundary_coords.x = 10;

    Coordinates new_coords;
    new_coords.y = 9;
    new_coords.x = 8;

    ASSERT_FALSE(threeCheck.check_left_boundary(boundary_coords, new_coords, CROSS));
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



//TEST(double_three_check_tests, find_double_three_vertically) {
//	// create board with double three on it
//	std::vector<std::vector<Tile>> board = create_double_three_board_vertically();
//	DoubleThreeCheck threeCheck = DoubleThreeCheck();
//	ASSERT_TRUE(threeCheck.find_three(board));
//}
//
//TEST(double_three_check_tests, find_double_three_cross) {
//	// create board with double three on it
//	std::vector<std::vector<Tile>> board = create_double_three_board_cross();
//	DoubleThreeCheck threeCheck = DoubleThreeCheck();
//	ASSERT_TRUE(threeCheck.find_three(board));
//}
