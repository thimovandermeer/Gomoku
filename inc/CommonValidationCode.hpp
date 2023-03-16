//
// Created by Thimo Van der meer on 16/03/2023.
//

#ifndef GOMOKU_COMMONVALIDATIONCODE_HPP
#define GOMOKU_COMMONVALIDATIONCODE_HPP
#include "types.hpp"

boundary_check_return check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction, const std::vector<std::vector<Tile>> &board);
double_type			check_right_boundary_horizontal(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board);
double_type		check_right_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords);
double_type		check_right_boundary_cross(Coordinates boundary_coords, Coordinates new_coords);
boundary_check_return 	check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction);
double_type		check_left_boundary_horizontal(Coordinates boundary_coords, Coordinates new_coords);
double_type		check_left_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords);
double_type		check_left_boundary_cross(Coordinates boundary_coords, Coordinates new_coords);
bool            check_free_left(Coordinates left_boundary, Direction dir, const std::vector<std::vector<Tile>> &board);
bool            check_free_right(Coordinates right_boundary, Direction dir, const std::vector<std::vector<Tile>> &board);
bool		    open_space_is_empty(Coordinates empty_space, const std::vector<std::vector<Tile>> &board);

#endif //GOMOKU_COMMONVALIDATIONCODE_HPP
