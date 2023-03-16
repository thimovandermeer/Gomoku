//
// Created by Thimo Van der meer on 16/03/2023.
//

#include <gtest/gtest.h>
#include "types.hpp"
#include "CommonValidationCode.hpp"
#include "utils.hpp"
auto board = create_empty_board();
TEST(common_validation_tests, check_right_boundary_horizontal) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 10;
new_coords.x = 11;
auto result = check_right_boundary(boundary_coords, new_coords, HORIZONTAL, board);
ASSERT_EQ(result.doubleType, NORMAL);
}

TEST(common_validation_tests, check_right_boundary_horizontal_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 10;
new_coords.x = 15;
auto result = check_right_boundary(boundary_coords, new_coords, HORIZONTAL, board);
ASSERT_EQ(result.doubleType, NONE);
}

TEST(common_validation_tests, check_right_boundary_vertical) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 11;
new_coords.x = 10;
auto result = check_right_boundary(boundary_coords, new_coords, VERTICAL, board);
ASSERT_EQ(result.doubleType, NORMAL);
}

TEST(common_validation_tests, check_right_boundary_vertical_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 15;
new_coords.x = 10;

ASSERT_EQ(check_right_boundary(boundary_coords, new_coords, VERTICAL, board).doubleType, NONE);
}

TEST(common_validation_tests, check_right_boundary_cross) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 11;
new_coords.x = 11;

ASSERT_EQ(check_right_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NORMAL);
}

TEST(common_validation_tests, check_right_boundary_cross_false_y_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 12;
new_coords.x = 11;

ASSERT_EQ(check_right_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NONE);
}

TEST(common_validation_tests, check_right_boundary_cross_false_x_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 11;
new_coords.x = 15;

ASSERT_EQ(check_right_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_horizontal) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 10;
new_coords.x = 9;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, HORIZONTAL).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_horizontal_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 10;
new_coords.x = 5;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, HORIZONTAL).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_vertical) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 10;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, VERTICAL).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_vertical_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 5;
new_coords.x = 10;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, VERTICAL).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_cross) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 9;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_cross_false_y_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 7;
new_coords.x = 9;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_cross_false_x_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 7;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS).doubleType, NONE);
}

TEST(double_three_check_tests, open_space_is_empty_positive) {
    Coordinates coords;
    coords.y = 10;
    coords.x = 10;


    auto board = create_filled_board();
    board[coords.y][coords.x] = Tile::EMPTY;

    // function undertest
    ASSERT_TRUE(open_space_is_empty(coords, board));
}

TEST(double_three_check_tests, open_space_is_empty_negative) {
    Coordinates coords;
    coords.y = 10;
    coords.x = 10;


    auto board = create_empty_board();
    board[coords.y][coords.x] = Tile::P2;
    // function undertest
    ASSERT_FALSE(open_space_is_empty(coords, board));
}
