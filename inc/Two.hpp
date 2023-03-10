//
// Created by Thimo Van der meer on 2/10/23.
//

#ifndef GOMOKU_DOUBLETWO_H
#define GOMOKU_DOUBLETWO_H

#include <string>
#include <vector>
#include "logger.hpp"
#include "Gomoku.hpp"
#include "types.hpp"

class ITwo {
public:
    virtual ~ITwo() = default;
    virtual Doubles create_two(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
};

class Two : public ITwo {
public:
    Two();
    Two(const Two&) {};
    ~Two() override = default;

    Doubles boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates);
    Doubles create_two(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) override;
    Coordinates check_two_in_a_row(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player);
    Direction determine_direction(Doubles doubles);
};


#endif //GOMOKU_DOUBLETWO_H
