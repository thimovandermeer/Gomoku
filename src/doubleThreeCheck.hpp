//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP
#include <memory>
#include "../inc/Validator.hpp"

class IDoubleThreeCheck {
public:
	virtual ~IDoubleThreeCheck() = default;
	virtual std::unique_ptr<IDoubleThreeCheck> clone() const = 0;
	virtual void DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) = 0;
};

class DoubleThreeCheck: public IDoubleThreeCheck
{
public:
	std::unique_ptr<IDoubleThreeCheck> clone() const override {
		return std::make_unique<DoubleThreeCheck>(*this);
	}

	void DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) override;
private:
	errorState set_state(State newState, std::string &errorReason);
	std::vector<std::vector<Tile>>  	_board;
	Coordinates                     	_coord;
	Player                          	_player;
	errorState                           _state;
};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
