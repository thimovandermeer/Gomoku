//
// Created by Thimo Van der meer on 10/03/2023.
//

#ifndef GOMOKU_CAPTURE_HPP
#define GOMOKU_CAPTURE_HPP

#include "types.hpp"
#include <vector>

class ICapture {
public:
    virtual ~ICapture() = default;
    virtual State CaptureCheck(const Coordinate& newCoords,
                               const std::vector<std::vector<Tile>>& board, const Player& player) = 0;
};

class Capture : public ICapture {
public:
	Capture() {};

	Capture(const Capture &)
	{};

	~Capture() override = default;

	State CaptureCheck(const Coordinate &newCoords,
					   const std::vector<std::vector<Tile>> &board, const Player &player) override;

private:
	bool captureLogic(const Coordinate &newCoords, const Tile &player, const std::vector<std::vector<Tile>> &board);
};

#endif //GOMOKU_CAPTURE_HPP
