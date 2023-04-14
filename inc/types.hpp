//
// Created by Thimo Van der meer on 3/9/23.
//

#ifndef GOMOKU_TYPES_HPP
#define GOMOKU_TYPES_HPP

#include <string>
#include <vector>

enum class Tile {
    P1, P2, EMPTY, OOB
};

enum class Player {
    PLAYERONE, PLAYERTWO
};

struct Coordinate {
    int x;
    int y;
};

enum OkState {
    ACCEPTED, ERROR
};

struct Doubles {
    Coordinate one;
    Coordinate two;
};

struct State {
    OkState state;
    std::string errorReason;
    bool capture;
    Doubles capturePos;
};

struct bestMove {
    Coordinate bestCoords;
    int maxScore;
};

enum class ButtonId {
    SINGLEPLAYER_GAME,
    MULTIPLAYER_GAME,
    RULES,
    SUGGEST_MOVE
};

enum class GameType {
    INVALID,
    SINGLEPLAYER,
    MULTIPLAYER
};

#endif //GOMOKU_TYPES_HPP
