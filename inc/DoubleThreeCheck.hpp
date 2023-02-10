//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP
#include <memory>
#include <string>
#include <vector>
//#include "Validator.hpp"

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

class IDoubleThreeCheck {
public:
    virtual std::unique_ptr<IDoubleThreeCheck> clone() const = 0;
	virtual ~IDoubleThreeCheck() = default;
	virtual errorState DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) = 0;
};

class DoubleThreeCheck: public IDoubleThreeCheck
{
public:
	DoubleThreeCheck() = default;
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

};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
