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
    virtual Doubles
    createTwo(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
};

class Two : public ITwo {
public:
    Two();
    Two(const Two&) {};
    ~Two() override = default;

    Doubles boundaryCheck(Coordinate coordinatesOnBoard, Coordinate newCoordinates);
    Doubles
    createTwo(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) override;
    static Coordinate
    checkTwoInARow(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player);
    static Direction determineDirection(Doubles doubles);
};


#endif //GOMOKU_DOUBLETWO_H
