//
// Created by Thimo Van der meer on 10/03/2023.
//

#ifndef GOMOKU_CAPTURE_HPP
#define GOMOKU_CAPTURE_HPP

#include "types.hpp"
#include "DoubleThreeCheck.hpp"
#include <vector>

class IDoubleThreeCheck;
class ICapture {
public:
    virtual ~ICapture() = default;
    virtual State CaptureCheck(const Coordinate& newCoords, const std::vector<std::vector<Tile>>& board, const Player& player) = 0;
};

class Capture : public ICapture {
public:
	Capture(std::unique_ptr<IDoubleThreeCheck> &doubleThree) :_doubleThreeCheck(std::move(doubleThree)) {};

	Capture()
	{};

	~Capture() override = default;

	State CaptureCheck(const Coordinate &newCoords,
					   const std::vector<std::vector<Tile>> &board, const Player &player) override;

private:
	State captureLogic();
	void 	setVars(const Coordinate &newCoords, const Tile &player, const std::vector<std::vector<Tile>>& board);
	bool checkLeftHorizontal();
	bool checkRightHorizontal();
	bool checkLeftVertical();
	bool checkRightVertical();
	bool checkDiagonalLeftDown();
	bool checkDiagonalLeftUp();
	bool checkDiagonalRightDown();
	bool checkDiagonalRightUp();


	/*
	 * vars
	 */

	Coordinate _newCoords;
	Tile		_player;
	Tile		_opponent;
	std::vector<std::vector<Tile>> 	_board;
	std::unique_ptr<IDoubleThreeCheck> _doubleThreeCheck;

};

#endif //GOMOKU_CAPTURE_HPP
