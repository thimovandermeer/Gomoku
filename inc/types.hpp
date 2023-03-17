//
// Created by Thimo Van der meer on 3/9/23.
//

#ifndef GOMOKU_TYPES_HPP
#define GOMOKU_TYPES_HPP

#include <string>

enum class Tile {
    P1, P2, EMPTY
};

enum class Player {
    PLAYERONE, PLAYERTWO
};

enum Direction {
    HORIZONTAL, VERTICAL, CROSS
};

struct Coordinate {
    int y;
    int x;
};

enum OkState {
    ACCEPTED, ERROR
};

struct Doubles {
    Coordinate leftBoundaryCoordinates;
    Coordinate rightBoundaryCoordinates;
    Direction direction;
};

struct State {
    OkState         state;
    std::string     errorReason;
    bool            capture;
    Doubles         capture_pos;
};



struct Threes {
    Coordinate leftBoundaryCoordinates;
    Coordinate rightBoundaryCoordinates;
    Coordinate openSpaceCoordinates;
    bool fullFree;
    bool openSpace;
    Direction direction;
};

enum DoubleType {
    NORMAL, EMPTYSPACE, NONE
};

struct BoundaryCheckReturn {
    DoubleType doubleType;
    Coordinate openSpace;
};

#endif //GOMOKU_TYPES_HPP
