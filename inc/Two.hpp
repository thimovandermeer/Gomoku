//
// Created by Thimo Van der meer on 2/10/23.
//

#ifndef GOMOKU_DOUBLETWO_H
#define GOMOKU_DOUBLETWO_H

#include <string>
#include <vector>
#include "logger.hpp"

enum class Tile;

enum Direction {
    HORIZONTAL, VERTICAL, CROSS
};

struct Coordinates {
    int x;
    int y;
};
enum Player {
    PLAYERONE, PLAYERTWO
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


class ITwo {
public:
    virtual ~ITwo() = default;
    virtual Doubles create_two(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
};

class Two : public ITwo {
public:
    Two();
    Two(const Two&) {}
    ~Two() override = default;

    Doubles boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates);
    Doubles create_two(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) override;
    Coordinates check_two_in_a_row(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player);
    Direction determine_direction(Doubles doubles);
};


#endif //GOMOKU_DOUBLETWO_H
