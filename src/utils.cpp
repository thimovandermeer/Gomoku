//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "utils.hpp"
std::vector<std::vector<Tile>> create_empty_board() {
	return{MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::FREE}};
}

std::vector<std::vector<Tile>> create_filled_board() {
	return{MAX_BOARD_SIZE, {MAX_BOARD_SIZE, Tile::PLAYERONE}};
}
