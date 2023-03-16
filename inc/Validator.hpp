//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

#include "DoubleThreeCheck.hpp"
#include "Capture.hpp"
#include <vector>
#include <string>
#include "types.hpp"
#define MAX_BOARD_SIZE 19

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual errorState validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player,const std::vector<Doubles> &opponent_doubles) = 0;
    virtual std::vector<Doubles> get_double_two_list() = 0;
};
class IDoubleThreeCheck;

class Validator : public IValidator {
public:
    explicit Validator(std::unique_ptr<IDoubleThreeCheck>& DoubleThreeCheck, std::unique_ptr<ICapture>& Capture)
            :
            _coord{},
            _player{},
            _doubleThreeCheck(std::move(DoubleThreeCheck)),
            _capture(std::move(Capture)) {}
    ~Validator() override = default;

    errorState
    validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player,const std::vector<Doubles> &opponent_doubles) override;
    std::vector<Doubles> get_double_two_list() override;
private:
    void set_data(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player);
    void set_board(const std::vector<std::vector<Tile>>& board);
    void set_coordinates(const Coordinates& coord);
    void set_player(const Player& player);
    void set_state(State newState, std::string& errorReason);
    void set_opponent_doubles(const std::vector<Doubles> &opponent_doubles);
    void board_validation();
    void coordinates_validation();
    void boundary_checking();
    void taken_check();
    void player_validation();
    void double_three_validation();
    void update_double_list();
    void capture_validation();
    std::vector<std::vector<Tile>> _board;
    Coordinates _coord;
    Player _player;
    errorState _state;
    std::vector<Doubles>                _opponent_doubles;

    std::vector<Doubles>                _double_list;
    std::unique_ptr<IDoubleThreeCheck>  _doubleThreeCheck;
    std::unique_ptr<ICapture>           _capture;
};

#endif //GOMOKU_VALIDATOR_HPP
