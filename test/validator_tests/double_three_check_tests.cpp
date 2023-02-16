//
// Created by Thimo Van der meer on 09/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "../inc/DoubleThreeCheck.hpp"
#include "utils.hpp"

std::unique_ptr<ITwo>					twoCheck = std::make_unique<Two>();
DoubleThreeCheck 	threeCheck = DoubleThreeCheck(twoCheck);

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
