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
new_coords.y = 13;
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

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, HORIZONTAL, board).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_horizontal_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 10;
new_coords.x = 5;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, HORIZONTAL, board).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_vertical) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 10;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, VERTICAL, board).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_vertical_false) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 5;
new_coords.x = 10;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, VERTICAL, board).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_cross) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 9;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NORMAL);
}

TEST(common_validation_tests, check_left_boundary_cross_false_y_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 7;
new_coords.x = 9;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NONE);
}

TEST(common_validation_tests, check_left_boundary_cross_false_x_different) {
// create board with double three on it
Coordinates boundary_coords;
boundary_coords.y = 10;
boundary_coords.x = 10;

Coordinates new_coords;
new_coords.y = 9;
new_coords.x = 7;

ASSERT_EQ(check_left_boundary(boundary_coords, new_coords, CROSS, board).doubleType, NONE);
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

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_right_horizontal) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{10,12};

    auto board = create_empty_board();
    board[10][11] = Tile::P2;
    ASSERT_EQ(check_right_boundary_horizontal(boundary_coords, new_coords, board), NONE);
}

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_left_horizontal) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{10,8};

    auto board = create_empty_board();
    board[10][9] = Tile::P2;
    ASSERT_EQ(check_left_boundary_horizontal(boundary_coords, new_coords, board), NONE);
}

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_up_vertical) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{12,10};

    auto board = create_empty_board();
    board[11][10] = Tile::P2;
    ASSERT_EQ(check_right_boundary_vertical(boundary_coords, new_coords, board), NONE);
}

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_down_vertical) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{8,10};

    auto board = create_empty_board();
    board[9][10] = Tile::P2;
    ASSERT_EQ(check_left_boundary_vertical(boundary_coords, new_coords, board), NONE);
}

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_left_cross) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{8,8};

    auto board = create_empty_board();
    board[9][9] = Tile::P2;
    ASSERT_EQ(check_left_boundary_cross(boundary_coords, new_coords, board), NONE);
}

TEST(double_three_check_tests, check_double_three_with_open_space_not_free_right_cross) {
    Coordinates boundary_coords{10,10};
    Coordinates new_coords{12,12};

    auto board = create_empty_board();
    board[11][11] = Tile::P2;
    ASSERT_EQ(check_right_boundary_cross(boundary_coords, new_coords, board) , NONE);
}




