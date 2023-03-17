//
// Created by Thimo Van der meer on 2/10/23.
//

#include "Two.hpp"
#include "logger.hpp"

Two::Two() {
    LOG("TWO constructor");
}

Doubles Two::createTwo(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    auto current_coordinates = checkTwoInARow(board, coord, player);
    if (current_coordinates.y != -1) {
        return (boundaryCheck(current_coordinates, coord));
    } else {
        auto fake = Coordinate{-1, -1};
        auto FakeDoubles = Doubles{fake, fake, {}};
        return FakeDoubles;
    }
}


Coordinate Two::checkTwoInARow(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    Coordinate already_on_board_coords{};
    LOG("incoming coords %i, %i", coord.y, coord.x);
    // TODO: do the boundary checks properly now everything around the boundaries is not done
    if (coord.x > 0 && coord.y > 0) {
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
    //TODO: boundary checkign should be done here if they near the boundaries of a board
    return {-1, -1};
}

Doubles Two::boundaryCheck(Coordinate coordinatesOnBoard, Coordinate newCoordinates) {
    auto doubles = Doubles();
    if (coordinatesOnBoard.y < newCoordinates.y || coordinatesOnBoard.x < newCoordinates.x) {
        doubles.leftBoundaryCoordinates = coordinatesOnBoard;
        doubles.rightBoundaryCoordinates = newCoordinates;
    } else {
        doubles.leftBoundaryCoordinates = newCoordinates;
        doubles.rightBoundaryCoordinates = coordinatesOnBoard;
    }
    doubles.direction = determineDirection(doubles);
    return doubles;
}

Direction Two::determineDirection(Doubles doubles) {
    if (doubles.leftBoundaryCoordinates.x == doubles.rightBoundaryCoordinates.x) {
        return VERTICAL;
    } else if (doubles.leftBoundaryCoordinates.y == doubles.rightBoundaryCoordinates.y) {
        return HORIZONTAL;
    } else {
        return CROSS;
    }
}

