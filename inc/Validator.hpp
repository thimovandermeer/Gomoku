//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

#include <vector>
#include "Gomoku.hpp"



struct Coordinates {
    int x;
    int y;
};
enum Player {PLAYERONE, PLAYERTWO};

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual bool validate(std::vector<std::vector<Tile>> board, Coordinates coord, Player player) = 0;
};

class Validator : public IValidator {
public:
    Validator() = default;
    ~Validator() override = default;
    bool validate(std::vector<std::vector<Tile>> board, Coordinates, Player);
private:


};


#endif //GOMOKU_VALIDATOR_HPP
