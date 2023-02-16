//
// Created by Thimo Van der meer on 2/10/23.
//

#ifndef GOMOKU_DOUBLETWO_H
#define GOMOKU_DOUBLETWO_H

#include "logger.hpp"
#include <string>
#include <vector>

enum Direction {HORIZONTAL, VERTICAL, CROSS};
enum class Tile{PLAYERONE, PLAYERTWO, FREE};
struct Coordinates {
    int x;
    int y;
};
enum Player {PLAYERONE, PLAYERTWO};

enum State {ACCEPTED, ERROR};

struct errorState {
    State       state;
    std::string error_reason;
};

struct Doubles {
    Coordinates left_boundary_coordinates;
    Coordinates right_boundary_coordinates;
    Direction   direction;
};


class ITwo {
public:
    virtual std::unique_ptr<ITwo> clone() const = 0;
    virtual ~ITwo() = default;
    virtual  Doubles         create_two(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& player) = 0;
};

class Two : public ITwo{
public:
    Two();
    Two(const Two&) {}
    ~Two() = default;
    std::unique_ptr<ITwo> clone() const override  {
        return std::make_unique<Two>(*this);
    }

    Doubles 		boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates);
    Doubles         create_two(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& player) override;
    Coordinates		check_two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& player);
    Direction       determine_direction(Doubles doubles);
};



#endif //GOMOKU_DOUBLETWO_H
