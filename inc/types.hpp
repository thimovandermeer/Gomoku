//
// Created by Thimo Van der meer on 3/9/23.
//

#ifndef GOMOKU_TYPES_HPP
#define GOMOKU_TYPES_HPP
#include "string"
enum class Tile {
    P1, P2, EMPTY
};

enum class Player {
    PLAYERONE, PLAYERTWO
};

enum Direction {
    HORIZONTAL, VERTICAL, CROSS
};

struct Coordinates {
    int y;
    int x;
};

enum State {
    ACCEPTED, ERROR
};

struct errorState {
    State state;
    std::string error_reason;
};

struct Doubles {
    Coordinates left_boundary_coordinates;
    Coordinates right_boundary_coordinates;
    Direction direction;
};

struct Threes {
    Coordinates left_boundary_coordinates;
    Coordinates right_boundary_coordinates;
    Coordinates open_space_coordinates;
    bool        full_free;
    bool        open_space;
    Direction   direction;
};

enum double_type {
    NORMAL, EMPTYSPACE, NONE
};

struct boundary_check_return {
    double_type doubleType;
    Coordinates	openSpace;
};


#endif //GOMOKU_TYPES_HPP
