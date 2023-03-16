//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "utils.hpp"
#include <iostream>

std::vector<std::vector<Tile>> create_empty_board() {
    return {MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::EMPTY}};
}

std::vector<std::vector<Tile>> create_filled_board() {
    return {MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::P1}};
}

void printBoard(const std::vector<std::vector<Tile>>& b) {
    for (const auto& elem : b) {
        for (const auto& nr : elem) {
            std::cerr << (int)nr << " ";
        }
        std::cerr << "\n";
    }
}