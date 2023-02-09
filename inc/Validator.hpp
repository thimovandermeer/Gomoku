//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP
#include <vector>
#include <string>

enum class Tile;

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

class IValidator {
public:
    virtual std::unique_ptr<IValidator> clone() const = 0;
    virtual ~IValidator() = default;
    virtual errorState validate(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) = 0;
};

class Validator : public IValidator {
public:
    Validator() = default;
    ~Validator() override = default;
    std::unique_ptr<IValidator> clone() const override {
        return std::make_unique<Validator>(*this);
    }

    errorState validate(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player) override;

private:
    void set_data(const std::vector<std::vector<Tile>> &board, const Coordinates& coord, const Player& player);
    void set_board(const std::vector<std::vector<Tile>> &board);
    void set_coordinates(const Coordinates &coord);
    void set_player(const Player &player);
    void set_state(State newState, std::string &errorReason);
    void board_validation();
    void coordinates_validation();
    void boundary_checking();
    void taken_check();
    void player_validation();

    std::vector<std::vector<Tile>>  	_board;
    Coordinates                     	_coord;
    Player                          	_player;
    errorState                           _state;
};


#endif //GOMOKU_VALIDATOR_HPP
