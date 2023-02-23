//
// Created by Thimo Van der meer on 16/02/2023.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"
#include "../inc/DoubleThreeCheck.hpp"
#include "utils.hpp"

std::unique_ptr<ITwo> two_check_two = std::make_unique<Two>();
DoubleThreeCheck three_check_three = DoubleThreeCheck(two_check_two);


std::vector<std::vector<Tile>> create_double_three_board_vertically() {
    std::vector<std::vector<Tile>> board = create_empty_board();
    board[11][10] = Tile::P1;
    board[12][10] = Tile::P1;
    board[13][10] = Tile::P1;
    return board;
}

std::vector<std::vector<Tile>> create_double_three_board_cross() {
    std::vector<std::vector<Tile>> board = create_empty_board();
    board[3][3] = Tile::P1;
    board[4][4] = Tile::P1;
    board[5][5] = Tile::P1;
    return board;
}

std::vector<std::vector<Tile>> create_double_two_board_horizontally() {
    std::vector<std::vector<Tile>> board = create_empty_board();
    board[10][11] = Tile::P1;
    return board;
}

TEST(double_two_check_tests, find_double_two_horizontally) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 10;
    coord.x = 12;
    auto two = *dynamic_cast<Two*>(two_check_two.get());
    auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
    ASSERT_EQ(result.y, 10);
    ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_vertically) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 11;
    coord.x = 11;

    auto two = *dynamic_cast<Two*>(two_check_two.get());
    auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
    ASSERT_EQ(result.y, 10);
    ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_up) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 11;
    coord.x = 12;

    auto two = *dynamic_cast<Two*>(two_check_two.get());
    auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
    ASSERT_EQ(result.y, 10);
    ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, find_double_two_cross_down) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 9;
    coord.x = 11;

    auto two = *dynamic_cast<Two*>(two_check_two.get());
    auto result = two.check_two_in_a_row(board, coord, PLAYERONE);
    ASSERT_EQ(result.y, 10);
    ASSERT_EQ(result.x, 11);
}

TEST(double_two_check_tests, no_double_two_possible) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 17;
    coord.x = 17;

    auto two = *dynamic_cast<Two*>(two_check_two.get());
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

    auto two = *dynamic_cast<Two*>(two_check_two.get());
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
    auto two = *dynamic_cast<Two*>(two_check_two.get());
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
    auto two = *dynamic_cast<Two*>(two_check_two.get());
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
    auto two = *dynamic_cast<Two*>(two_check_two.get());
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
    auto two = *dynamic_cast<Two*>(two_check_two.get());
    ASSERT_EQ(two.determine_direction(doubles), CROSS);
}

TEST(double_two_boundary_checks, check_on_board_bigger_than_new) {
    Coordinates coord_one;
    coord_one.y = 9;
    coord_one.x = 11;

    Coordinates coord_two;
    coord_two.y = 8;
    coord_two.x = 11;

    auto two = *dynamic_cast<Two*>(two_check_two.get());
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

    auto two = *dynamic_cast<Two*>(two_check_two.get());
    auto result = two.boundary_check(coord_one, coord_two);
    ASSERT_EQ(result.left_boundary_coordinates.y, coord_two.y);
    ASSERT_EQ(result.left_boundary_coordinates.x, coord_two.x);
}

TEST(double_two_two_in_a_row, check_size_double_two_vector) {
    auto board = create_double_two_board_horizontally();
    Coordinates coord;
    coord.y = 11;
    coord.x = 12;

    three_check_three.two_in_a_row(board, coord, PLAYERONE);
    ASSERT_EQ(1, three_check_three.double_two_size());
}