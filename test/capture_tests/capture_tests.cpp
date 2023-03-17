//
// Created by Thimo Van der meer on 10/03/2023.
//

#include <gtest/gtest.h>
#include "Capture.hpp"
#include "utils.hpp"

// dit worden alleen maar Gmock like tests dus met I expect this function to be called once etc

Capture capture_object{};

TEST(capture_tests, left_boundary_horizontal_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 7;

    doubles.rightBoundaryCoordinates.y = 8;
    doubles.rightBoundaryCoordinates.x = 8;
    // add coordinates right side

    Coordinate coords;
    coords.y = 8;
    coords.x = 6;
    doubles.direction = HORIZONTAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[8][9] = Tile::P1;
    LOG("TEST");
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);

}

TEST(capture_tests, left_boundary_vertical_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 8;

    doubles.rightBoundaryCoordinates.y = 9;
    doubles.rightBoundaryCoordinates.x = 8;
    // add coordinates right side

    Coordinate coords;
    coords.y = 7;
    coords.x = 8;
    doubles.direction = VERTICAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[10][8] = Tile::P1;
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);

}

TEST(capture_tests, left_boundary_cross_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 8;

    doubles.rightBoundaryCoordinates.y = 9;
    doubles.rightBoundaryCoordinates.x = 9;
    // add coordinates right side

    Coordinate coords;
    coords.y = 7;
    coords.x = 7;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[10][10] = Tile::P1;
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);
}

TEST(capture_tests, right_boundary_horizontal_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 8;

    doubles.rightBoundaryCoordinates.y = 8;
    doubles.rightBoundaryCoordinates.x = 9;
    // add coordinates right side

    Coordinate coords;
    coords.y = 8;
    coords.x = 10;
    doubles.direction = HORIZONTAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[8][7] = Tile::P1;
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);
}

TEST(capture_tests, right_boundary_vertical_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 8;

    doubles.rightBoundaryCoordinates.y = 9;
    doubles.rightBoundaryCoordinates.x = 8;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 8;
    doubles.direction = VERTICAL;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[7][8] = Tile::P1;
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);
}

TEST(capture_tests, right_boundary_cross_capture) {
    Doubles doubles;

    doubles.leftBoundaryCoordinates.y = 8;
    doubles.leftBoundaryCoordinates.x = 8;

    doubles.rightBoundaryCoordinates.y = 9;
    doubles.rightBoundaryCoordinates.x = 9;
    // add coordinates right side

    Coordinate coords;
    coords.y = 10;
    coords.x = 10;
    doubles.direction = CROSS;


    // check coordinates
    std::vector<Doubles> vec;
    vec.push_back(doubles);
    auto board = create_empty_board();
    board[7][7] = Tile::P1;
    auto result = capture_object.CaptureCheck(vec, coords, board, Player::PLAYERONE);
    ASSERT_TRUE(result.capture);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.y, doubles.leftBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.leftBoundaryCoordinates.x, doubles.leftBoundaryCoordinates.x);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.y, doubles.rightBoundaryCoordinates.y);
    ASSERT_EQ(result.capturePos.rightBoundaryCoordinates.x, doubles.rightBoundaryCoordinates.x);
}

