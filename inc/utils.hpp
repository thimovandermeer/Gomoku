//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_UTILS_HPP
#define GOMOKU_UTILS_HPP

#include "types.hpp"

std::vector<std::vector<Tile>> create_empty_board();
std::vector<std::vector<Tile>> create_filled_board();
void printBoard(const std::vector<std::vector<Tile>>& b);
void printBoardAi(const std::vector<std::vector<TileAi>>& b);
#endif //GOMOKU_UTILS_HPP
