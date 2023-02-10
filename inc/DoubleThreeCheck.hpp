//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP
#include <memory>
#include <string>
#include <vector>
#include "Two.hpp"

class IDoubleThreeCheck {
public:
    virtual std::unique_ptr<IDoubleThreeCheck> clone() const = 0;
	virtual ~IDoubleThreeCheck() = default;
	virtual errorState DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) = 0;
};

class DoubleThreeCheck: public IDoubleThreeCheck
{
public:
	DoubleThreeCheck(ITwo &Two) : _Two(Two.clone()) {}
    DoubleThreeCheck(const DoubleThreeCheck&) {}
	~DoubleThreeCheck() = default;
	std::unique_ptr<IDoubleThreeCheck> clone() const override {
		return std::make_unique<DoubleThreeCheck>(*this);
	}

	size_t	double_two_size();
	errorState DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) override;
    bool find_three(Coordinates newCoords, std::vector<Doubles> &double_two);
    errorState find_double_three();
    bool check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction);
    bool check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction);
    Direction determine_direction(Doubles doubles);
	Doubles boundary_check(Coordinates coordinates_on_board, Coordinates new_coordinates);
	void two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play);
	Coordinates check_two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& player);
    Doubles get_last_three();
private:
	std::vector<Doubles>	_doubleThreeList;
	std::vector<Doubles>	_doubleTwoList;

	void set_state(State newState, std::string &errorReason);
	errorState                          _state;

    std::unique_ptr<ITwo>               _Two;

};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
