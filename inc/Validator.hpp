//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP
#include <vector>

enum class Tile;

struct Coordinates {
    int x;
    int y;
};
enum Player {PLAYERONE, PLAYERTWO};

// state implementation instead of returning bools implementeren
enum State {ACCEPTED, ERROR};

//struct State_one {
//    State       state;
//    std::string error_reason;
//};

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual State validate(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) = 0;
};

class Validator : public IValidator {
public:
    Validator() = default;
    ~Validator() override = default;

    State validate(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) override;

private:
    void set_data(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player);
    void set_board(const std::vector<std::vector<Tile>> &board);
    void set_coordinates(const Coordinates &coord);
    void set_player(const Player &player);
    void set_state(State newState);
    void board_validation();
    void coordinates_validation();
    void boundary_checking();
    void taken_check();
    void player_validation();

    std::vector<std::vector<Tile>>  _board;
    Coordinates                     _coord;
    Player                          _player;
    State                           _state;
};


#endif //GOMOKU_VALIDATOR_HPP
