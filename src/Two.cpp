//
// Created by Thimo Van der meer on 2/10/23.
//

#include "Two.hpp"

Two::Two() {
    LOG("TWO constructor");
}

Doubles Two::create_two(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    auto current_coordinates = check_two_in_a_row(board, coord, player);
    if (current_coordinates.y != -1) {
        return (boundary_check(current_coordinates, coord));
    } else {
        auto fake = Coordinates{-1,-1};
        auto FakeDoubles = Doubles{fake, fake};
        return FakeDoubles;
    }
}


Coordinates Two::check_two_in_a_row(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    Coordinates already_on_board_coords{};
    LOG("incoming coords %i, %i", coord.y, coord.x);
    if (static_cast<Player>(board[coord.y - 1][coord.x - 1]) == player) {
        already_on_board_coords.y = coord.y - 1;
        already_on_board_coords.x = coord.x - 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y][coord.x - 1]) == player) {
        already_on_board_coords.y = coord.y;
        already_on_board_coords.x = coord.x - 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y + 1][coord.x - 1]) == player) {
        already_on_board_coords.y = coord.y + 1;
        already_on_board_coords.x = coord.x - 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y][coord.x + 1]) == player) {
        already_on_board_coords.y = coord.y;
        already_on_board_coords.x = coord.x + 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y + 1][coord.x + 1]) == player) {
        already_on_board_coords.y = coord.y + 1;
        already_on_board_coords.x = coord.x + 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y - 1][coord.x + 1]) == player) {
        already_on_board_coords.y = coord.y - 1;
        already_on_board_coords.x = coord.x + 1;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y + 1][coord.x]) == player) {
        already_on_board_coords.y = coord.y + 1;
        already_on_board_coords.x = coord.x;
        return already_on_board_coords;
    } else if (static_cast<Player>(board[coord.y - 1][coord.x]) == player) {
        already_on_board_coords.y = coord.y - 1;
        already_on_board_coords.x = coord.x;
        return already_on_board_coords;
    } else {
        already_on_board_coords.y = -1;
        already_on_board_coords.x = -1;
        return already_on_board_coords;
    }
}

Doubles Two::boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates) {
    auto doubles = Doubles();
    if (coordinates_on_board.y < new_coordinates.y || coordinates_on_board.x < new_coordinates.x) {
        doubles.left_boundary_coordinates = coordinates_on_board;
        doubles.right_boundary_coordinates = new_coordinates;
    } else {
        doubles.left_boundary_coordinates = new_coordinates;
        doubles.right_boundary_coordinates = coordinates_on_board;
    }
    doubles.direction = determine_direction(doubles);
    return doubles;
}

Direction Two::determine_direction(Doubles doubles) {
    if (doubles.left_boundary_coordinates.x == doubles.right_boundary_coordinates.x) {
        return VERTICAL;
    } else if (doubles.left_boundary_coordinates.y == doubles.right_boundary_coordinates.y)
        return HORIZONTAL;
    else {
        return CROSS;
    }
}

