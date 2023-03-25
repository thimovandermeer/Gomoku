//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP

#include <memory>
#include <string>
#include <vector>
#include "types.hpp"

class ITwo;

class IDoubleThreeCheck {
public:
    virtual ~IDoubleThreeCheck() = default;
    virtual State DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
};

class DoubleThreeCheck : public IDoubleThreeCheck {
public:
    explicit DoubleThreeCheck() {
		p1_doubleThreeExists = 0;
		p2_doubleThreeExists = 0;
	}
    DoubleThreeCheck(const DoubleThreeCheck&){}
    ~DoubleThreeCheck() override = default;

	State DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) override;


private:
	int doubleThreeCheckLogic(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board);
	int checkHorizontal(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board);
	int checkVertical(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board);
	int checkDiagonal(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board);
	int checkAntiDiagonal(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board);

	int p1_doubleThreeExists;
	int p2_doubleThreeExists;
};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
