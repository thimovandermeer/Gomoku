//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

struct Coordinates {int x, int y};
enum player {PLAYERONE, PLAYERTWO};

class IValidator {
public:
    bool validate(std::vector<std::vector<tile>> board, Coordinates, player) = 0;
};

class Validator : IValidator {
public:
    Validator() = default;
    ~Validator() = default;
    bool validate(std::vector<std::vector<tile>> board, Coordinates, player);
private:


};


#endif //GOMOKU_VALIDATOR_HPP
