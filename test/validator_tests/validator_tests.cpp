//
// Created by Thimo Van der meer on 2/3/23.
//

#include <gtest/gtest.h>
#include "/Users/thvan-de/CLionProjects/Gomoku/inc/Validator.hpp"

// move this function to utils folder
std::vector<std::vector<Tile>> create_empty_board() {
    return{20, {20, Tile::FREE}};
}

// create unit test for above function
TEST(validator_tests, create_empty_board_test) {
    std::vector<std::vector<Tile>> board = create_empty_board();
    ASSERT_TRUE(board.size() == 20);
}

TEST(validator_tests, out_of_board_test) {
    Validator validate = Validator();
    std::vector<std::vector<Tile>> board = create_empty_board();
    Coordinates coords{0,0};
    Player player{PLAYERONE};
    validate.validate(board, coords, player);


}