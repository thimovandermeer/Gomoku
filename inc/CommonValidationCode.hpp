//
// Created by Thimo Van der meer on 16/03/2023.
//

#ifndef GOMOKU_COMMONVALIDATIONCODE_HPP
#define GOMOKU_COMMONVALIDATIONCODE_HPP

#include "types.hpp"

BoundaryCheckReturn check_right_boundary(Coordinate boundaryCoords, Coordinate newCoords, Direction direction, const std::vector<std::vector<Tile>>& board);
DoubleType check_right_boundary_horizontal(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
DoubleType check_right_boundary_vertical(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
DoubleType check_right_boundary_cross(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
BoundaryCheckReturn check_left_boundary(Coordinate boundaryCoords, Coordinate newCoords, Direction direction, const std::vector<std::vector<Tile>>& board);
DoubleType check_left_boundary_horizontal(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
DoubleType check_left_boundary_vertical(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
DoubleType check_left_boundary_cross(Coordinate boundaryCoords, Coordinate newCoords, const std::vector<std::vector<Tile>>& board);
bool check_free_left(Coordinate leftBoundary, Direction dir, const std::vector<std::vector<Tile>>& board);
bool check_free_right(Coordinate rightBoundary, Direction dir, const std::vector<std::vector<Tile>>& board);
bool open_space_is_empty(Coordinate emptySpace, const std::vector<std::vector<Tile>>& board);

#endif //GOMOKU_COMMONVALIDATIONCODE_HPP
