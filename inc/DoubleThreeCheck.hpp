//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP

#include <memory>
#include <string>
#include <vector>
#include "Two.hpp"
#include "types.hpp"


class ITwo;
class IDoubleThreeCheck {
public:
    virtual ~IDoubleThreeCheck() = default;
    virtual errorState DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
    virtual std::vector<Doubles>    get_double_two() = 0;
};

class DoubleThreeCheck : public IDoubleThreeCheck {
public:
    explicit DoubleThreeCheck(std::unique_ptr<ITwo>& Two) : _two(std::move(Two)) {
        _doubleTwoList = std::vector<Doubles>();
        _full_frees = 0;
    }
    DoubleThreeCheck(const DoubleThreeCheck&) {}
    ~DoubleThreeCheck() override = default;

	Threes			fill_double_three_stack(Coordinates bound_coordinates, Coordinates newCoords, boundary_check_return type, bool left, Direction dir);
	void 			set_board(const std::vector<std::vector<Tile>> &board);
	size_t			double_two_size();
	errorState 		DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates& new_coord, const Player& player) override;
    bool 			find_three(Coordinates newCoords, std::vector<Doubles> &double_two);
    errorState 		find_double_three();


	bool 			two_in_a_row(const std::vector<std::vector<Tile>> &board, const Coordinates &coord, const Player& play);
    Threes			get_last_three();
    bool            full_free_check();

    std::vector<Doubles>    get_double_two() override;
private:
    void set_state(State newState, std::string& errorReason);
    std::vector<Threes>             _doubleThreeList;
    std::vector<Doubles>            _doubleTwoList;
    errorState                      _state;
    std::shared_ptr<ITwo>          _two;
    std::vector<std::vector<Tile>> _board;
    int                             _full_frees;

};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
