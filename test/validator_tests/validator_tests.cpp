//
// Created by Thimo Van der meer on 2/3/23.
//

#include <gtest/gtest.h>
#include "Gomoku.hpp"

#define MAX_BOARD_SIZE 19

// move this function to utils folder
std::vector<std::vector<Tile>> create_empty_board() {
    return{MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::FREE}};
}

std::vector<std::vector<Tile>> create_filled_board() {
    return{MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::PLAYERONE}};
}

// create unit test for above function
TEST(validator_tests, create_empty_board_test) {
    std::vector<std::vector<Tile>> board = create_empty_board();
    ASSERT_TRUE(board.size() == 19) << "Size should be 20 but is: " << board.size() << "\n";
}

TEST(validator_tests, out_of_board_test_y) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{0,20};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state, ERROR) << "location should be out of the board\n";
}

TEST(validator_tests, in_board_test_y) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{0,18};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state, ACCEPTED) << "location should be out of the board\n";
}

TEST(validator_tests, out_of_board_test_x) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{21,0};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state, ERROR) << "location should be out of the board\n";
}

TEST(validator_tests, in_board_test_x) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{18,0};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state, ACCEPTED) << "location should be out of the board\n";
}

TEST(validator_tests, out_of_board_test_minus) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{-21,0};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state, ERROR) << "Number is negative impossible on board\n";
}

TEST(validator_tests, spot_taken) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_filled_board();
    Coordinates coords{5,5};
    Player player{PLAYERONE};
    ASSERT_EQ(validate.validate(board, coords, player).state,ERROR) << "This coordinates are already taken\n";
}

