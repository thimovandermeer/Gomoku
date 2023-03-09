//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

#include "DoubleThreeCheck.hpp"
#include <vector>
#include <string>
#include "types.hpp"
#define MAX_BOARD_SIZE 19

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual errorState
    validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
};
class IDoubleThreeCheck;

class Validator : public IValidator {
public:
    explicit Validator(std::unique_ptr<IDoubleThreeCheck>& DoubleThreeCheck)
            : _coord{}, _player{}, _doubleThreeCheck(std::move(DoubleThreeCheck)) {}
    ~Validator() override = default;

    errorState
    validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) override;

private:
    void set_data(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player);
    void set_board(const std::vector<std::vector<Tile>>& board);
    void set_coordinates(const Coordinates& coord);
    void set_player(const Player& player);
    void set_state(State newState, std::string& errorReason);
    void board_validation();
    void coordinates_validation();
    void boundary_checking();
    void taken_check();
    void player_validation();
    void double_three_validation();

    std::vector<std::vector<Tile>> _board;
    Coordinates _coord;
    Player _player;
    errorState _state;

    std::unique_ptr<IDoubleThreeCheck> _doubleThreeCheck;
};

#endif //GOMOKU_VALIDATOR_HPP
